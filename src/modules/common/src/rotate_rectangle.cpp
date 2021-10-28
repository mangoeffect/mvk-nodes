/**
 * @file rotate_rectangle.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "common/rotate_rectangle.h"
#include "common/rotate_rectangle_impl.h"

namespace mvk
{
    RotateRectangle::~RotateRectangle()
    {
        
    }

    RotateRectangle::RotateRectangle(const std::array<Point, 4>& points)
    : rotate_rectangle_impl_(new RotateRectangleImpl(points))
    {
        
    }

    std::array<Point, 4> RotateRectangle::GetPoints() const
    {
        return rotate_rectangle_impl_->GetPoints();
    }

    Point RotateRectangle::GetCenter() const
    {
        return rotate_rectangle_impl_->GetCenter();
    }

    float RotateRectangle::GetWidth() const
    {
        return rotate_rectangle_impl_->GetWidth();
    }

    float RotateRectangle::GetHeight() const
    {
        return rotate_rectangle_impl_->GetHeight();
    }

    double RotateRectangle::GetArea() const
    {
        return rotate_rectangle_impl_->GetArea();
    }

    double RotateRectangle::GetAngle() const
    {
        return rotate_rectangle_impl_->GetAngle();
    }
} // namespace mvk


