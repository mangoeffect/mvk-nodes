/**
 * @file circle.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "common/circle.hpp"
#include "common/common_defines.hpp"

namespace mvk
{
    double GetCircleArea(const Circle& circle)
    {
        return MVK_PI * circle.radius * circle.radius;
    }
} // namespace mvk


