/**
 * @file algorithms.h
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_ALGORITHMS_H_
#define MVK_ALGORITHMS_H_

#include "common/point.hpp"
#include "common/rotate_rectangle.hpp"

#include <vector>

namespace mvk
{
    /**
     * @brief 计算散点点集凸包
     * 
     * @param points(in) 散点点集坐标 
     * @param convex_hull(in) 凸包坐标  
     * @return int 执行错误码
     */
    int ConvexHull(const std::vector<Point2f>& points, std::vector<Point2f>& convex_hull);

    double PolygonArea(const std::vector<Point2f>& points);

    int MinRectangle(const std::vector<Point2f>& points, RotateRect& min_rect);
    
} // namespace mvk

#endif //MVK_ALGORITHMS_H_
