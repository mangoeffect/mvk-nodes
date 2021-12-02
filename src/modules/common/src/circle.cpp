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
#include <numbers>

namespace mvk
{
    double GetCircleArea(const Circle& circle)
    {
        return std::numbers::pi * circle.radius * circle.radius;
    }
} // namespace mvk


