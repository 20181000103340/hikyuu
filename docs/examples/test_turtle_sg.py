#!/usr/bin/python
# -*- coding: utf8 -*-

from hikyuu import *

# 使用测试数据初始化
config_file = './test_data/hikyuu_linux.ini'
hikyuu_init(config_file)

class TurtleSignal(SignalBase):
    def __init__(self, n=20):
        super(TurtleSignal, self).__init__("TurtleSignal")
        self.set_param("n", 20)

    def _clone(self):
        return TurtleSignal()

    def _calculate(self, k):
        n = self.get_param("n")
        c = CLOSE(k)
        h = REF(HHV(c, n), 1)  # 前n日高点
        L = REF(LLV(c, n), 1)  # 前n日低点
        for i in range(h.discard, len(k)):
            if (c[i] >= h[i]):
                self._add_buy_signal(k[i].datetime)
            elif (c[i] <= L[i]):
                self._add_sell_signal(k[i].datetime)

if __name__ == "__main__":
    sg = TurtleSignal()
    s = get_stock("sh000001")
    k = s.get_kdata(Query(-500))

    print("\n==========运行海龟交易策略示例==========")
    print("测试周期：上证指数近500日数据")
    print("策略参数：n = 20 (20日突破)\n")

    # 只有设置交易对象时，才会开始实际计算
    sg.to = k
    dates = k.get_datetime_list()
    for d in dates:
        if (sg.should_buy(d)):
            print("买入信号：%s" % d)
        elif (sg.should_sell(d)):
            print("卖出信号：%s" % d)
