//
// Created by mango on 4/10/2020.
//

#ifndef MACHINE_VISION_LIBRARY_LINEFIT_H
#define MACHINE_VISION_LIBRARY_LINEFIT_H

//-------------OpenCV----------
#include "opencv2/opencv.hpp"

//--------------GSL-------------
#include "gsl/gsl_vector.h"
#include "gsl/gsl_multimin.h"


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
		explicit LineFit(const std::vector<cv::Point2d>& points, const FitAlgorithms& fitAlgorithms = FitAlgorithms::REGRESSION, const int& maxIter = 100);
		~LineFit();

        static  cv::Ptr<LineFit> CreateInstance(const std::vector<cv::Point2d>& points, const FitAlgorithms& fitAlgorithms = FitAlgorithms::REGRESSION);

        void Run();


        LineFitResult GetResult() const;
    private:

		//--------------------------------------拟合算法 | fit algorithms------------------------------------------------
		void FitLineByRegression();
		void FitLineByHuber();
		void FitLineByTukey();
		void FitLineByDrop();
		void FitLineByGauss();

		//--------------------------------------迭代参数 | iteration parameters------------------------------
		int _maxIter;									//迭代最大次数
		static int _outlierThreshold;					//离群阈值，超过此值被判定为离群点
		gsl_multimin_function _function;				//迭代函数
		gsl_multimin_fminimizer * _fminimizer;			//迭代优化器
		gsl_vector *_startPoint;						//迭代算法的初始值
		gsl_vector *_stepSize;							//迭代算法的初始步长
		

		void SetStartPoint(const double& a, const double& b);						//设置迭代起始点
		static double HuberLossFunc(const gsl_vector * v, void * params);		    //目标函数
		static double TukeyLossFunc(const gsl_vector * v, void * params);

        //---------------------------------------- 输入 | input----------------------------------------------
        std::vector<cv::Point2d> _points;
        FitAlgorithms _fitAlgorithms;
        static std::vector<double> _weigths;

        //-----------------------------------------输出 | output---------------------------------------------
        LineFitResult _result;
    };//class LineFit

}//namespace  mv

#endif //MACHINE_VISION_LIBRARY_LINEFIT_H
