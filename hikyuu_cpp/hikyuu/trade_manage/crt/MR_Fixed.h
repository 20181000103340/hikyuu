/*
 *  Copyright (c) 2022 hikyuu.org
 *
 *  Created on: 2022-09-01
 *      Author: fasiondog
 */

#pragma once

#include "../MarginRatioBase.h"

namespace hku {

/**
 * @brief 固定保证金比例算法
 * @ingroup TradeMargin
 * @param initRatio 保证金比例 (0, 1]
 * @param maintainRatio 维持保证金比例 (0, 1]
 * @return MRPtr
 */
MRPtr HKU_API MR_Fixed(double initRatio, double maintainRatio);

}  // namespace hku