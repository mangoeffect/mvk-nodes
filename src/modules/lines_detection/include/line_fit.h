/**
 * @file line_fit.h
 * @author mango (2321544362@qq.com)
 * @brief 二维平面直线拟合算法声明
 * @version 0.1
 * @date 2021-07-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef LINE_FIT_H_
#define LINE_FIT_H_

#include <vector>

#include "opencv2/opencv.hpp"

namespace mvk
{
    namespace line_fit
    {
        /**
         * @brief 直线拟合结果
         */
        struct LineFitResult
        {
            double a;                ///< 一般式参数a
            double b;                ///< 一般式参数b     
            double c;                ///< 一般式参数c   
            std::vector<cv::Point2f>  inliers;     ///< 内点，未被剔除用于拟合
            std::vector<cv::Point2f>  outliers;    ///< 离群点，被剔除未参与拟合
        };//LineFitResult


        /**
         * @brief 直线拟合类实现
         * 
         */
        class LineFit
        {
        private:
            std::vector<cv::Point2f> points_;                                                              ///< 待拟合的点集
            LineFitResult result_;                                                                         ///< 拟合结果
            LineFitMethod common_paramter_linefit_method_{LineFitMethod::RACSAC};                          ///< 拟合方法, 默认RACSAC
            DistType common_parameter_dist_type_{DistType::DIST_L2};                                       ///< 距离类型， 默认DIST_L2
        public:
            LineFit(/* args */);
            ~LineFit();

             /**
             * @brief 设置输入坐标点数组
             * @param points(in) 坐标点数据
             * @return 执行错误码
             */
            int SetInputPoints(const std::vector<cv::Point2f>& points);

            /**
             * @brief 执行拟合处理
             * 
             * @return int 
             */
            int DoFitting();
            
            //--------------------参数设置与获取-------------------------
            /**
             * @brief 设置公共参数中的距离类型参数
             * 
             * @param type 
             * @return int 
             */
            int SetCommonParameterDistType(const DistType& type);

            /**
             * @brief 获取公共参中的距离类型参数
             * 
             * @return DistType 
             */
            DistType GetCommonParameterDistType() const;

            //--------------------参数设置与获取-------------------------

            /**
             * @brief 获取拟合结果
             * 
             * @return LineFitResult 
             */
            LineFitResult GetReasult() const;
        };
        
        
    }// namespace line_fit
}//namespace mvk

#endif //LINE_FIT_H_
