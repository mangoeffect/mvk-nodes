/**
 * @file rotate_rectangle.h
 * @author mango (2321544362@qq.com)
 * @brief 旋转矩形类
 * @version 0.1
 * @date 2021-08-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_ROTATE_RECTANGLE_H_
#define MVK_ROTATE_RECTANGLE_H_

#include "common/points.h"
#include "common/common_defines.h"
#include <array>

namespace mvk
{
    class MVK_COMMON_EXPORT RotateRectangleImpl;                    ///< 旋转矩形实现类前置声明

    /**
     * @brief 旋转矩形
     * 
     */
    class MVK_COMMON_EXPORT RotateRectangle
    {
    private:
        std::shared_ptr<RotateRectangleImpl> rotate_rectangle_impl_;        ///< 旋转矩形实现类对象指针
    public:
        /**
         * @brief 默认构造函数
         * 
         */
        RotateRectangle() = delete;

        /**
         * @brief 构造函数
         * 
         * @param points 
         */
        RotateRectangle(const std::array<Point, 4>& points);

        /**
         * @brief 析构函数
         * 
         */
        ~RotateRectangle();

        /**
         * @brief 获取矩形四个顶点坐标
         * 
         * @return std::array<Point, 4> 
         */
        std::array<Point, 4> GetPoints() const;

        /**
         * @brief 获取矩形中心点坐标
         * 
         * @return Point 
         */
        Point GetCenter() const;

        /**
         * @brief 获取矩形宽度
         * 
         * @return float 
         */
        float GetWidth() const;

        /**
         * @brief 获取矩形高度
         * 
         * @return float 
         */
        float GetHeight() const;

        /**
         * @brief 获取矩形面积
         * 
         * @return double 
         */
        double GetArea() const;

        /**
         * @brief 获取矩形旋转角度
         * 
         * @return double 
         */
        double GetAngle() const;
    };
    
} // namespace mvk

#endif //MVK_ROTATE_RECTANGLE_H_
