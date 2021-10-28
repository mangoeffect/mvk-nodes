/**
 * @file line_impl.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "common/line_impl.h"

namespace mvk
{
    LineImpl::LineImpl(const Point& point, const Vector& direct)
    {
        //todo: 求取其它参数
    }
    
    LineImpl::~LineImpl()
    {
    }

    // ---------------------------两点式----------------------------
    void LineImpl::SetByTwoPointFormula(const Point& point1, const Point& point2)
    {
        point1_ = point1;
        point2_ = point2;

        //todo: 求取其它参数
    }

    std::array<Point, 2> LineImpl::GetEndsPoints() const
    {
        return {point1_, point2_};
    }

    // ---------------------------点法式、点向式---------------------
    void LineImpl::SetByPointNormalFormula(const Point& point, const Vector& normal)
    {
        centroid_ = point;
        normal_ = normal;
        //todo: 求取其它形式参数
    }
    void LineImpl::SetByPointDirectFormula(const Point& point, const Vector& direct)
    {
        centroid_ = point;
        direct_ = direct;
        //todo: 求取其它形式参数
    }
    
    Point LineImpl::GetPoint() const
    {
        return centroid_;
    }

    Vector LineImpl::GetNormalVector() const
    {
        return normal_;
    }

    Vector LineImpl::GetDirectVector() const
    {
        return direct_;
    }

    // ----------------------------截距式---------------------------
    void LineImpl::SetByInterceptFormula(const double& slope, const double& intercept)
    {
        slope_ = slope;
        intercept_ = intercept;
        //todo: 求取其它形式参数
    }

    double LineImpl::GetSlope() const
    {
        return slope_;
    }

    double LineImpl::GetIntercept() const
    {
        return intercept_;
    }

    // ----------------------------一般式---------------------------
    void LineImpl::SetByGeneralFormula(const double& a, const double& b, const double& c)
    {
        a_ = a;
        b_ = b;
        c_ = c;

        //todo: 求取其它形式参数
    }

    double LineImpl::GetA() const
    {
        return a_;
    }

    double LineImpl::GetB() const
    {
        return b_;
    }

    double LineImpl::GetC() const
    {
        return c_;
    }

    bool LineImpl::HasIntersection(const LineImpl& other)
    {
        //todo: 判断是否平行
        return false;
    }

    Point LineImpl::GetIntersection(const LineImpl& other)
    {
        Point intersection;
        //todo: 求取交点
        return intersection;
    }
} // namespace mvk

