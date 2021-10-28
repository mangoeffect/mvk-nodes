/**
 * @file rectangle_impl.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "common/rectangle_impl.h"

namespace mvk
{
    RectangleImpl::RectangleImpl(const Point& top_left, const float& width, const float& height)
    {
        Point top_right(top_left.GetX() + width, top_left.GetY());
        Point bottom_right(top_left.GetX() + width, top_left.GetY() + height);
        Point bottom_left(top_left.GetX(), top_left.GetY() + height);
        points_[0] = top_left;
        points_[1] = top_right;
        points_[2] = bottom_right;
        points_[3] = bottom_left;
        
        center_.SetX(0.5f * (top_left.GetX() + bottom_right.GetX()));
        center_.SetY(0.5f * (top_left.GetY() + bottom_right.GetY()));

        area_ = width * height;
    }

    RectangleImpl::RectangleImpl(const Point& top_left, const Point& bottom_right)
    {
        float width = std::abs(bottom_right.GetX() - top_left.GetX());
        float height = std::abs(bottom_right.GetY() - top_left.GetY());
        Point top_right(top_left.GetX() + width, top_left.GetY());
        Point bottom_left(top_left.GetX(), top_left.GetY() + height);

        points_[0] = top_left;
        points_[1] = top_right;
        points_[2] = bottom_right;
        points_[3] = bottom_left;
        
        center_.SetX(0.5f * (top_left.GetX() + bottom_right.GetX()));
        center_.SetY(0.5f * (top_left.GetY() + bottom_right.GetY()));

        area_ = width * height;
    }

    RectangleImpl::~RectangleImpl()
    {

    }
     
    float RectangleImpl::GetWidth() const
    {
        return width_;
    }

    float RectangleImpl::GetHeight() const
    {
        return height_;
    }

    double RectangleImpl::GetArea() const
    {
        return area_;
    }


    Point RectangleImpl::GetCenter() const
    {
        return center_;
    }


    Point RectangleImpl::GetTopleft() const
    {
        return points_[0];
    }

    Point RectangleImpl::GetTopRight() const
    {
        return points_[1];
    }

    Point RectangleImpl::GetBottomRight() const
    {
        return points_[2];
    }

    Point RectangleImpl::GetBottomLeft() const
    {
        return points_[3];
    }


    std::array<Point, 4> RectangleImpl::GetPoints() const
    {
        return points_;
    }

    RectangleImpl RectangleImpl::operator& (const RectangleImpl& other) const
    {
        float overlap_width = GetWidth() + other.GetWidth() - (std::max(GetTopRight().GetX(), other.GetTopRight().GetX()) - std::min(GetTopleft().GetX(), other.GetTopleft().GetX()));
        float overlap_height = GetHeight() + other.GetHeight() - (std::max(GetBottomRight().GetY(), other.GetBottomRight().GetY()) - std::min(GetTopleft().GetY(), other.GetTopleft().GetY()));

        if(overlap_width <= 0 || overlap_height <= 0)
        {
            //无交集
            return RectangleImpl(Point(0.0f, 0.0f), 0.0f, 0.0f);
        }else
        {
            Point top_left(std::max(GetTopleft().GetX(), other.GetTopleft().GetX()), std::max(GetTopleft().GetY(), other.GetTopleft().GetY()));
            return RectangleImpl(top_left, overlap_width, overlap_height);
        }
    }


    RectangleImpl RectangleImpl::operator| (const RectangleImpl& other) const
    {
         Point top_left(std::min(GetTopleft().GetX(), other.GetTopleft().GetX()), std::min(GetTopleft().GetY(), other.GetTopleft().GetY()));
         Point bottom_right(std::max(GetBottomRight().GetX(), other.GetBottomRight().GetX()), std::max(GetBottomRight().GetY(), other.GetBottomRight().GetY()));
         return RectangleImpl(top_left, bottom_right);
    }
} // namespace mvk



