/**
 * @file points.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "common/point.hpp"

namespace mvk
{
    template<typename T>
    T DotProduct(const Point<T>& p1, const Point<T>& p2)
    {
        return p1.x * p2.x + p1.y * p2.y;
    }
} // namespace mvk

