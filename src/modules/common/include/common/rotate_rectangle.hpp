/**
 * @file rotate_rectangle.hpp
 * @author mango (2321544362@qq.com)
 * @brief 旋转矩形类
 * @version 0.1
 * @date 2021-08-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_ROTATE_RECTANGLE_HPP_
#define MVK_ROTATE_RECTANGLE_HPP_

#include "common/point.hpp"
#include <array>
#include <cmath>

namespace mvk
{
    /**
     * @brief 旋转矩形,顺时针坐标点
     * 方向角度定义： 坐标点0 ----> 1直线与x轴夹角
     * 宽度定义： 坐标点0 <---> 1 ( 2 <----> 3)的距离
     * 高度定义： 坐标点0 <---> 1 ( 2 <----> 3)的距离
     */
    template<typename T = float>
    struct RotateRect
    {
        std::array<Point<T>, 4> points;
        
        /**
         * @brief 获取矩形宽度：
         * 宽度定义： 坐标点0 <---> 1 ( 2 <----> 3)的距离
         * 
         * @return float 
         */
        float GetWidth() const
        {
            Point<T> diff = points[1] - points[0];
            return std::sqrt(diff.x * diff.x + diff.y * diff.y);
        }

        /**
         * @brief 获取矩形高度
         * 高度定义： 坐标点0 <---> 1 ( 2 <----> 3)的距离
         * 
         * @return float 
         */
        float GetHeight() const
        {
            Point<T> diff = points[2] - points[1];
            return std::sqrt(diff.x * diff.x + diff.y * diff.y);
        }

        /**
         * @brief 获取矩形面积
         * 
         * @return float 
         */
        float GetAngle()
        {
            Point<T> v = points[1] - points[0];
            //归一化
            double vm = std::sqrt(std::pow(v.x) + std::pow(v.y));
            v.x /= vm;
            v.y /= vm;
            Point<T> vx(1.0, 0);
            return std::acos(vx.Dot(v));
        }

        Point<T> GetDirection() const
        {
            auto diret = points[1] - points[0];
            diret.Normalize();
            return diret;
        }

        float GetArea() const
        {
            return GetWidth() * GetHeight();
        }
    };
    
    using RotateRectf = RotateRect<float>;
} // namespace mvk

#endif //MVK_ROTATE_RECTANGLE_H_
