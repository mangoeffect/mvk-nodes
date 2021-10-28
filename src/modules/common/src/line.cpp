/**
 * @file line.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "common/line.h"
#include "common/line_impl.h"


namespace mvk
{
    Line::Line(const Point& point, const Vector& direct)
    : line_impl_(new LineImpl(point, direct))
    {
    }
    
    Line::~Line()
    {
    }

    // ---------------------------两点式----------------------------
    void Line::SetByTwoPointFormula(const Point& point1, const Point& point2)
    {
        line_impl_->SetByTwoPointFormula(point1, point2);
    }

    std::array<Point, 2> Line::GetEndsPoints() const
    {
        return line_impl_->GetEndsPoints();
    }

    // ---------------------------点法式、点向式---------------------
    void Line::SetByPointNormalFormula(const Point& point, const Vector& normal)
    {
        line_impl_->SetByPointNormalFormula(point, normal);
    }

    void Line::SetByPointDirectFormula(const Point& point, const Vector& direct)
    {
        line_impl_->SetByPointDirectFormula(point, direct);
    }
    
    Point Line::GetPoint() const
    {
        return line_impl_->GetPoint();
    }

    Vector Line::GetNormalVector() const
    {
        return line_impl_->GetNormalVector();
    }

    Vector Line::GetDirectVector() const
    {
        return line_impl_->GetDirectVector();
    }

    // ----------------------------截距式---------------------------
    void Line::SetByInterceptFormula(const double& slope, const double& intercept)
    {
        line_impl_->SetByInterceptFormula(slope, intercept);
    }

    double Line::GetSlope() const
    {
        return line_impl_->GetSlope();
    }

    double Line::GetIntercept() const
    {
        return line_impl_->GetIntercept();
    }

    // ----------------------------一般式---------------------------
    void Line::SetByGeneralFormula(const double& a, const double& b, const double& c)
    {
        line_impl_->SetByGeneralFormula(a, b, c);
    }
    double Line::GetA() const
    {
        return line_impl_->GetA();
    }

    double Line::GetB() const
    {
        return line_impl_->GetB();
    }

    double Line::GetC() const
    {
        return line_impl_->GetC();
    }

    bool Line::HasIntersection(const Line& other)
    {
        return line_impl_->HasIntersection(*other.line_impl_);
    }

    Point Line::GetIntersection(const Line& other)
    {
        return line_impl_->GetIntersection(*other.line_impl_);
    }
} // namespace mvk

