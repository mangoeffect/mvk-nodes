/**
 * @file rectangle.h
 * @author mango (2321544362@qq.com)
 * @brief 矩形相关定义
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_RECTANGLE_H_
#define MVK_RECTANGLE_H_

#include "common/points.h"
#include "common/common_defines.h"
#include <array>

namespace mvk
{
    class MVK_COMMON_EXPORT RectangleImpl;                  ///< 矩形类实现类

    /**
     * @brief 矩形类
     * 
     */
    class MVK_COMMON_EXPORT Rectangle
    {
    private:
        std::shared_ptr<RectangleImpl> rectangle_impl_;     ///< 矩形实现类对象指针
    public:
        /**
         * @brief 默认构造
         * 
         */
        Rectangle() = delete;

        /**
         * @brief 构造函数
         * 
         * @param top_left(in) 矩形左上角顶点坐标 
         * @param width(in) 矩形宽度 
         * @param height(in) 矩形高度 
         */
        Rectangle(const Point& top_left, const float& width, const float& height);

        /**
         * @brief 构造函数
         * 
         * @param top_left(in) 矩形左上角顶点坐标 
         * @param bottom_right(in) 矩形右下角顶点坐标 
         */
        Rectangle(const Point& top_left, const Point& bottom_right);

        /**
         * @brief 析构函数
         * 
         */
        ~Rectangle();

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
         * @brief 获取矩形中心点坐标
         * 
         * @return Point 
         */
        Point GetCenter() const;

        /**
         * @brief 获取矩形左上角顶点坐标
         * 
         * @return Point 
         */
        Point GetTopleft() const;

        /**
         * @brief 获取矩形右上角顶点坐标
         * 
         * @return Point 
         */
        Point GetTopRight() const;

        /**
         * @brief 获取矩形右下角顶点坐标
         * 
         * @return Point 
         */
        Point GetBottomRight() const;

        /**
         * @brief 获取矩形左下角顶点坐标
         * 
         * @return Point 
         */
        Point GetBottomLeft() const;

        /**
         * @brief 获取矩形四个顶点坐标，顺序为左上-右上-右下-左下
         * 
         * @return std::array<Point, 4> 
         */
        std::array<Point, 4> GetPoints() const;

        /**
         * @brief 求取两个矩形交集
         * 
         * @param other(in) 另一个矩形
         * @return Rectangle 
         */
        Rectangle operator& (const Rectangle& other) const;

        /**
         * @brief 求取两个矩形并集
         * 
         * @param other 
         * @return Rectangle 
         */
        Rectangle operator| (const Rectangle& other) const;
    };

} // namespace mvk


#endif //MVK_RECTANGLE_H_

