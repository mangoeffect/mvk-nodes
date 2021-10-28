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

#include "common/points.h"
#include "common/points_impl.h"

namespace mvk
{
    Point::Point(/* args */): point_impl_(new PointImpl(0, 0))
    {

    }

    Point::Point(const std::shared_ptr<PointImpl>& point_impl)
    {
        point_impl_ = point_impl;
    }
    
    Point::Point(const float& x, const float& y) : point_impl_(new PointImpl(x, y))
    {

    }

    Point::~Point()
    {
        point_impl_->~PointImpl();
    }

    float Point::Dot(const Point& other)
    {
        return point_impl_->Dot(*other.point_impl_);
    }


    double Point::Ddot(const Point& other)
    {
        return point_impl_->Ddot(*other.point_impl_);
    }


    Point Point::operator + (const Point& other)
    {
        std::shared_ptr<PointImpl> p(&point_impl_->operator+(*other.point_impl_));
        return Point(p);
    }


    Point Point::operator - (const Point& other)
    {
        std::shared_ptr<PointImpl> p(&point_impl_->operator-(*other.point_impl_));
        return Point(p);
    }

    float Point::GetX() const
    {
        return point_impl_->GetX();
    }

    float Point::GetY() const
    {
        return point_impl_->GetY();
    }

    void Point::SetX(const float& x)
    {
        point_impl_->SetX(x);
    }

    void Point::SetY(const float& y)
    {
        point_impl_->SetY(y);
    }

} // namespace mvk

