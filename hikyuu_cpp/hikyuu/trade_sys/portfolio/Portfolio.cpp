/*
 * Portfolio.cpp
 *
 *  Created on: 2016年2月21日
 *      Author: fasiondog
 */

#include <boost/bind.hpp>
#include "../../trade_manage/crt/crtTM.h"

#include "Portfolio.h"

namespace hku {

HKU_API std::ostream& operator<<(std::ostream& os, const Portfolio& pf) {
    os << "Portfolio(" << pf.name() << ", " << pf.getParameter() << ")";
    return os;
}

HKU_API std::ostream& operator<<(std::ostream& os, const PortfolioPtr& pf) {
    if (pf) {
        os << *pf;
    } else {
        os << "Portfolio(NULL)";
    }

    return os;
}

Portfolio::Portfolio() : m_name("Portfolio"), m_is_ready(false) {
    setParam<bool>("trace", false);  // 打印跟踪
}

Portfolio::Portfolio(const string& name) : m_name(name), m_is_ready(false) {
    setParam<bool>("trace", false);
}

Portfolio::Portfolio(const TradeManagerPtr& tm, const SelectorPtr& se, const AFPtr& af)
: m_name("Portfolio"), m_tm(tm), m_se(se), m_af(af), m_is_ready(false) {
    setParam<bool>("trace", false);
}

Portfolio::~Portfolio() {}

void Portfolio::reset() {
    m_is_ready = false;
    m_pro_sys_list.clear();
    m_real_sys_list.clear();
    m_running_sys_set.clear();
    m_running_sys_list.clear();
    m_tmp_cur_selected_list.clear();
    m_tmp_will_remove_sys.clear();
    if (m_tm)
        m_tm->reset();
    if (m_shadow_tm)
        m_shadow_tm->reset();
    if (m_se)
        m_se->reset();
    if (m_af)
        m_af->reset();
}

PortfolioPtr Portfolio::clone() {
    PortfolioPtr p = make_shared<Portfolio>();
    p->m_params = m_params;
    p->m_name = m_name;
    p->m_query = m_query;
    p->m_pro_sys_list = m_pro_sys_list;
    p->m_real_sys_list = m_real_sys_list;
    p->m_running_sys_set = m_running_sys_set;
    p->m_running_sys_list = m_running_sys_list;
    p->m_is_ready = m_is_ready;
    if (m_se)
        p->m_se = m_se->clone();
    if (m_af)
        p->m_af = m_af->clone();
    if (m_tm)
        p->m_tm = m_tm->clone();
    if (m_shadow_tm)
        p->m_shadow_tm = m_shadow_tm->clone();
    return p;
}

bool Portfolio::readyForRun() {
    SPEND_TIME(Portfolio_readyForRun);
    if (!m_se) {
        HKU_WARN("m_se is null!");
        m_is_ready = false;
        return false;
    }

    if (!m_tm) {
        HKU_WARN("m_tm is null!");
        m_is_ready = false;
        return false;
    }

    if (!m_af) {
        HKU_WARN("m_am is null!");
        m_is_ready = false;
        return false;
    }

    reset();

    // 将影子账户指定给资产分配器
    m_shadow_tm = m_tm->clone();
    m_af->setTM(m_tm);
    m_af->setShadowTM(m_shadow_tm);

    // 为资金分配器设置关联查询条件
    m_af->setQuery(m_query);

    // 从 se 获取原型系统列表
    m_pro_sys_list = m_se->getProtoSystemList();

    // 获取所有备选子系统，为无关联账户的子系统分配子账号，对所有子系统做好启动准备
    TMPtr pro_tm = crtTM(m_tm->initDatetime(), 0.0, m_tm->costFunc(), "TM_SUB");
    size_t total = m_pro_sys_list.size();
    for (size_t i = 0; i < total; i++) {
        SystemPtr& pro_sys = m_pro_sys_list[i];
        SystemPtr sys = pro_sys->clone();
        m_real_sys_list.emplace_back(sys);

        // 如果原型子系统没有关联账户，则为其创建一个和总资金金额相同的账户，以便能够运行
        if (!pro_sys->getTM()) {
            pro_sys->setTM(m_tm->clone());
        }

        // 为内部实际执行的系统创建初始资金为0的子账户
        sys->setTM(pro_tm->clone());
        sys->getTM()->name(fmt::format("TM_SUB{}", i));
        sys->name(fmt::format("PF_Real_{}_{}", i, sys->name()));

        if (sys->readyForRun() && pro_sys->readyForRun()) {
            KData k = sys->getStock().getKData(m_query);
            sys->setTO(k);
            pro_sys->setTO(k);
        } else {
            HKU_THROW("Exist invalid system, it could not ready for run!");
        }
    }

    // 告知 se 当前实际运行的系统列表
    m_se->calculate(m_real_sys_list, m_query);

    m_is_ready = true;
    return true;
}

void Portfolio::runMoment(const Datetime& date) {
    HKU_CHECK(isReady(), "Not ready to run! Please perform readyForRun() first!");

    // 当前日期小于账户建立日期，直接忽略
    HKU_IF_RETURN(date < m_shadow_tm->initDatetime(), void());

    if (getParam<bool>("trace")) {
        HKU_INFO("========================================================================");
        HKU_INFO("{}", date);
    }

    // 从选股策略获取当前选中的系统列表
    m_tmp_cur_selected_list = m_se->getSelectedSystemList(date);
    if (getParam<bool>("trace")) {
        for (auto& sys : m_tmp_cur_selected_list) {
            HKU_INFO("select: {}, cash: {}", sys->getTO().getStock(), sys->getTM()->currentCash());
        }
    }

    // 资产分配算法调整各子系统资产分配
    m_af->adjustFunds(date, m_tmp_cur_selected_list, m_running_sys_list);
    if (getParam<bool>("trace")) {
        for (auto& sys : m_tmp_cur_selected_list) {
            HKU_INFO("allocate --> select: {}, cash: {}", sys->getTO().getStock(),
                     sys->getTM()->currentCash());
        }
    }

    // 由于系统的交易指令可能被延迟执行，需要保存并判断
    // 遍历当前运行中的子系统，如果已没有分配资金和持仓，则放入待移除列表
    m_tmp_will_remove_sys.clear();
    int precision = m_shadow_tm->getParam<int>("precision");
    for (auto& running_sys : m_running_sys_list) {
        Stock stock = running_sys->getStock();
        TMPtr sub_tm = running_sys->getTM();
        PositionRecord position = sub_tm->getPosition(stock);
        price_t cash = sub_tm->currentCash();

        // 已没有持仓且没有现金，则放入待移除列表
        if (position.number == 0 && cash <= precision) {
            if (cash != 0) {
                sub_tm->checkout(date, cash);
                m_shadow_tm->checkin(date, cash);
            }
            m_tmp_will_remove_sys.push_back(running_sys);
        }
    }

    // 依据待移除列表将系统从运行中系统列表里删除
    for (auto& sub_sys : m_tmp_will_remove_sys) {
        m_running_sys_list.remove(sub_sys);
        m_running_sys_set.erase(sub_sys);
    }

    // 遍历本次选择的系统列表，如果存在分配资金且不在运行中列表内，则加入运行列表
    for (auto& sub_sys : m_tmp_cur_selected_list) {
        price_t cash = sub_sys->getTM()->currentCash();
        if (cash > 0 && m_running_sys_set.find(sub_sys) == m_running_sys_set.end()) {
            m_running_sys_list.push_back(sub_sys);
            m_running_sys_set.insert(sub_sys);
        }
    }

    // 执行所有运行中的系统
    for (auto& sub_sys : m_running_sys_list) {
        auto tr = sub_sys->runMoment(date);
        if (!tr.isNull()) {
            m_tm->addTradeRecord(tr);
        }
    }
}

void Portfolio::run(const KQuery& query) {
    HKU_CHECK(readyForRun(),
              "readyForRun fails, check to see if a valid TradeManager, Selector, or "
              "AllocateFunds instance have been specified.");

    DatetimeList datelist = StockManager::instance().getTradingCalendar(query);
    for (auto& date : datelist) {
        runMoment(date);
    }
}

FundsRecord Portfolio::getFunds(KQuery::KType ktype) const {
    FundsRecord total_funds;
    for (auto& sub_sys : m_running_sys_list) {
        FundsRecord funds = sub_sys->getTM()->getFunds(ktype);
        total_funds += funds;
    }
    total_funds.cash += m_shadow_tm->currentCash();
    return total_funds;
}

FundsRecord Portfolio::getFunds(const Datetime& datetime, KQuery::KType ktype) {
    FundsRecord total_funds;
    for (auto& sub_sys : m_real_sys_list) {
        FundsRecord funds = sub_sys->getTM()->getFunds(datetime, ktype);
        total_funds += funds;
    }
    total_funds.cash += m_shadow_tm->cash(datetime, ktype);
    return total_funds;
}

PriceList Portfolio::getFundsCurve(const DatetimeList& dates, KQuery::KType ktype) {
    size_t total = dates.size();
    PriceList result(total);
    for (auto& sub_sys : m_real_sys_list) {
        auto curve = sub_sys->getTM()->getFundsCurve(dates, ktype);
        for (auto i = 0; i < total; i++) {
            result[i] += curve[i];
        }
    }
    return result;
}

PriceList Portfolio::getFundsCurve() {
    DatetimeList dates = getDateRange(m_shadow_tm->initDatetime(), Datetime::now());
    return getFundsCurve(dates, KQuery::DAY);
}

PriceList Portfolio::getProfitCurve(const DatetimeList& dates, KQuery::KType ktype) {
    size_t total = dates.size();
    PriceList result(total);
    for (auto& sub_sys : m_real_sys_list) {
        auto curve = sub_sys->getTM()->getProfitCurve(dates, ktype);
        for (auto i = 0; i < total; i++) {
            result[i] += curve[i];
        }
    }
    return result;
}

PriceList Portfolio::getProfitCurve() {
    DatetimeList dates = getDateRange(m_shadow_tm->initDatetime(), Datetime::now());
    return getProfitCurve(dates, KQuery::DAY);
}

} /* namespace hku */
