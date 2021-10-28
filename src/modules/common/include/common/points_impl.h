/**
 * @file points_impl.h
 * @author mango (2321544362@qq.com)
 * @brief points实现类
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_POINTS_IMPL_H_
#define MVK_POINTS_IMPL_H_

#include "common/common_defines.h"

namespace mvk
{
    /**
     * @brief point实现类
     * 
     */
    class MVK_COMMON_EXPORT PointImpl
    {
    private:
        float x_;                                ///< 横坐标
        float y_;                                ///< 纵坐标
    public:
         /**
         * @brief 默认构造函数
         * 
         */
        PointImpl();

        /**
         * @brief 拷贝构造函数
         * 
         * @param other 
         */
        PointImpl(const PointImpl& other);

        /**
         * @brief 构造函数
         * 
         * @param x(in) 横坐标初值 
         * @param y(in) 纵坐标初值 
         */
        PointImpl(const float& x, const float& y);

        /**
         * @brief 析构函数
         * 
         */
        ~PointImpl();

        /**
         * @brief 由坐标点表示的两个向量点乘， x1 * y1 + x2 * y2
         * 
         * @param other(in) 另一个坐标点 
         * @return float 点乘结果
         */
        float Dot(const PointImpl& other);

        /**
         * @brief 由坐标点表示的两个向量点乘， x1 * y1 + x2 * y2
         * 
         * @param other(in) 另一个坐标点 
         * @return double 点乘结果
         */
        double Ddot(const PointImpl& other);

        /**
         * @brief 两坐标点相加
         * 
         * @param other(in) 另一个坐标点 
         * @return Point 
         */
        PointImpl operator + (const PointImpl& other);

        /**
         * @brief 两坐标点相减
         * 
         * @param other(in) 另一个坐标点 
         * @return Point 
         */
        PointImpl operator - (const PointImpl& other);

           /**
         * @brief 返回横坐标X值
         * 
         * @return float 
         */
        float GetX() const;

        /**
         * @brief 返回纵坐标Y值
         * 
         * @return float 
         */
        float GetY() const;

        /**
         * @brief 设置横坐标X值
         * 
         * @param x 
         */
        void SetX(const float& x);

        /**
         * @brief 设置纵坐标Y值
         * 
         * @param y 
         */
        void SetY(const float& y);
    };    
} // namespace mvk


#endif //MVK_POINTS_IMPL_H_
