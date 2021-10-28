/**
 * @file polygon_impl.h
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_POLYGON_IMPL_H_
#define MVK_POLYGON_IMPL_H_

#include "common/points.h"
#include <vector>

namespace mvk
{
    class MVK_COMMON_EXPORT PolygonImpl
    {
    private:
        std::vector<Point> points_;                                             ///< 多边形轮廓坐标点
        Point centroid_;                                                        ///< 多边形质心坐标点
        bool sorted_;                                                           ///< 多边形轮廓点是否已经排序
    public:
         PolygonImpl(const std::vector<Point>& points, const bool& sorted = true);
        ~PolygonImpl();

        Point GetCentroid() const;

        double GetArea() const;

        int GetConvexHull(std::vector<Point>& convex_hull) const;
    };    
} // namespace mvk

#endif //MVK_POLYGON_IMPL_H_
