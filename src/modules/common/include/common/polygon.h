/**
 * @file polygon.h
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_POLYGON_H_
#define MVK_POLYGON_H_

#include "common/points.h"
#include <vector>

namespace mvk
{
    class MVK_COMMON_EXPORT PolygonImpl;                                                ///< Polygon实现类前置声明

    class MVK_COMMON_EXPORT Polygon
    {
    private:
        std::shared_ptr<PolygonImpl> polygon_impl_;                                     ///< Polygon实现类对象指针
    public:
        /**
         * @brief 构造函数
         * 
         * @param points(in) 多边形轮廓点 
         * @param sorted(in) 轮廓点是否已经排序 
         */
        Polygon(const std::vector<Point>& points, const bool& sorted = true);

        /**
         * @brief 析构函数
         * 
         */
        ~Polygon();

        /**
         * @brief 获取多边形质心
         * 
         * @return Point 
         */
        Point GetCentroid() const;

        /**
         * @brief 获取多边形质心
         * 
         * @return double 
         */
        double GetArea() const;

        /**
         * @brief 获取多边形凸包
         * 
         * @param convex_hull(out) 多边形凸包 
         * @return int 执行错误码 
         */
        int GetConvexHull(std::vector<Point>& convex_hull) const;
    };
    
} // namespace mvk


#endif //MVK_POLYGON_H_
