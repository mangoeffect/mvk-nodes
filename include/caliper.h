//
// Created by $mango on 4/2/2020.
//

#ifndef MACHINE_VISION_LIBRARY_CALIPER_H
#define MACHINE_VISION_LIBRARY_CALIPER_H

#include "opencv2/opencv.hpp"
#include <iostream>
#include <vector>

namespace mv
{

    class Caliper
    {
    public:
        explicit Caliper(const cv::Point2d center, const size_t len, const double k, const size_t filterSize = 1);
        void Init(cv::Mat inputImage);
        void SetParam();
        void SetParam(const std::string name, const double value);
        void Run();


    private:
        void SearchCaliperPath();           //搜索卡尺路径，保存路径点集以供分析
        void DifferenceFilter(const size_t& _filterSize);                //一维差分滤波处理卡尺路径像素值


        cv::Point2d center;                 //卡尺中心点坐标
        size_t len;                         //卡尺长度
        double angle;                       //卡尺与x轴夹角
        size_t  filterSize;                 //滤波核半宽

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
        double k;                            //arctan(angle)
        int b;
        std::vector<cv::Point2d> path;       //卡尺路径点集
        std::vector<int> pathPixelValue;  //卡尺路径点集对应像素值
        std::vector<int> pathPixelValueAfterFilter;  //卡尺路径点集对应像素值(滤波处理后）
    public:
        cv::Mat inputImage;
        //-------------卡尺结果-------------------------------
        //保留前、中、后三个点
        struct result
        {
            cv::Point2d front;
            cv::Point2d center;
            cv::Point2d back;
        };
    };//Caliper
}//namespace mv
#endif //MACHINE_VISION_LIBRARY_CALIPER_H
