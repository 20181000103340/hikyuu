#!/usr/bin/python
# -*- coding: utf8 -*-
# cp936

import os.path
import pathlib
import struct
import sqlite3
import datetime
import math
import sys

import tables as tb

from io import SEEK_END, SEEK_SET

from common import *

HDF5_COMPRESS_LEVEL = 9

def ProgressBar(cur, total):
    percent = '{:.0%}'.format(cur / total)
    sys.stdout.write('\r')
    sys.stdout.write("[%-50s] %s" % ('=' * int(math.floor(cur * 50 / total)),percent))
    sys.stdout.flush()


class H5Record(tb.IsDescription):
    datetime = tb.UInt64Col()        #IGNORE:E1101
    openPrice = tb.UInt32Col()       #IGNORE:E1101
    highPrice = tb.UInt32Col()       #IGNORE:E1101
    lowPrice = tb.UInt32Col()        #IGNORE:E1101
    closePrice = tb.UInt32Col()      #IGNORE:E1101
    transAmount = tb.UInt64Col()     #IGNORE:E1101
    transCount = tb.UInt64Col()      #IGNORE:E1101
    
class H5Index(tb.IsDescription):
    datetime = tb.UInt64Col()        #IGNORE:E1101
    start    = tb.UInt64Col()        #IGNORE:E1101


def create_database(connect):
    """创建SQLITE3数据库表"""
    try:
        cur = connect.cursor()
        filename = os.getcwd() + '/sqlite_createdb.sql'
        with open(filename, 'r', encoding='utf8') as sqlfile:
            cur.executescript(sqlfile.read())
        connect.commit()
        cur.close()
    except sqlite3.OperationalError:
        print("相关数据表可能已经存在，放弃创建。如需重建，请手工删除相关数据表。")
    except Exception as e:
        raise(e)


def get_marketid(connect, market):
    cur = connect.cursor()
    a = cur.execute("select marketid, market from market where market='{}'".format(market))
    marketid = [i for i in a]
    marketid = marketid[0][0]
    cur.close()
    return marketid


def get_codepre_list(connect, marketid, quotations):
    stktype_list = get_stktype_list(quotations)
    sql = "select codepre, type from coderuletype " \
          "where marketid={marketid} and type in {type_list}"\
        .format(marketid=marketid, type_list=stktype_list)
    cur = connect.cursor()
    a = cur.execute(sql)
    a = a.fetchall()
    cur.close()
    return sorted(a, key=lambda k: len(k[0]), reverse=True)


def tdx_import_stock_name_from_file(connect, filename, market, quotations=None):
    """更新每只股票的名称、当前是否有效性、起始日期及结束日期
        如果导入的代码表中不存在对应的代码，则认为该股已失效

        :param connect: sqlite3实例
        :param filename: 代码表文件名
        :param market: 'SH' | 'SZ'
        :param quotation: 待导入的行情类别，空为导入全部 'stock' | 'fund' | 'bond' | None
    """
    cur = connect.cursor()

    newStockDict = {}
    with open(filename, 'rb') as f:
        data = f.read(50)
        data = f.read(314)
        while data:
            a = struct.unpack('6s 17s 8s 283s', data)
            stockcode = a[0].decode()
            stockname = a[2].decode(encoding='gbk').encode('utf8')
            pos = stockname.find(0x00)
            if pos >= 0:
                stockname = stockname[:pos]
            newStockDict[stockcode] = stockname.decode(encoding='utf8').strip()
            data = f.read(314)

    a = cur.execute("select marketid from market where market = '%s'" % market.upper())
    marketid = [i for i in a]
    marketid = marketid[0][0]

    stktype_list = get_stktype_list(quotations)
    a = cur.execute("select stockid, code, name, valid from stock where marketid={} and type in {}"
                    .format(marketid, stktype_list))
    a = a.fetchall()
    oldStockDict = {}
    for oldstock in a:
        oldstockid, oldcode, oldname, oldvalid = oldstock[0], oldstock[1], oldstock[2], int(oldstock[3])
        oldStockDict[oldcode] = oldstockid

        # 新的代码表中无此股票，则置为无效
        if (oldvalid == 1) and (oldcode not in newStockDict):
            cur.execute("update stock set valid=0 where stockid=%i" % oldstockid)

        # 股票名称发生变化，更新股票名称;如果原无效，则置为有效
        if oldcode in newStockDict:
            if oldname != newStockDict[oldcode]:
                cur.execute("update stock set name='%s' where stockid=%i" %
                            (newStockDict[oldcode], oldstockid))
            if oldvalid == 0:
                cur.execute("update stock set valid=1, endDate=99999999 where stockid=%i" % oldstockid)

    # 处理新出现的股票
    codepre_list = get_codepre_list(connect, marketid, quotations)

    today = datetime.date.today()
    today = today.year * 10000 + today.month * 100 + today.day
    count = 0
    for code in newStockDict:
        if code not in oldStockDict:
            for codepre in codepre_list:
                length = len(codepre[0])
                if code[:length] == codepre[0]:
                    count += 1
                    #print(market, code, newStockDict[code], codepre)
                    sql = "insert into Stock(marketid, code, name, type, valid, startDate, endDate) \
                           values (%s, '%s', '%s', %s, %s, %s, %s)" \
                          % (marketid, code, newStockDict[code], codepre[1], 1, today, 99999999)
                    cur.execute(sql)
                    break

    #print('%s新增股票数：%i' % (market.upper(), count))
    connect.commit()
    cur.close()


def tdx_import_day_data_from_file(connect, filename, h5file, market, stock_record):
    """

    :param connect:
    :param filename:
    :param h5file:
    :param stock_record: (stockid, marketid, code, valid, type)
    :return:
    """
    add_record_count = 0
    if not os.path.exists(filename):
        return add_record_count

    stockid, marketid, code, valid, stktype = stock_record[0], stock_record[1], stock_record[2], stock_record[3],stock_record[4]

    try:
        group = h5file.get_node("/", "data")
    except:
        group = h5file.create_group("/", "data")

    tablename = market.upper() + code
    try:
        table = h5file.get_node(group, tablename)
    except:
        table = h5file.create_table(group, tablename, H5Record)

    if table.nrows > 0:
        startdate = table[0]['datetime']/10000
        lastdatetime = table[-1]['datetime']/10000
    else:
        startdate = None
        lastdatetime = None

    update_flag = False
    row = table.row
    with open(filename, 'rb') as src_file:
        data = src_file.read(32)
        while data:
            record = struct.unpack('iiiiifii', data)
            if lastdatetime and record[0] <= lastdatetime:
                data = src_file.read(32)
                continue

            if 0 not in record[1:5]:
                if record[2] >= record[1] >= record[3] \
                        and record[2] >= record[4] >= record[3]:
                    row['datetime'] = record[0] * 10000
                    row['openPrice'] = record[1] * 10
                    row['highPrice'] = record[2] * 10
                    row['lowPrice'] = record[3] * 10
                    row['closePrice'] = record[4] * 10
                    row['transAmount'] = round(record[5] * 0.001)
                    if stktype == 2:
                        # 指数
                        row['transCount'] = record[6]
                    else:
                        row['transCount'] = round(record[6] * 0.01)

                    row.append()
                    add_record_count += 1
                    if not update_flag:
                        update_flag = True

            data = src_file.read(32)

    if update_flag:
        table.flush()

    if startdate is not None and valid == 0:
        cur = connect.cursor()
        cur.execute("update stock set valid=1, startdate=%i, enddate=%i where stockid=%i" %
                    (startdate, 99999999, stockid))
        connect.commit()
        cur.close()

    return add_record_count


def tdx_import_min_data_from_file(connect, filename, h5file, market, stock_record):
    add_record_count = 0
    if not os.path.exists(filename):
        return add_record_count

    stockid, marketid, code, valid, stktype = stock_record[0], stock_record[1], stock_record[2], stock_record[3],stock_record[4]

    try:
        group = h5file.get_node("/", "data")
    except:
        group = h5file.create_group("/", "data")

    tablename = market.upper() + code
    try:
        table = h5file.get_node(group, tablename)
    except:
        table = h5file.create_table(group, tablename, H5Record)

    if table.nrows > 0:
        lastdatetime = table[-1]['datetime']
    else:
        lastdatetime = None

    update_flag = False
    row = table.row
    with open(filename, 'rb') as src_file:
        def trans_date(yymm, hhmm):
            tmp_date = yymm >> 11
            remainder = yymm & 0x7ff
            year = tmp_date + 2004
            month = remainder // 100
            day = remainder % 100
            hh = hhmm // 60
            mm = hhmm % 60
            return year * 100000000 + month * 1000000 + day * 10000 + hh * 100 + mm

        def get_date(pos):
            src_file.seek(pos * 32, SEEK_SET)
            data = src_file.read(4)
            a = struct.unpack('hh', data)
            return trans_date(a[0], a[1])

        def find_pos():
            src_file.seek(0, SEEK_END)
            pos = src_file.tell()
            total = pos // 32
            if lastdatetime is None:
                return total, 0

            low, high = 0, total - 1
            mid = high // 2
            while mid <= high:
                cur_date = get_date(low)
                if cur_date > lastdatetime:
                    mid = low
                    break

                cur_date = get_date(high)
                if cur_date <= lastdatetime:
                    mid = high + 1
                    break

                cur_date = get_date(mid)
                if cur_date <= lastdatetime:
                    low = mid + 1
                else:
                    high = mid - 1

                mid = (low + high) // 2

            return total, mid

        file_total, pos = find_pos()
        if pos < file_total:
            src_file.seek(pos * 32, SEEK_SET)

            data = src_file.read(32)
            while data:
                record = struct.unpack('hhfffffii', data)
                if 0 not in record[2:6]:
                    if record[3] >= record[2] >= record[4] \
                            and record[3] >= record[5] >= record[4]:
                        row['datetime'] = trans_date(record[0], record[1])
                        row['openPrice'] = record[2] * 1000
                        row['highPrice'] = record[3] * 1000
                        row['lowPrice'] = record[4] * 1000
                        row['closePrice'] = record[5] * 1000
                        row['transAmount'] = round(record[6] * 0.001)
                        if stktype == 2:
                            # 指数
                            row['transCount'] = record[7]
                        else:
                            row['transCount'] = round(record[6] * 0.01)

                        row.append()
                        add_record_count += 1
                        if not update_flag:
                            update_flag = True

                data = src_file.read(32)

    if update_flag:
        table.flush()

    return add_record_count

def tdx_import_data(connect, market, ktype, quotations, src_dir, dest_dir, progress=ProgressBar):
    """
    导入通达信日线数据，只导入基础信息数据库中存在的股票
    """

    add_record_count = 0
    market = market.upper()
    filename = "{}_{}.h5".format(market, ktype)
    filename = "{}/{}".format(dest_dir, filename.lower())
    h5file = tb.open_file(filename, "a", filters=tb.Filters(complevel=HDF5_COMPRESS_LEVEL, complib='zlib', shuffle=True))

    if ktype.upper() == "DAY":
        suffix = ".day"
        func_import_from_file = tdx_import_day_data_from_file
    elif ktype.upper() == "1MIN":
        suffix = ".lc1"
        func_import_from_file = tdx_import_min_data_from_file
    elif ktype.upper() == "5MIN":
        suffix = ".lc5"
        func_import_from_file = tdx_import_min_data_from_file

    marketid = get_marketid(connect, market)
    stktype_list = get_stktype_list(quotations)
    sql = "select stockid, marketid, code, valid, type from stock where marketid={} and type in {}".format(marketid, stktype_list)

    cur = connect.cursor()
    a = cur.execute(sql)
    a = a.fetchall()

    total = len(a)
    for i, stock in enumerate(a):
        filename = src_dir + "\\" + market.lower() + stock[2]+ suffix
        #print(i,filename)
        this_count = func_import_from_file(connect, filename, h5file, market, stock)
        add_record_count += this_count
        if this_count > 0:
            if ktype == 'DAY':
                update_hdf5_extern_data(h5file, market.upper() + stock[2], 'DAY')
            elif ktype == '5MIN':
                update_hdf5_extern_data(h5file, market.upper() + stock[2], '5MIN')
        if progress:
            progress(i, total)

    connect.commit()
    h5file.close()
    return add_record_count


def update_hdf5_extern_data(h5file, tablename, data_type):
    
    def getWeekDate(olddate):
        y = olddate//100000000
        m = olddate//1000000 - y*100
        d = olddate//10000 - (y*10000+m*100)
        tempdate = datetime.date(y,m,d)
        #python中周一是第0天，周五的第4天
        tempweekdate = tempdate + datetime.timedelta(4-tempdate.weekday())
        newdate = tempweekdate.year*100000000 + tempweekdate.month*1000000 + tempweekdate.day*10000
        return newdate

    def getMonthDate(olddate):
        y = olddate//100000000
        m = olddate//1000000 - y*100
        import calendar
        _, d = calendar.monthrange(y, m)
        return(y*100000000 + m*1000000 + d*10000)

    def getQuarterDate(olddate):
        quarterDict={1:3,2:3,3:3,4:6,5:6,6:6,7:9,8:9,9:9,10:12,11:12,12:12}
        d_dict = {3:310000, 6:300000, 9:300000, 12:310000}
        y = olddate//100000000
        m = olddate//1000000 - y*100
        new_m = quarterDict[m]
        return( y*100000000 + new_m*1000000 + d_dict[new_m])
    
    def getHalfyearDate(olddate):
        y = olddate//100000000
        m = olddate//1000000 - y*100
        return y*100000000 + (6300000 if m < 7 else 12310000)
    
    def getYearDate(olddate):
        y = olddate//100000000
        return(y*100000000 + 12310000)

    def getMin60Date(olddate):
        mint = olddate-olddate//10000*10000
        if mint<=1030:
            newdate = olddate//10000*10000 + 1030
        elif mint<=1130:
            newdate = olddate//10000*10000 + 1130
        elif mint<=1400:
            newdate = olddate//10000*10000 + 1400
        else:
            newdate = olddate//10000*10000 + 1500
        return newdate
    
    def getMin15Date(olddate):
        mint = olddate-olddate//10000*10000
        if mint<=945:
            newdate = olddate//10000*10000 + 945
        elif mint<=1000:
            newdate = olddate//10000*10000 + 1000
        elif mint<=1015:
            newdate = olddate//10000*10000 + 1015
        elif mint<=1030:
            newdate = olddate//10000*10000 + 1030
        elif mint<=1045:
            newdate = olddate//10000*10000 + 1045
        elif mint<=1100:
            newdate = olddate//10000*10000 + 1100
        elif mint<=1115:
            newdate = olddate//10000*10000 + 1115
        elif mint<=1130:
            newdate = olddate//10000*10000 + 1130
        elif mint<=1315:
            newdate = olddate//10000*10000 + 1315
        elif mint<=1330:
            newdate = olddate//10000*10000 + 1330
        elif mint<=1345:
            newdate = olddate//10000*10000 + 1345
        elif mint<=1400:
            newdate = olddate//10000*10000 + 1400
        elif mint<=1415:
            newdate = olddate//10000*10000 + 1415
        elif mint<=1430:
            newdate = olddate//10000*10000 + 1430
        elif mint<=1445:
            newdate = olddate//10000*10000 + 1445
        else:
            newdate = olddate//10000*10000 + 1500
        return newdate    
    
    def getMin30Date(olddate):
        mint = olddate-olddate//10000*10000
        if mint<=1000:
            newdate = olddate//10000*10000 + 1000
        elif mint<=1030:
            newdate = olddate//10000*10000 + 1030
        elif mint<=1100:
            newdate = olddate//10000*10000 + 1100
        elif mint<=1130:
            newdate = olddate//10000*10000 + 1130
        elif mint<=1330:
            newdate = olddate//10000*10000 + 1330
        elif mint<=1400:
            newdate = olddate//10000*10000 + 1400
        elif mint<=1430:
            newdate = olddate//10000*10000 + 1430
        else:
            newdate = olddate//10000*10000 + 1500
        return newdate    
    
    def getNewDate(index_type, olddate):
        if index_type == 'week':
            return getWeekDate(olddate)
        elif index_type == 'month':
            return getMonthDate(olddate)
        elif index_type == 'quarter':
            return getQuarterDate(olddate)
        elif index_type == 'halfyear':
            return getHalfyearDate(olddate)
        elif index_type == 'year':
            return getYearDate(olddate)
        elif index_type == 'min15':
            return getMin15Date(olddate)
        elif index_type == 'min30':
            return getMin30Date(olddate)
        elif index_type == 'min60':
            return getMin60Date(olddate)
        else:
            return None
    
    if data_type == 'DAY':
        index_list = ('week', 'month', 'quarter', 'halfyear', 'year')
    else:
        index_list = ('min15', 'min30', 'min60')

    groupDict = {}
    for index_type in index_list:
        try:
            groupDict[index_type] = h5file.get_node("/", index_type)
        except:
            groupDict[index_type] = h5file.create_group("/", index_type)

    try:
        table = h5file.get_node("/data", tablename)
    except:
        return

    for index_type in index_list:
        try:
            index_table = h5file.get_node(groupDict[index_type],tablename)
        except:
            index_table = h5file.create_table(groupDict[index_type],tablename, H5Index)

        total = table.nrows
        if 0 == total:
            continue

        index_total = index_table.nrows
        index_row = index_table.row
        if index_total:
            index_last_date = int(index_table[-1]['datetime'])
            last_date = getNewDate(index_type, int(table[-1]['datetime']))
            if index_last_date == last_date:
                continue
            startix = int(index_table[-1]['start'])
            pre_index_date = int(index_table[-1]['datetime'])
        else:
            startix = 0
            date = int(table[0]['datetime'])
            pre_index_date = getNewDate(index_type,date)
            index_row['datetime'] = pre_index_date
            index_row['start'] = 0
            index_row.append()

        index = startix
        for row in table[startix:]:
            date = int(row['datetime'])
            cur_index_date = getNewDate(index_type, date)
            if cur_index_date != pre_index_date:
                index_row['datetime'] = cur_index_date
                index_row['start'] = index
                index_row.append()
                pre_index_date = cur_index_date
            index += 1
        index_table.flush()


def qianlong_import_weight(connect, src_dir, market):
    """导入钱龙格式的权息数据"""
    cur = connect.cursor()
    marketid = cur.execute("select marketid from Market where market='%s'" % market)
    marketid = [id[0] for id in marketid]
    marketid = marketid[0]

    src_path = pathlib.Path(src_dir + '/shase/weight') if market == 'SH' else pathlib.Path(src_dir + '/sznse/weight')
    wgt_file_list = list(src_path.glob('*.wgt'))

    total_count = 0
    for wgt_file in wgt_file_list:
        code = wgt_file.stem
        stockid = cur.execute("select stockid from Stock where marketid=%s and code='%s'" % (marketid, code))
        stockid = [id[0] for id in stockid]
        if not stockid:
            continue

        with wgt_file.open('rb') as sourcefile:
            stockid = stockid[0]
            a = cur.execute("select date from stkweight where stockid=%s" % stockid)
            dateDict = dict([(i[0], None) for i in a])

            records = []
            data = sourcefile.read(36)
            while data:
                a = struct.unpack('iiiiiiiii', data)
                date = (a[0] >> 20) * 10000 + (((a[0] << 12) & 4294967295) >> 28) * 100 + ((a[0] & 0xffff) >> 11)
                if date not in dateDict:
                    records.append((stockid, date, a[1], a[2], a[3], a[4], a[5], a[6], a[7]))
                data = sourcefile.read(36)
            sourcefile.close()

            if records:
                cur.executemany("INSERT INTO StkWeight(stockid, date, countAsGift, \
                                 countForSell, priceForSell, bonus, countOfIncreasement, totalCount, freeCount) \
                                 VALUES (?,?,?,?,?,?,?,?,?)",
                                records)
                total_count += len(records)

    connect.commit()
    cur.close()
    return total_count


if __name__ == '__main__':
    
    import time
    starttime = time.time()
    
    src_dir = "D:\\TdxW_HuaTai"
    dest_dir = "c:\\stock"
    
    connect = sqlite3.connect(dest_dir + "\\stock.db")
    create_database(connect)

    print("导入股票代码表")
    tdx_import_stock_name_from_file(connect, src_dir + "\\T0002\\hq_cache\\shm.tnf", 'SH', ['stock', 'fund'])
    tdx_import_stock_name_from_file(connect, src_dir + "\\T0002\\hq_cache\\szm.tnf", 'SZ', ['stock', 'fund'])

    print("\n导入上证日线数据")
    add_count = 0
    add_count = tdx_import_data(connect, 'SH', 'DAY', ['stock', 'fund'], src_dir + "\\vipdoc\\sh\\lday", dest_dir)
    #add_count = tdx_import_data(connect, 'SZ', 'DAY', 'stock', src_dir + "\\vipdoc\\sz\\lday", dest_dir)
    print("\n导入数量：", add_count)

    print("\n导入上证5分钟数据")
    #add_count = tdx_import_data(connect, 'SH', '5MIN', 'stock', src_dir + "\\vipdoc\\sh\\fzline", dest_dir)
    print("\n导入数量：", add_count)

    print("\n导入上证1分钟数据")
    #add_count = tdx_import_data(connect, 'SH', '1MIN', 'stock', src_dir + "\\vipdoc\\sh\\minline", dest_dir)
    print("\n导入数量：", add_count)

    print("\n导入权息数据")
    total_count = 0
    #total_count = qianlong_import_weight(connect, r'C:\stock\weight', 'SH')
    #total_count += qianlong_import_weight(connect, r'C:\stock\weight', 'SZ')
    print(total_count)

    connect.close()
    
    endtime = time.time()
    print("\nTotal time:")
    print("%.2fs" % (endtime-starttime))
    print("%.2fm" % ((endtime-starttime)/60))