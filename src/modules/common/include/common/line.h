/**
 * @file line.h
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-09-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_LINE_H_
#define MVK_LINE_H_

#include "common/common_defines.h"
#include "common/points.h"
#include <array>

namespace mvk
{
    class MVK_COMMON_EXPORT LineImpl;                   ///< Line实现类前置声明

    /**
     * @brief Line声明
     * 
     */
    class MVK_COMMON_EXPORT Line
    {
    private:
        std::shared_ptr<LineImpl> line_impl_;           ///< Line实现类对象指针
    public:
        /**
         * @brief 构造函数,输入直线上一点与直线方向向量
         * 
         * @param point(in)  直线上某一个点
         * @param direct(in) 直线方向向量 
         */
        Line(const Point& point, const Vector& direct);

        /**
         * @brief 析构函数
         * 
         */
        ~Line();

        // ---------------------------两点式----------------------------

        /**
         * @brief 基于两点式参数设置直线方程
         * 
         * @param point1(in) 在直线上第一个点 
         * @param point2(in) 在直线上第二个点 
         */
        void SetByTwoPointFormula(const Point& point1, const Point& point2);

        /**
         * @brief 返回两点式两个点，在表示直线段时返回直线两端坐标
         * 
         * @return std::array<Point, 2> 
         */
        std::array<Point, 2> GetEndsPoints() const;

        // ---------------------------点法式、点向式---------------------

        /**
         * @brief 基于点法式设置直线方程
         * 
         * @param point(in) 直线上某一点 
         * @param normal(in) 直线法向量
         */
        void SetByPointNormalFormula(const Point& point, const Vector& normal);

        /**
         * @brief 基于点向式设置直线参数方程
         * 
         * @param point(in) 直线上某一点 
         * @param direct(in) 直线方向向量 
         */
        void SetByPointDirectFormula(const Point& point, const Vector& direct);
        
        /**
         * @brief 获取直线上一点
         * 
         * @return Point 
         */
        Point GetPoint() const;

        /**
         * @brief 获取直线法向量
         * 
         * @return Vector 
         */
        Vector GetNormalVector() const;

        /**
         * @brief 获取直线方向向量
         * 
         * @return Vector 
         */
        Vector GetDirectVector() const;

        // ----------------------------截距式---------------------------

        /**
         * @brief 基于截距式设置直线参数方程
         * 
         * @param slope 
         * @param intercept 
         */
        void SetByInterceptFormula(const double& slope, const double& intercept);

        /**
         * @brief 获取直线斜率
         * 
         * @return double 
         */
        double GetSlope() const;

        /**
         * @brief 获取直线截距
         * 
         * @return double 
         */
        double GetIntercept() const;

        // ----------------------------一般式---------------------------

        /**
         * @brief 基于一般式设置直线参数方程, Ax + By + C = 0
         * 
         * @param a(in) 直线方程一般式参数a
         * @param b(in) 直线方程一般式参数b
         * @param c(in) 直线方程一般式参数c
         */
        void SetByGeneralFormula(const double& a, const double& b, const double& c);

        /**
         * @brief 获取一般式直线方程参数a
         * 
         * @return double 
         */
        double GetA() const;

        /**
         * @brief 获取一般式直线方程参数b
         * 
         * @return double 
         */
        double GetB() const;

        /**
         * @brief 获取一般式直线方程参数c
         * 
         * @return double 
         */
        double GetC() const;

        /**
         * @brief 判断两直线是否相交，返回true为两直线有交点
         * 
         * @param other(in) 另一条直线 
         * @return true 两直线有交点
         * @return false 两直线平行
         */
        bool HasIntersection(const Line& other);

        /**
         * @brief 获取两直线交点
         * 
         * @param other(in) 另一条直线
         * @return Point 
         */
        Point GetIntersection(const Line& other);
    };
    
} // namespace mvk


#endif //MVK_LINE_H_
