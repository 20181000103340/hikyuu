#!/usr/bin/python
# -*- coding: utf8 -*-

from hikyuu import *
import matplotlib.pyplot as plt

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
        return h, L

if __name__ == "__main__":
    sg = TurtleSignal()
    s = get_stock("sh000001")
    k = s.get_kdata(Query(-200))  # 取最近200天的数据

    # 计算信号
    sg.to = k
    h, L = sg._calculate(k)
    
    # 准备绘图数据
    dates = k.get_datetime_list()
    closes = [x.close for x in k]
    highs = h
    lows = L
    
    # 创建图表
    plt.figure(figsize=(15,8))
    plt.title("海龟交易系统信号 - 上证指数")
    
    # 绘制K线和通道
    plt.plot(range(len(k)), closes, 'black', label='收盘价', linewidth=1)
    plt.plot(range(len(k)), highs, 'r--', label='上轨', linewidth=1)
    plt.plot(range(len(k)), lows, 'g--', label='下轨', linewidth=1)
    
    # 标记买卖点
    buy_dates = []
    sell_dates = []
    for i, d in enumerate(dates):
        if (sg.should_buy(d)):
            buy_dates.append(i)
            plt.plot(i, closes[i], '^r', markersize=10)
        elif (sg.should_sell(d)):
            sell_dates.append(i)
            plt.plot(i, closes[i], 'vg', markersize=10)
    
    # 设置x轴标签
    plt.xticks(range(0, len(k), 20), 
               [str(dates[i]) for i in range(0, len(k), 20)],
               rotation=45)
    
    plt.grid(True)
    plt.legend()
    plt.show()

    # 打印交易信号
    print("\n==========海龟交易信号==========")
    print("测试周期：上证指数近200日数据")
    print("策略参数：n = 20 (20日突破)\n")
    print("买入信号：")
    for i in buy_dates:
        print(dates[i], "价格:", closes[i])
    print("\n卖出信号：")
    for i in sell_dates:
        print(dates[i], "价格:", closes[i])
