/**
 * @file rectangle.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "common/rectangle.hpp"

namespace mvk
{
    Point2f GetRectCenter(const Rect& rect)
    {
        return Point2f(0.5f * (rect.topleft.x + rect.bottomright.x), 
                       0.5f * (rect.topleft.y + rect.bottomright.y));
    }
} // namespace mvk


