/**
 * @file polygon.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "common/polygon.h"
#include "common/polygon_impl.h"

namespace mvk
{
    Polygon::Polygon(const std::vector<Point>& points, const bool& sorted)
    : polygon_impl_(new PolygonImpl(points, sorted))
    {

    }
    
    Polygon::~Polygon()
    {

    }

    Point Polygon::GetCentroid() const
    {
        return polygon_impl_->GetCentroid();
    }

    double Polygon::GetArea() const
    {
        return polygon_impl_->GetArea();
    }

    int Polygon::GetConvexHull(std::vector<Point>& convex_hull) const
    {
        return polygon_impl_->GetConvexHull(convex_hull);
    }
} // namespace mvk
