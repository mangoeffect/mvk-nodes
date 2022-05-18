/**
 * @file lines_defines.h
 * @author mango (2321544362@qq.com)
 * @brief lines detection模块相关类型定义
 * @version 0.1
 * @date 2021-08-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_LINES_DEFINES_HPP_
#define MVK_LINES_DEFINES_HPP_

namespace mvk
{
    /**
     * @brief 直线拟合算法枚举
     */
    enum  class LineFitMethod
    {
        REGRESSION = 0,              ///< 标准的最小二乘拟合
        HUBER = 1,                   ///< 加权最小二乘拟合，通过Huber方法减小离群点的影响
        TUKEY = 2,                   ///< 加权最小二乘拟合，通过Tukey方法减小离群点的影响
        DROP = 3,                    ///< 加权的最小二乘法拟合，异常值的影响被消除
        GAUSS = 4,                   ///< 加权的最小二乘法拟合，异常值的影响被减小基于最逼近线上的所有其轮廓点的平均值和距离标准方差
        ORTHOGONAL = 5,              ///< 基于正交回归方法拟合，标准最小二乘算法区别为使用投影误差代替残差计算
        RACSAC = 6                   ///< 使用随机抽样一致性方法拟合         
    };//enum  class LineFitMethod

    
    /**
     * @brief 度量距离类型, 与OpenCV中cv::fitLine方法中定义一致
     */
    enum class DistType
    {
        DIST_L2 = 0,            
        DIST_L1 = 1,
        DISL_L12 = 2,
        DISL_HUBER = 3,
    };
} // namespace mvk


#endif //MVK_LINES_DEFINES_H_
