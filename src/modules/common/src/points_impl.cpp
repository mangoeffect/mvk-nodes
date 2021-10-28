/**
 * @file points_impl.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "common/points_impl.h"

namespace mvk
{
    PointImpl::PointImpl(/* args */): x_(0), y_(0)
    {

    }

    PointImpl::PointImpl(const PointImpl& other)
    {
        x_ = other.GetX();
        y_ = other.GetY();
    }
    
    PointImpl::PointImpl(const float& x, const float& y) : x_(x), y_(y)
    {

    }

    PointImpl::~PointImpl()
    {
    }

    float PointImpl::Dot(const PointImpl& other)
    {
        return x_ * other.GetX() + y_ * other.GetY();
    }


    double PointImpl::Ddot(const PointImpl& other)
    {
        return static_cast<double>(x_) * other.GetX() + static_cast<double>(y_) * other.GetY();
    }


    PointImpl PointImpl::operator + (const PointImpl& other)
    {
        return PointImpl(x_ + other.GetX(), y_ + other.GetY());
    }


    PointImpl PointImpl::operator - (const PointImpl& other)
    {
        return PointImpl(x_ - other.GetX(), y_ - other.GetY());
    }

    float PointImpl::GetX() const
    {
        return x_;
    }

    float PointImpl::GetY() const
    {
        return y_;
    }

    void PointImpl::SetX(const float& x)
    {
        x_ = x;
    }

    void PointImpl::SetY(const float& y)
    {
        y_ = y;
    }
} // namespace mvk


