/**
 * @file polygon_impl.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "common/polygon_impl.h"

namespace mvk
{
    PolygonImpl:: PolygonImpl(const std::vector<Point>& points, const bool& sorted)
    : points_(points)
    {
    }
    
    PolygonImpl::~PolygonImpl()
    {
    }

    Point PolygonImpl::GetCentroid() const
    {
        return centroid_;
    }

    double PolygonImpl::GetArea() const
    {
        return 0.0;
    }

    int PolygonImpl::GetConvexHull(std::vector<Point>& convex_hull) const
    {
        return 0;
    }
} // namespace mvk

