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

#include "common/circle.h"
#include "common/circle_impl.h"

namespace mvk
{
    Circle::~Circle()
    {
    }

    Circle::Circle(const Point& center, const float& radius)
    : circle_impl_(new CircleImpl(center, radius))
    {

    }
    
    double Circle::GetArea() const
    {
        return circle_impl_->GetArea();
    }

    float Circle::GetRadius() const
    {
        return circle_impl_->GetRadius();
    }

    Point Circle::GetCenter() const
    {
        return circle_impl_->GetCenter();
    }
} // namespace mvk


