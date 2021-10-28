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

#include "common/rectangle.h"
#include "common/rectangle_impl.h"

namespace mvk
{
    Rectangle::~Rectangle()
    {

    }
    
    Rectangle::Rectangle(const Point& top_left, const float& width, const float& height)
    : rectangle_impl_(new RectangleImpl(top_left, width, height))
    {

    }

    Rectangle::Rectangle(const Point& top_left, const Point& bottom_right)
    : rectangle_impl_(new RectangleImpl(top_left, bottom_right))
    {

    }


    float Rectangle::GetWidth() const
    {
        return rectangle_impl_->GetWidth();
    }


    float Rectangle::GetHeight() const
    {
        return rectangle_impl_->GetHeight();
    }


    double Rectangle::GetArea() const
    {
        return rectangle_impl_->GetArea();
    }


    Point Rectangle::GetCenter() const
    {
        return rectangle_impl_->GetCenter();
    }

    Point Rectangle::GetTopleft() const
    {
        return rectangle_impl_->GetTopleft();
    }

    Point Rectangle::GetTopRight() const
    {
        return rectangle_impl_->GetTopRight();
    }

    Point Rectangle::GetBottomRight() const
    {
        return rectangle_impl_->GetBottomRight();
    }


    Point Rectangle::GetBottomLeft() const
    {
        return rectangle_impl_->GetBottomLeft();
    }

    std::array<Point, 4> Rectangle::GetPoints() const
    {
        return rectangle_impl_->GetPoints();
    }

    Rectangle Rectangle::operator& (const Rectangle& other) const
    {
        auto rect = rectangle_impl_->operator&(*other.rectangle_impl_);
        return Rectangle(rect.GetTopleft(), rect.GetBottomRight());
    }

    Rectangle Rectangle::operator| (const Rectangle& other) const
    {
        auto rect = rectangle_impl_->operator|(*other.rectangle_impl_);
        return Rectangle(rect.GetTopleft(), rect.GetBottomRight());
    }
} // namespace mvk


