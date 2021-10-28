/**
 * @file rotate_rectangle_impl.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "common/rotate_rectangle_impl.h"

namespace mvk
{
    RotateRectangleImpl::~RotateRectangleImpl()
    {

    }
  
    RotateRectangleImpl::RotateRectangleImpl(const std::array<Point, 4>& points)
    {
        points_ = points_;
        //todo: 计算矩形各个参数值
    }

    std::array<Point, 4> RotateRectangleImpl::GetPoints() const
    {
        return points_;
    }

    Point RotateRectangleImpl::GetCenter() const
    {
        return center_;
    }

    float RotateRectangleImpl::GetWidth() const
    {
        return width_;
    }

    float RotateRectangleImpl::GetHeight() const
    {
        return height_;
    }

    double RotateRectangleImpl::GetArea() const
    {
        return area_;
    }

    double RotateRectangleImpl::GetAngle() const
    {
        return angle_;
    }
} // namespace mvk

