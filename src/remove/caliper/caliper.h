
/**
* @file caliper.h
* @brief 卡尺工具头文件
* @details 根据《机器视觉算法与应用》一维边缘点检测原理实现
* @author 芒果
* @date 2020-4-2
* @version 1.0.0
*/

#ifndef MACHINE_VISION_LIBRARY_CALIPER_H
#define MACHINE_VISION_LIBRARY_CALIPER_H

#include "opencv2/opencv.hpp"

#include <iostream>
#include <vector>

namespace mvp
{
    namespace caliper
    {
        /**
         * @brief 极值点信息
         */
        struct ExtremPointInfo
        {
            cv::Point2d pt;                  ///< 极值点像素坐标
            int ps;                          ///< 极值点在路径中的位置
            int value;                       ///< 极值
            double score;                    ///< 得分

            ExtremPointInfo(const cv::Point2d& _pt, const int& _ps, const int& _value) : pt(_pt), ps(_ps), value(_value), score(0) {}
        };

        // 以得分为条件比较极值点，用于排序
        static bool CompareExtremPointInfoBysocre(const ExtremPointInfo& ep1, const ExtremPointInfo& ep2)
        {
            return ep1.score > ep2.score;
        }

        // 以位置顺序为条件比较极值点，用于排序
        static bool CompareExtremPointInfoByPs(const ExtremPointInfo& ep1, const ExtremPointInfo& ep2)
        {
            return  ep1.ps > ep2.ps;
        }

        /**
         * @brief 卡尺工具
         */ 
        class Caliper
        {
        public:
            explicit Caliper(const cv::Point2d center, const size_t len, const double k);
            static cv::Ptr<Caliper> CreateInstance(const cv::Point2d center, const size_t len, const double k);
            void Init(cv::Mat inputImage);
            void SetParam();
            void SetParam(const std::string& name, const int& value);
            void Run();


        private:
            //1. 搜索
            void SearchCaliperPath();           //搜索卡尺路径，保存路径点集以供分析
            //2. 滤波
            void DifferenceFilter(const size_t& _filterSize);                //一维差分滤波处理卡尺路径像素值
            //3. 查找边缘点
            void FindExtremePoint();            //查找极值点
            //4. 筛选边缘点
            void ExtremePointRating();          //极值点评分

            // ----------必须参数--初始化时设置-----------------------------
            cv::Point2d center;                 //卡尺中心点坐标
            size_t len;                         //卡尺长度
            double k;                           //arctan(angle)
            double angle;                       //卡尺与x轴夹角

            //-------------调试参数-SetParam函数设置------------------------------
            size_t  filterSize;                 //滤波核半宽
            size_t  contrastThreshold;          //对比度阈值
            int  polarity;                      //搜索方向的极性:黑到白1、白到黑-1,不考虑0

            //-------------坐标系说明------------------------------
            //0---------------------x轴--------------------------->
            //:     .                               |
            //:             .                      angle
            //:                     .
            //y轴                  第一象限  .       |
            //:                                     .
            //:
            //V

            //-------------卡尺在x轴的投影范围---------------------
            double  min_x;
            double  max_x;                      // len*cos(angle)

            //-------------卡尺直线方程---------------------------
            // y = kx + b

            double b;
            std::vector<cv::Point2d> path;       //卡尺路径点集
            std::vector<int> pathPixelValue;     //卡尺路径点集对应像素值
            std::vector<int> pathPixelValueAfterFilter;  //卡尺路径点集对应像素值(滤波处理后）

            std::vector<ExtremPointInfo> extremePoints;      //极值点
        public:
            cv::Mat input_image_;
            //-------------卡尺结果-------------------------------
            //保留前、中、后三个点,极性最强点(最强点属于三个点之一）,如果找不到统一默认为输入的center坐标点
            struct Result
            {
                cv::Point2d front;
                cv::Point2d center;
                cv::Point2d back;
                cv::Point2d peak;
            } result;
        };//Caliper

    }//namespace caliper  
}//namespace mvp
#endif //MACHINE_VISION_LIBRARY_CALIPER_H
