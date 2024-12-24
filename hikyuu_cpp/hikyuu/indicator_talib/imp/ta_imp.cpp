/*
 *  Copyright (c) 2024 hikyuu.org
 *
 *  Created on: 2024-12-20
 *      Author: fasiondog
 */

#include "ta_func.h"
#include "ta_defines.h"
#include "ta_imp.h"
#include "hikyuu/indicator/crt/ALIGN.h"

#if HKU_SUPPORT_SERIALIZATION
EXPOERT_TA_FUNC(TA_ACCBANDS)
EXPOERT_TA_FUNC(TA_ACOS)
EXPOERT_TA_FUNC(TA_AD)
EXPOERT_TA_FUNC(TA_ADD)
// TA_ADOSC
EXPOERT_TA_FUNC(TA_ADX)
EXPOERT_TA_FUNC(TA_ADXR)
// TA_APO
EXPOERT_TA_FUNC(TA_AROON)
EXPOERT_TA_FUNC(TA_AROONOSC)
EXPOERT_TA_FUNC(TA_ASIN)
EXPOERT_TA_FUNC(TA_ATAN)
EXPOERT_TA_FUNC(TA_ATR)
EXPOERT_TA_FUNC(TA_AVGDEV)
EXPOERT_TA_FUNC(TA_AVGPRICE)
// TA_BBANDS
EXPOERT_TA_FUNC(TA_BETA)
EXPOERT_TA_FUNC(TA_BOP)
EXPOERT_TA_FUNC(TA_CCI)
EXPOERT_TA_FUNC(TA_CDL2CROWS)
EXPOERT_TA_FUNC(TA_CDL3BLACKCROWS)
EXPOERT_TA_FUNC(TA_CDL3INSIDE)
EXPOERT_TA_FUNC(TA_CDL3LINESTRIKE)
EXPOERT_TA_FUNC(TA_CDL3OUTSIDE)
EXPOERT_TA_FUNC(TA_CDL3STARSINSOUTH)
EXPOERT_TA_FUNC(TA_CDL3WHITESOLDIERS)
EXPOERT_TA_FUNC(TA_CDLABANDONEDBABY)
EXPOERT_TA_FUNC(TA_CDLADVANCEBLOCK)
EXPOERT_TA_FUNC(TA_CDLBELTHOLD)
EXPOERT_TA_FUNC(TA_CDLBREAKAWAY)
EXPOERT_TA_FUNC(TA_CDLCLOSINGMARUBOZU)
EXPOERT_TA_FUNC(TA_CDLCONCEALBABYSWALL)
EXPOERT_TA_FUNC(TA_CDLCOUNTERATTACK)
EXPOERT_TA_FUNC(TA_CDLDARKCLOUDCOVER)
EXPOERT_TA_FUNC(TA_CDLDOJI)
EXPOERT_TA_FUNC(TA_CDLDOJISTAR)
EXPOERT_TA_FUNC(TA_CDLDRAGONFLYDOJI)
EXPOERT_TA_FUNC(TA_CDLENGULFING)
EXPOERT_TA_FUNC(TA_CDLEVENINGDOJISTAR)
EXPOERT_TA_FUNC(TA_CDLGAPSIDESIDEWHITE)
EXPOERT_TA_FUNC(TA_CDLGRAVESTONEDOJI)
EXPOERT_TA_FUNC(TA_CDLHAMMER)
EXPOERT_TA_FUNC(TA_CDLHANGINGMAN)
EXPOERT_TA_FUNC(TA_CDLHARAMI)
EXPOERT_TA_FUNC(TA_CDLHARAMICROSS)
EXPOERT_TA_FUNC(TA_CDLHIGHWAVE)
EXPOERT_TA_FUNC(TA_CDLHIKKAKE)
EXPOERT_TA_FUNC(TA_CDLHIKKAKEMOD)
EXPOERT_TA_FUNC(TA_CDLHOMINGPIGEON)
EXPOERT_TA_FUNC(TA_CDLIDENTICAL3CROWS)
EXPOERT_TA_FUNC(TA_CDLINNECK)
EXPOERT_TA_FUNC(TA_CDLINVERTEDHAMMER)
EXPOERT_TA_FUNC(TA_CDLKICKING)
EXPOERT_TA_FUNC(TA_CDLKICKINGBYLENGTH)
EXPOERT_TA_FUNC(TA_CDLLADDERBOTTOM)
EXPOERT_TA_FUNC(TA_CDLLONGLEGGEDDOJI)
EXPOERT_TA_FUNC(TA_CDLLONGLINE)
EXPOERT_TA_FUNC(TA_CDLMARUBOZU)
EXPOERT_TA_FUNC(TA_CDLMATCHINGLOW)
EXPOERT_TA_FUNC(TA_CDLMATHOLD)
EXPOERT_TA_FUNC(TA_CDLMORNINGDOJISTAR)
EXPOERT_TA_FUNC(TA_CDLMORNINGSTAR)
EXPOERT_TA_FUNC(TA_CDLONNECK)
EXPOERT_TA_FUNC(TA_CDLPIERCING)
EXPOERT_TA_FUNC(TA_CDLRICKSHAWMAN)
EXPOERT_TA_FUNC(TA_CDLRISEFALL3METHODS)
EXPOERT_TA_FUNC(TA_CDLSEPARATINGLINES)
EXPOERT_TA_FUNC(TA_CDLSHOOTINGSTAR)
EXPOERT_TA_FUNC(TA_CDLSHORTLINE)
EXPOERT_TA_FUNC(TA_CDLSPINNINGTOP)
EXPOERT_TA_FUNC(TA_CDLSTALLEDPATTERN)
EXPOERT_TA_FUNC(TA_CDLSTICKSANDWICH)
EXPOERT_TA_FUNC(TA_CDLTAKURI)
EXPOERT_TA_FUNC(TA_CDLTASUKIGAP)
EXPOERT_TA_FUNC(TA_CDLTHRUSTING)
EXPOERT_TA_FUNC(TA_CDLTRISTAR)
EXPOERT_TA_FUNC(TA_CDLUNIQUE3RIVER)
EXPOERT_TA_FUNC(TA_CDLUPSIDEGAP2CROWS)
EXPOERT_TA_FUNC(TA_CDLXSIDEGAP3METHODS)
EXPOERT_TA_FUNC(TA_CEIL)
EXPOERT_TA_FUNC(TA_CMO)
EXPOERT_TA_FUNC(TA_CORREL)
EXPOERT_TA_FUNC(TA_COS)
EXPOERT_TA_FUNC(TA_COSH)
EXPOERT_TA_FUNC(TA_DEMA)
EXPOERT_TA_FUNC(TA_DIV)
EXPOERT_TA_FUNC(TA_DX)
EXPOERT_TA_FUNC(TA_EMA)
EXPOERT_TA_FUNC(TA_EXP)
EXPOERT_TA_FUNC(TA_FLOOR)
EXPOERT_TA_FUNC(TA_HT_DCPERIOD)
EXPOERT_TA_FUNC(TA_HT_DCPHASE)
EXPOERT_TA_FUNC(TA_HT_PHASOR)
EXPOERT_TA_FUNC(TA_HT_SINE)
EXPOERT_TA_FUNC(TA_HT_TRENDLINE)
EXPOERT_TA_FUNC(TA_HT_TRENDMODE)
EXPOERT_TA_FUNC(TA_IMI)
EXPOERT_TA_FUNC(TA_KAMA)
EXPOERT_TA_FUNC(TA_LINEARREG_ANGLE)
EXPOERT_TA_FUNC(TA_LINEARREG_INTERCEPT)
EXPOERT_TA_FUNC(TA_LINEARREG_SLOPE)
EXPOERT_TA_FUNC(TA_LINEARREG)
EXPOERT_TA_FUNC(TA_LN)
EXPOERT_TA_FUNC(TA_LOG10)
// TA_MA
// TA_MACD
// TA_MACDEXT
EXPOERT_TA_FUNC(TA_MACDFIX)
// TA_MAMA
// TA_MAVP
EXPOERT_TA_FUNC(TA_MAX)
EXPOERT_TA_FUNC(TA_MAXINDEX)
EXPOERT_TA_FUNC(TA_MEDPRICE)
EXPOERT_TA_FUNC(TA_MFI)
EXPOERT_TA_FUNC(TA_MIDPOINT)
EXPOERT_TA_FUNC(TA_MIDPRICE)
EXPOERT_TA_FUNC(TA_MIN)
EXPOERT_TA_FUNC(TA_MININDEX)
EXPOERT_TA_FUNC(TA_MINMAX)
EXPOERT_TA_FUNC(TA_MINMAXINDEX)
EXPOERT_TA_FUNC(TA_MINUS_DI)
EXPOERT_TA_FUNC(TA_MINUS_DM)
EXPOERT_TA_FUNC(TA_MOM)
EXPOERT_TA_FUNC(TA_MULT)
EXPOERT_TA_FUNC(TA_NATR)
// TA_NVI ta_func.h 未公开此函数
EXPOERT_TA_FUNC(TA_OBV)
EXPOERT_TA_FUNC(TA_PLUS_DI)
EXPOERT_TA_FUNC(TA_PLUS_DM)
// TA_PPO
// TA_PVI ta_func.h 未公开此函数
EXPOERT_TA_FUNC(TA_ROC)
EXPOERT_TA_FUNC(TA_ROCP)
EXPOERT_TA_FUNC(TA_ROCR)
EXPOERT_TA_FUNC(TA_ROCR100)
EXPOERT_TA_FUNC(TA_RSI)
// TA_SAR
// TA_SAREXT
EXPOERT_TA_FUNC(TA_SIN)
EXPOERT_TA_FUNC(TA_SINH)
EXPOERT_TA_FUNC(TA_SMA)
EXPOERT_TA_FUNC(TA_SQRT)
// TA_STDDEV
// TA_STOCH
// TA_STOCHF
// TA_STOCHRSI
EXPOERT_TA_FUNC(TA_SUB)
EXPOERT_TA_FUNC(TA_SUM)
// TA_T3
EXPOERT_TA_FUNC(TA_TAN)
EXPOERT_TA_FUNC(TA_TANH)
EXPOERT_TA_FUNC(TA_TEMA)
EXPOERT_TA_FUNC(TA_TRANGE)
EXPOERT_TA_FUNC(TA_TRIMA)
EXPOERT_TA_FUNC(TA_TRIX)
EXPOERT_TA_FUNC(TA_TSF)
EXPOERT_TA_FUNC(TA_TYPPRICE)
// TA_ULTOSC
// TA_VAR
EXPOERT_TA_FUNC(TA_WCLPRICE)
EXPOERT_TA_FUNC(TA_WILLR)
EXPOERT_TA_FUNC(TA_WMA)
#endif

namespace hku {

TA_HLC_OUT3_N_IMP(TA_ACCBANDS, TA_ACCBANDS_Lookback, 20, 2, 100000)
TA_IN1_OUT1_IMP(TA_ACOS, TA_ACOS_Lookback)
TA_HLCV_OUT1_IMP(TA_AD, TA_AD_Lookback)
TA_IN2_OUT1_IMP(TA_ADD, TA_ADD_Lookback)
TA_HLC_OUT1_N_IMP(TA_ADX, TA_ADX_Lookback, 14, 2, 100000)
TA_HLC_OUT1_N_IMP(TA_ADXR, TA_ADXR_Lookback, 14, 2, 100000)
TA_HL_OUT2_N_IMP(TA_AROON, TA_AROON_Lookback, 14, 2, 100000)
TA_HL_OUT1_N_IMP(TA_AROONOSC, TA_AROONOSC_Lookback, 14, 2, 100000)
TA_IN1_OUT1_IMP(TA_ASIN, TA_ASIN_Lookback)
TA_IN1_OUT1_IMP(TA_ATAN, TA_ATAN_Lookback)
TA_HLC_OUT1_N_IMP(TA_ATR, TA_ATR_Lookback, 14, 1, 100000)
TA_IN1_OUT1_N_IMP(TA_AVGDEV, TA_AVGDEV_Lookback, 14, 2, 100000)
TA_OHLC_OUT1_IMP(TA_AVGPRICE, TA_AVGPRICE_Lookback)
TA_IN2_OUT1_N_IMP(TA_BETA, TA_BETA_Lookback, 5, 1, 100000)
TA_OHLC_OUT1_IMP(TA_BOP, TA_BOP_Lookback)
TA_HLC_OUT1_N_IMP(TA_CCI, TA_CCI_Lookback, 14, 2, 100000)
TA_OHLC_OUT1_INT_IMP(TA_CDL2CROWS, TA_CDL2CROWS_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDL3BLACKCROWS, TA_CDL3BLACKCROWS_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDL3INSIDE, TA_CDL3INSIDE_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDL3LINESTRIKE, TA_CDL3LINESTRIKE_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDL3OUTSIDE, TA_CDL3OUTSIDE_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDL3STARSINSOUTH, TA_CDL3STARSINSOUTH_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDL3WHITESOLDIERS, TA_CDL3WHITESOLDIERS_Lookback)
TA_OHLC_OUT1_INT_P1_D_IMP(TA_CDLABANDONEDBABY, TA_CDLABANDONEDBABY_Lookback, penetration,
                          3.000000e-1, 0.000000e+0, 3.000000e+37)
TA_OHLC_OUT1_INT_IMP(TA_CDLADVANCEBLOCK, TA_CDLADVANCEBLOCK_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLBELTHOLD, TA_CDLBELTHOLD_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLBREAKAWAY, TA_CDLBREAKAWAY_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLCLOSINGMARUBOZU, TA_CDLCLOSINGMARUBOZU_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLCONCEALBABYSWALL, TA_CDLCONCEALBABYSWALL_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLCOUNTERATTACK, TA_CDLCOUNTERATTACK_Lookback)
TA_OHLC_OUT1_INT_P1_D_IMP(TA_CDLDARKCLOUDCOVER, TA_CDLDARKCLOUDCOVER_Lookback, penetration,
                          5.000000e-1, 0.000000e+0, 3.000000e+37)
TA_OHLC_OUT1_INT_IMP(TA_CDLDOJI, TA_CDLDOJI_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLDOJISTAR, TA_CDLDOJISTAR_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLDRAGONFLYDOJI, TA_CDLDRAGONFLYDOJI_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLENGULFING, TA_CDLENGULFING_Lookback)
TA_OHLC_OUT1_INT_P1_D_IMP(TA_CDLEVENINGDOJISTAR, TA_CDLEVENINGDOJISTAR_Lookback, penetration,
                          3.000000e-1, 0.000000e+0, 3.000000e+37)
TA_OHLC_OUT1_INT_P1_D_IMP(TA_CDLEVENINGSTAR, TA_CDLEVENINGSTAR_Lookback, penetration, 3.000000e-1,
                          0.000000e+0, 3.000000e+37)
TA_OHLC_OUT1_INT_IMP(TA_CDLGAPSIDESIDEWHITE, TA_CDLGAPSIDESIDEWHITE_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLGRAVESTONEDOJI, TA_CDLGRAVESTONEDOJI_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLHAMMER, TA_CDLHAMMER_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLHANGINGMAN, TA_CDLHANGINGMAN_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLHARAMI, TA_CDLHARAMI_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLHARAMICROSS, TA_CDLHARAMICROSS_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLHIGHWAVE, TA_CDLHIGHWAVE_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLHIKKAKE, TA_CDLHIKKAKE_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLHIKKAKEMOD, TA_CDLHIKKAKEMOD_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLHOMINGPIGEON, TA_CDLHOMINGPIGEON_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLIDENTICAL3CROWS, TA_CDLIDENTICAL3CROWS_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLINNECK, TA_CDLINNECK_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLINVERTEDHAMMER, TA_CDLINVERTEDHAMMER_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLKICKING, TA_CDLKICKING_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLKICKINGBYLENGTH, TA_CDLKICKINGBYLENGTH_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLLADDERBOTTOM, TA_CDLLADDERBOTTOM_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLLONGLEGGEDDOJI, TA_CDLLONGLEGGEDDOJI_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLLONGLINE, TA_CDLLONGLINE_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLMARUBOZU, TA_CDLMARUBOZU_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLMATCHINGLOW, TA_CDLMATCHINGLOW_Lookback)
TA_OHLC_OUT1_INT_P1_D_IMP(TA_CDLMATHOLD, TA_CDLMATHOLD_Lookback, penetration, 5.000000e-1,
                          0.000000e+0, 3.000000e+37)
TA_OHLC_OUT1_INT_P1_D_IMP(TA_CDLMORNINGDOJISTAR, TA_CDLMORNINGDOJISTAR_Lookback, penetration,
                          3.000000e-1, 0.000000e+0, 3.000000e+37)
TA_OHLC_OUT1_INT_P1_D_IMP(TA_CDLMORNINGSTAR, TA_CDLMORNINGSTAR_Lookback, penetration, 3.000000e-1,
                          0.000000e+0, 3.000000e+37)
TA_OHLC_OUT1_INT_IMP(TA_CDLONNECK, TA_CDLONNECK_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLPIERCING, TA_CDLPIERCING_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLRICKSHAWMAN, TA_CDLRICKSHAWMAN_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLRISEFALL3METHODS, TA_CDLRISEFALL3METHODS_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLSEPARATINGLINES, TA_CDLSEPARATINGLINES_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLSHOOTINGSTAR, TA_CDLSHOOTINGSTAR_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLSHORTLINE, TA_CDLSHORTLINE_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLSPINNINGTOP, TA_CDLSPINNINGTOP_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLSTALLEDPATTERN, TA_CDLSTALLEDPATTERN_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLSTICKSANDWICH, TA_CDLSTICKSANDWICH_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLTAKURI, TA_CDLTAKURI_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLTASUKIGAP, TA_CDLTASUKIGAP_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLTHRUSTING, TA_CDLTHRUSTING_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLTRISTAR, TA_CDLTRISTAR_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLUNIQUE3RIVER, TA_CDLUNIQUE3RIVER_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLUPSIDEGAP2CROWS, TA_CDLUPSIDEGAP2CROWS_Lookback)
TA_OHLC_OUT1_INT_IMP(TA_CDLXSIDEGAP3METHODS, TA_CDLXSIDEGAP3METHODS_Lookback)

TA_IN1_OUT1_IMP(TA_CEIL, TA_CEIL_Lookback)
TA_IN1_OUT1_N_IMP(TA_CMO, TA_CMO_Lookback, 14, 2, 100000)
TA_IN2_OUT1_N_IMP(TA_CORREL, TA_CORREL_Lookback, 30, 1, 100000)
TA_IN1_OUT1_IMP(TA_COS, TA_COS_Lookback)
TA_IN1_OUT1_IMP(TA_COSH, TA_COSH_Lookback)
TA_IN1_OUT1_N_IMP(TA_DEMA, TA_DEMA_Lookback, 30, 2, 100000)
TA_IN2_OUT1_IMP(TA_DIV, TA_DIV_Lookback)
TA_HLC_OUT1_N_IMP(TA_DX, TA_DX_Lookback, 14, 2, 100000)
TA_IN1_OUT1_N_IMP(TA_EMA, TA_EMA_Lookback, 14, 2, 100000)
TA_IN1_OUT1_IMP(TA_EXP, TA_EXP_Lookback)
TA_IN1_OUT1_IMP(TA_FLOOR, TA_FLOOR_Lookback)
TA_IN1_OUT1_IMP(TA_HT_DCPERIOD, TA_HT_DCPERIOD_Lookback)
TA_IN1_OUT1_IMP(TA_HT_DCPHASE, TA_HT_DCPHASE_Lookback)
TA_IN1_OUT2_IMP(TA_HT_PHASOR, TA_HT_PHASOR_Lookback)
TA_IN1_OUT2_IMP(TA_HT_SINE, TA_HT_SINE_Lookback)
TA_IN1_OUT1_IMP(TA_HT_TRENDLINE, TA_HT_TRENDLINE_Lookback)
TA_IN1_OUT1_INT_IMP(TA_HT_TRENDMODE, TA_HT_TRENDMODE_Lookback)
TA_OC_OUT1_N_IMP(TA_IMI, TA_IMI_Lookback, 14, 2, 100000)
TA_IN1_OUT1_N_IMP(TA_KAMA, TA_KAMA_Lookback, 30, 2, 100000)
TA_IN1_OUT1_N_IMP(TA_LINEARREG_ANGLE, TA_LINEARREG_ANGLE_Lookback, 14, 2, 100000)
TA_IN1_OUT1_N_IMP(TA_LINEARREG_INTERCEPT, TA_LINEARREG_INTERCEPT_Lookback, 14, 2, 100000)
TA_IN1_OUT1_N_IMP(TA_LINEARREG_SLOPE, TA_LINEARREG_SLOPE_Lookback, 14, 2, 100000)
TA_IN1_OUT1_N_IMP(TA_LINEARREG, TA_LINEARREG_Lookback, 14, 2, 100000)
TA_IN1_OUT1_IMP(TA_LN, TA_LN_Lookback)
TA_IN1_OUT1_IMP(TA_LOG10, TA_LOG10_Lookback)
TA_IN1_OUT3_N_IMP(TA_MACDFIX, TA_MACDFIX_Lookback, 9, 1, 100000)
TA_IN1_OUT1_N_IMP(TA_MAX, TA_MAX_Lookback, 30, 2, 100000)
TA_IN1_OUT1_INT_N_IMP(TA_MAXINDEX, TA_MAXINDEX_Lookback, 30, 2, 100000)
TA_HL_OUT1_IMP(TA_MEDPRICE, TA_MEDPRICE_Lookback)
TA_HLCV_OUT1_N_IMP(TA_MFI, TA_MFI_Lookback, 14, 2, 100000)
TA_IN1_OUT1_N_IMP(TA_MIDPOINT, TA_MIDPOINT_Lookback, 14, 2, 100000)
TA_HL_OUT1_N_IMP(TA_MIDPRICE, TA_MIDPRICE_Lookback, 14, 2, 100000)
TA_IN1_OUT1_N_IMP(TA_MIN, TA_MIN_Lookback, 30, 2, 100000)
TA_IN1_OUT1_INT_N_IMP(TA_MININDEX, TA_MININDEX_Lookback, 30, 2, 100000)
TA_IN1_OUT2_N_IMP(TA_MINMAX, TA_MINMAX_Lookback, 30, 2, 100000)
TA_IN1_OUT2_INT_N_IMP(TA_MINMAXINDEX, TA_MINMAXINDEX_Lookback, 30, 2, 100000)
TA_HLC_OUT1_N_IMP(TA_MINUS_DI, TA_MINUS_DI_Lookback, 14, 1, 100000)
TA_HL_OUT1_N_IMP(TA_MINUS_DM, TA_MINUS_DM_Lookback, 14, 1, 100000)
TA_IN2_OUT1_IMP(TA_MULT, TA_MULT_Lookback)
TA_IN1_OUT1_N_IMP(TA_MOM, TA_MOM_Lookback, 10, 1, 100000)
TA_HLC_OUT1_N_IMP(TA_NATR, TA_NATR_Lookback, 14, 1, 100000)
TA_CV_OUT1_IMP(TA_OBV, TA_OBV_Lookback)
TA_HLC_OUT1_N_IMP(TA_PLUS_DI, TA_PLUS_DI_Lookback, 14, 1, 100000)
TA_HL_OUT1_N_IMP(TA_PLUS_DM, TA_PLUS_DM_Lookback, 14, 1, 100000)
TA_IN1_OUT1_N_IMP(TA_ROC, TA_ROC_Lookback, 10, 1, 100000)
TA_IN1_OUT1_N_IMP(TA_ROCP, TA_ROCP_Lookback, 10, 1, 100000)
TA_IN1_OUT1_N_IMP(TA_ROCR, TA_ROCR_Lookback, 10, 1, 100000)
TA_IN1_OUT1_N_IMP(TA_ROCR100, TA_ROCR100_Lookback, 10, 1, 100000)
TA_IN1_OUT1_N_IMP(TA_RSI, TA_RSI_Lookback, 14, 2, 100000)
TA_IN1_OUT1_IMP(TA_SIN, TA_SIN_Lookback)
TA_IN1_OUT1_IMP(TA_SINH, TA_SINH_Lookback)
TA_IN1_OUT1_N_IMP(TA_SMA, TA_SMA_Lookback, 30, 2, 100000)
TA_IN1_OUT1_IMP(TA_SQRT, TA_SQRT_Lookback)
TA_IN2_OUT1_IMP(TA_SUB, TA_SUB_Lookback)
TA_IN1_OUT1_N_IMP(TA_SUM, TA_SUM_Lookback, 30, 2, 100000)
TA_IN1_OUT1_IMP(TA_TAN, TA_TAN_Lookback)
TA_IN1_OUT1_IMP(TA_TANH, TA_TANH_Lookback)
TA_IN1_OUT1_N_IMP(TA_TEMA, TA_TEMA_Lookback, 30, 2, 100000)
TA_HLC_OUT1_IMP(TA_TRANGE, TA_TRANGE_Lookback)
TA_IN1_OUT1_N_IMP(TA_TRIMA, TA_TRIMA_Lookback, 30, 2, 100000)
TA_IN1_OUT1_N_IMP(TA_TRIX, TA_TRIX_Lookback, 30, 1, 100000)
TA_IN1_OUT1_N_IMP(TA_TSF, TA_TSF_Lookback, 14, 2, 100000)
TA_HLC_OUT1_IMP(TA_TYPPRICE, TA_TYPPRICE_Lookback)
TA_HLC_OUT1_IMP(TA_WCLPRICE, TA_WCLPRICE_Lookback)
TA_HLC_OUT1_N_IMP(TA_WILLR, TA_WILLR_Lookback, 14, 2, 100000)
TA_IN1_OUT1_N_IMP(TA_WMA, TA_WMA_Lookback, 30, 2, 100000)

}  // namespace hku