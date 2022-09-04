/*
 * PositionRecord.h
 *
 *  Created on: 2013-2-21
 *      Author: fasiondog
 */

#pragma once
#ifndef POSITIONRECORD_H_
#define POSITIONRECORD_H_

#include "TradeRecord.h"

#if HKU_SUPPORT_SERIALIZATION
#include <boost/serialization/split_member.hpp>
#endif

namespace hku {

/**
 * 持仓记录
 * @ingroup TradeManagerClass
 */
class HKU_API PositionRecord {
public:
    PositionRecord() = default;
    PositionRecord(const Stock& stock, const Datetime& takeDatetime, const Datetime& cleanDatetime,
                   double number, price_t stoploss, price_t goalPrice, price_t buyMoney,
                   price_t totalCost, price_t totalRisk, price_t sellMoney);

    /** 仅用于python的__str__ */
    string toString() const;

    void addTradeRecord(const TradeRecord& tr);

    Stock stock;              ///< 交易对象
    Datetime takeDatetime;    ///< 初次建仓日期
    Datetime cleanDatetime;   ///< 平仓日期，当前持仓记录中为Null<Datetime>()
    double number = 0.0;      ///< 当前持仓数量
    price_t stoploss = 0.0;   ///< 当前止损价
    price_t goalPrice = 0.0;  ///< 当前的目标价格
    price_t buyMoney = 0.0;   ///< 累计买入资金
    price_t totalCost = 0.0;  ///< 累计交易总成本
    price_t totalRisk = 0.0;  ///< 累计交易风险 = 各次 （买入价格-止损)*买入数量, 不包含交易成本
    price_t sellMoney = 0.0;  ///< 累计卖出资金

private:
    bool m_isShort = false;           // 是否空头仓位
    std::list<TradeRecord> m_trList;  // 记录对应买卖交易记录

//===================
//序列化支持
//===================
#if HKU_SUPPORT_SERIALIZATION
private:
    friend class boost::serialization::access;
    template <class Archive>
    void save(Archive& ar, const unsigned int version) const {
        namespace bs = boost::serialization;
        ar& BOOST_SERIALIZATION_NVP(stock);
        uint64_t take = takeDatetime.number();
        uint64_t clean = cleanDatetime.number();
        ar& bs::make_nvp("takeDatetime", take);
        ar& bs::make_nvp("cleanDatetime", clean);
        ar& BOOST_SERIALIZATION_NVP(number);
        ar& BOOST_SERIALIZATION_NVP(stoploss);
        ar& BOOST_SERIALIZATION_NVP(goalPrice);
        ar& BOOST_SERIALIZATION_NVP(buyMoney);
        ar& BOOST_SERIALIZATION_NVP(totalCost);
        ar& BOOST_SERIALIZATION_NVP(totalRisk);
        ar& BOOST_SERIALIZATION_NVP(sellMoney);
    }

    template <class Archive>
    void load(Archive& ar, const unsigned int version) {
        namespace bs = boost::serialization;
        ar& BOOST_SERIALIZATION_NVP(stock);
        uint64_t take, clean;
        ar& bs::make_nvp("takeDatetime", take);
        ar& bs::make_nvp("cleanDatetime", clean);
        takeDatetime = Datetime(take);
        cleanDatetime = Datetime(clean);
        ar& BOOST_SERIALIZATION_NVP(number);
        ar& BOOST_SERIALIZATION_NVP(stoploss);
        ar& BOOST_SERIALIZATION_NVP(goalPrice);
        ar& BOOST_SERIALIZATION_NVP(buyMoney);
        ar& BOOST_SERIALIZATION_NVP(totalCost);
        ar& BOOST_SERIALIZATION_NVP(totalRisk);
        ar& BOOST_SERIALIZATION_NVP(sellMoney);
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()
#endif /* HKU_SUPPORT_SERIALIZATION */
};

/** @ingroup TradeManagerClass */
typedef vector<PositionRecord> PositionRecordList;

/**
 * 输出持仓记录信息
 * @ingroup TradeManagerClass
 */
HKU_API std::ostream& operator<<(std::ostream&, const PositionRecord&);

bool HKU_API operator==(const PositionRecord& d1, const PositionRecord& d2);

} /* namespace hku */
#endif /* POSITIONRECORD_H_ */
