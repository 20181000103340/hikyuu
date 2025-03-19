from hikyuu import *

# 使用测试数据
config_file = './test_data/hikyuu_linux.ini'
hikyuu_init(config_file)

# 获取上证指数
s = get_stock("sh000001")
k = s.get_kdata(Query(-10))  # 获取最后10条K线数据

print("\n上证指数最后10条K线数据：")
for i in range(len(k)):
    print(k[i].datetime, "开盘价:", k[i].open, "最高价:", k[i].high,
          "最低价:", k[i].low, "收盘价:", k[i].close)
