
/**
* @file linefit.h
* @brief 直线拟合头文件
* @details 基于最小二乘、huber、tukey等方法拟合直线
* @author 芒果
* @date 2020-4-10
* @version 1.0.0
*/

#ifndef MVP_LINEFIT_H
#define MVP_LINEFIT_H

#include <memory>
#include <string>

//-------------OpenCV----------
#include "opencv2/opencv.hpp"
#include "../ransac/ransac.hpp"


namespace  mvp
{
    /**
     * @brief 直线拟合算法枚举
     */
    enum  class FitAlgorithms
    {
        REGRESSION = 0,          ///< 标准的最小二乘拟合
        HUBER,                   ///< 加权最小二乘拟合，通过Huber方法减小离群点的影响
        TUKEY,                   ///< 加权最小二乘拟合，通过Tukey方法减小离群点的影响
        DROP,                    ///< 加权的最小二乘法拟合，异常值的影响被消除
        GAUSS                    ///< 加权的最小二乘法拟合，异常值的影响被减小基于最逼近线上的所有其轮廓点的平均值和距离标准方差
    };//enum  class FitAlgorithms

    /**
     * @brief 度量距离类型, 与OpenCV中cv::fitLine方法中定义一致
     */
    enum class DistType
    {
        DIST_L2 = 0,            
        DIST_L1 = 1,
        DISL_L12 = 2,
        DISL_HUBER = 3,
    }

    /**
     * @brief 直线拟合结果，直线描述采用点斜式: y - b = k * (x - a)
     */
    struct LineFitResult
    {
        double a;                ///< 点斜式参数a,对应x
        double b;                ///< 点斜式参数b,对应y
        double k;                ///< 点斜式参数k,直线斜率
        
        std::vector<cv::Point_>  inliers;     ///< 内点，未被剔除用于拟合
        std::vector<cv::Point_>  outliers;    ///< 离群点，被剔除未参与拟合
    };//

    /**
     * @brief 直线拟合工具类
     */
    class LineFit : public Ransac
    {
    public:
        /**
         * @brief 默认构造函数
         */
        LineFit():outliers_distance_threshold_(3.0),
                  force_remove_ratio_(0.0),
                  force_remove_num_(0),
                  max_iter_num_(100),
                  dist_type_(DistType::DISL_HUBER)
        {

        }

        /**
         * @brief 创建直线拟合工具类
         */
        static std::shared_ptr<LineFit> CreateLineFitTool();
        
        /**
         * @brief 设置算法参数
         * @param json_str(in) json格式的参数
         * @return 函数状态，负数为执行异常
         */
        int SetParam(const std::string& json_str);

        /**
         * @brief 设置输入坐标点数组
         * @param point_array(in) 坐标点数据
         * @return 函数状态，负数为异常
         */
        int SetInputPointArray(const std::vector<cv::Point_>& point_array);

        
        /**
         * @brief 执行拟合算法
         * @return 函数状态，负数为异常
         */
        int Run();


        int SampleMnimumData() override;

        int FitModel() override;

        int ComputeCurrentInliers() override;

        int RecordBestModel() override;

        int IsGoodEnough() override;

        /**
         * @brief 设置离群点距离阈值，超过此值则判断为离群点，将其剔除后再拟合
         * @param threshold(in) 离群点阈值
         * @return 函数状态，负数为异常
         */
        int SetOutliersDistanceThreshold(const double& threshold);

       /**
         * @brief 设置强制剔除坐标点占比例, 取值范围[0.0, 1.0], 默认值0
         * @param ratio(in) 剔除坐标点占比例，取值范围[0.0, 1.0], 默认值0
         * @return 函数状态，负数为异常
         */
        int SetForceRemoveRatio(const double& ratio);

       /**
         * @brief 设置强制剔除坐标点数量, 优先级比force_remove_ratio_高，即若设置了force_remove_num_数则force_remove_ratio_无效,默认至少保留2个点做拟合，取值范围[0， std::numeric_limits<int>::max()]， 默认值0
         * @param num(in) 剔除点数，取值范围[0， std::numeric_limits<int>::max()]， 默认值0
         * @return 函数状态，负数为异常
         */
        int SetForceRemoveNum(const int& num);

       /**
         * @brief 设置最大迭代次数
         * @param num(in) 最大迭代次数，取值范围[1, std::numeric_limits<int>::max()]， 默认值100
         * @return 函数状态，负数为异常
         */
        int SetMaxIterNum(const int& num);
    private:
       
         double outliers_distance_threshold_;                             ///< 离群点距离阈值，超过此值则判断为离群点，将其剔除后再拟合,取值范围[0.0,std::numeric_limits<double>::max()], 默认值3.0（像素）
         double force_remove_ratio_;                                      ///< 根据距离由远到近，强制剔除坐标点占比例, 取值范围[0.0, 1.0], 默认值0
         int force_remove_num_;                                           ///< 根据距离由远到近，强制剔除坐标点数量, 优先级比force_remove_ratio_高，即若设置了force_remove_num_数则force_remove_ratio_无效,默认至少保留2个点做拟合，取值范围[0， std::numeric_limits<int>::max()]， 默认值0
         int max_iter_num_;                                               ///< 最大迭代次数，取值范围[1, std::numeric_limits<int>::max()]， 默认值100
         DistType dist_type_;                                             ///< 度量距离类型, 与OpenCV中cv::fitLine方法中定义一致, 默认huber

         LineFitResult result_;                                           ///< 拟合结果结构体
    };//class LineFit

}//namespace  mvp

#endif //MACHINE_VISION_LIBRARY_LINEFIT_H
