/**
 * @file circle_impl.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "common/circle_impl.h"

namespace mvk
{
    CircleImpl:: CircleImpl(const Point& center, const float& radius)
    : center_(center), radius_(radius), area_(MVK_PI * radius_ * radius_)
    {
        
    }

    double CircleImpl::GetArea() const
    {
        return area_;
    }

    float CircleImpl::GetRadius() const
    {
        return radius_;
    }

    Point CircleImpl::GetCenter() const
    {
        return center_;
    }
    
    CircleImpl::~CircleImpl()
    {
        
    }
    
} // namespace mvk
