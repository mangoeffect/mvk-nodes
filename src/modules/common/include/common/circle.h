/**
 * @file circle.h
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_CIRCLE_H_
#define MVK_CIRCLE_H_

#include "common/common_defines.h"
#include "common/points.h"

namespace mvk
{
    class MVK_COMMON_EXPORT CircleImpl;                       ///< 圆实现类
    
    /**
     * @brief 圆形
     * 
     */
    class MVK_COMMON_EXPORT Circle
    {
    private:
        std::shared_ptr<CircleImpl> circle_impl_;            ///< 圆实现类
    public:
        /**
         * @brief 默认构造函数
         * 
         */
        Circle() = delete;

        /**
         * @brief 构造函数
         * 
         * @param center(in) 圆心坐标点 
         * @param radius(in) 圆半径 
         */
        Circle(const Point& center, const float& radius);

        /**
         * @brief 析构函数
         * 
         */
        ~Circle();

        /**
         * @brief 返回圆面积
         * 
         * @return double 
         */
        double GetArea() const;

        /**
         * @brief 返回圆半径
         * 
         * @return float 
         */
        float GetRadius() const;

        /**
         * @brief 返回圆心坐标
         * 
         * @return Point 
         */
        Point GetCenter() const;
    };
    
} // namespace mvk


#endif //MVK_CIRCLE_H_

