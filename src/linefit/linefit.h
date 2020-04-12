//
// Created by mango on 4/10/2020.
//

#ifndef MACHINE_VISION_LIBRARY_LINEFIT_H
#define MACHINE_VISION_LIBRARY_LINEFIT_H

#include "opencv2/opencv.hpp"

namespace  mv
{
    enum  class FitAlgorithms
    {
//        Algorithm 拟合直线算法
//
//        'regression' 标准的最小二乘拟合
//        'huber' 加权最小二乘拟合，通过Huber方法减小离群点的影响
//        'tukey' 加权最小二乘拟合，通过Tukey方法减小离群点的影响
//        'drop'：加权的最小二乘法拟合，异常值的影响被消除
//        'gauss'：加权的最小二乘法拟合，异常值的影响被减小基于最逼近线上的所有其轮廓点的平均值和距离标准方差
        REGRESSION = 0,
        HUBER,
        TUKEY,
        DROP,
        GAUSS
    };//enum  class FitAlgorithms

    struct LineFitResult
    {
        // y = ax + b
        double a;
        double b;
    };//

    class LineFit
    {
    public:
        explicit LineFit(const std::vector<cv::Point2d>& points, const FitAlgorithms& fitAlgorithms = FitAlgorithms::REGRESSION)
                :  _points(points), _fitAlgorithms(fitAlgorithms){}

        static  cv::Ptr<LineFit> CreateInstance(const std::vector<cv::Point2d>& points, const FitAlgorithms& fitAlgorithms = FitAlgorithms::REGRESSION);

        void Run();

        //--------------------------------------拟合算法 | fit algorithms
        void FitLineByRegression();
        void FitLineByHuber();
        void FitLineByTukey();
        void FitLineByDrop();
        void FitLineByGauss();

        LineFitResult GetResult() const;
    private:
        //---------------------------------------- 输入 | input----------------------------------------------
        std::vector<cv::Point2d> _points;
        FitAlgorithms _fitAlgorithms;

        //-----------------------------------------输出 | output---------------------------------------------
        LineFitResult result;
    };//class LineFit

}//namespace  mv

#endif //MACHINE_VISION_LIBRARY_LINEFIT_H
