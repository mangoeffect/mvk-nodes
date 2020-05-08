//
// Created by mango on 4/10/2020.
//

#include "linefit.h"

#include <cassert>

using namespace mv;


// 构造函数 
LineFit::LineFit(const std::vector<cv::Point2d>& points, const FitAlgorithms& fitAlgorithms, const int& maxIter)
	: _points(points), _fitAlgorithms(fitAlgorithms), _maxIter(maxIter)
{
	_outlierThreshold = 3;							//离群点阈值

	_function.n = 2;								//变量个数

	_function.f = HuberLossFunc;

	_startPoint = gsl_vector_alloc(_function.n);
	_stepSize = gsl_vector_alloc(_function.n);

	_fminimizer = gsl_multimin_fminimizer_alloc(gsl_multimin_fminimizer_nmsimplex, 2);
}//LineFit

LineFit::~LineFit()
{
	// 释放资源
	gsl_vector_free(_startPoint);
	gsl_vector_free(_stepSize);

	gsl_multimin_fminimizer_free(_fminimizer);
}//~LineFit

void LineFit::SetStartPoint(const double& a, const double& b)
{
	gsl_vector_set(_startPoint, 0, a);
	gsl_vector_set(_startPoint, 1, b);
}//SetStartPoint


// Huber loss
double LineFit::HuberLossFunc(const gsl_vector * v, void * params)
{
	std::vector<cv::Point2d> *vect = static_cast<std::vector<cv::Point2d>*>(params);
	int N = static_cast<int>(vect->size());

	double a, b;
	a = gsl_vector_get(v, 0);
	b = gsl_vector_get(v, 1);

	double sum = 0;

	for (int i = 0; i < N; i++)
	{
		double yi = vect->at(i).y;
		double fi = a * vect->at(i).x + b;
		double dist = std::fabs(yi - fi);
		// huber loss
		if (dist <= _outlierThreshold)
		{
			dist = 0.5 * dist * dist;
			// 更新权重
			_weigths.at(i) = 1;
		}
		else
		{
			dist = _outlierThreshold * dist - 0.5 * _outlierThreshold * _outlierThreshold;
			// 更新权重
			_weigths.at(i) = _outlierThreshold / std::fabs(dist);
		}
		sum += std::fabs(dist);
	}
	return sum / N;
}//huber loss

// tukey loss
double LineFit::TukeyLossFunc(const gsl_vector * v, void * params)
{
	std::vector<cv::Point2d> *vect = static_cast<std::vector<cv::Point2d>*>(params);
	int N = static_cast<int>(vect->size());

	double a, b;
	a = gsl_vector_get(v, 0);
	b = gsl_vector_get(v, 1);

	double sum = 0;

	for (int i = 0; i < N; i++)
	{
		double yi = vect->at(i).y;
		double fi = a * vect->at(i).x + b;
		double dist = std::fabs(yi - fi * _weigths.at(i));
		// tukey loss
		if (dist <= _outlierThreshold)
		{
			dist = (1 - std::pow((1.0 - std::pow(dist, 2) / std::pow(_outlierThreshold, 2)), 3)) * _outlierThreshold * _outlierThreshold / 6;
			// 更新权重
			_weigths.at(i) = 1;
		}
		else
		{
			dist = _outlierThreshold * _outlierThreshold / 6;
			// 更新权重
			_weigths.at(i) = _outlierThreshold / std::fabs(dist);
		}
		sum += std::fabs(dist);
	}

	return sum / N;
}// tukey loss

cv::Ptr<mv::LineFit> mv::LineFit::CreateInstance(const std::vector<cv::Point2d> &points, const FitAlgorithms &fitAlgorithms)
{
    return  cv::makePtr<mv::LineFit>(points, fitAlgorithms);
}//CreateInstance

void mv::LineFit::Run()
{
    switch (_fitAlgorithms)
    {
        case FitAlgorithms ::REGRESSION:
            FitLineByRegression();
            break;
        case FitAlgorithms ::HUBER:
            FitLineByHuber();
            break;
        case FitAlgorithms ::TUKEY:
            FitLineByTukey();
            break;
        case FitAlgorithms ::DROP:
            FitLineByDrop();
            break;
        case FitAlgorithms ::GAUSS:
            FitLineByGauss();
            break;
        default:
            assert(false);
    }
}//Run

void mv::LineFit::FitLineByRegression()
{
    // 设置权重 | weights setting
    _weigths = std::vector<double>(_points.size(), 1);

    // AX = B
    // 构造A矩阵 | Construct A mat
    const int N = 2;
    cv::Mat A = cv::Mat::zeros(N, N, CV_64FC1);

    for (int row = 0;row < A.rows;row++)
    {
        for (int col = 0; col < A.cols;col++)
        {
            for (int k = 0;k < _points.size();k++)
            {
                A.at<double>(row, col) = A.at<double>(row, col) + pow(_points[k].x, row + col) * _weigths[k];
            }
        }
    }

    //构造B矩阵 | Construct B mat
    cv::Mat B = cv::Mat::zeros(N, 1, CV_64FC1);
    for (int row = 0;row < B.rows;row++)
    {

        for (int k = 0;k < _points.size();k++)
        {
            B.at<double>(row, 0) = B.at<double>(row, 0) + pow(_points[k].x, row)*_points[k].y * _weigths[k];
        }
    }

    // 求解A*X = B | Solve the A*X = B
    cv::Mat X;
    cv::solve(A, B, X,cv::DECOMP_LU);

    // y = b + ax
    _result.b = X.at<double>(0,0);
    _result.a = X.at<double>(1, 0);

}//FitLineByRegression

void mv::LineFit::FitLineByHuber()
{
	_function.params = (void *)&_points;


	// 用最小二乘拟合的结果作为初始值
	FitLineByRegression();

	// 设置初始值
	SetStartPoint(_result.a, _result.b);

	//经验值，初始步长十分之一 
	gsl_vector_set(_stepSize, 0, _result.a / 10.0);
	gsl_vector_set(_stepSize, 1, _result.b / 10.0);

	gsl_multimin_fminimizer_set(_fminimizer, &_function, _startPoint, _stepSize);

	int iter = 0;
	int status;
	do
	{
		iter++;
		status = gsl_multimin_fminimizer_iterate(_fminimizer);
		if (status == GSL_ENOPROG) // 表示无法找到更好的解了
		{
			break;
		}
		double size = gsl_multimin_fminimizer_size(_fminimizer);

		status = gsl_multimin_test_size(size, 1e-2);
	} while (status == GSL_CONTINUE && iter < _maxIter);

	gsl_vector * out = gsl_multimin_fminimizer_x(_fminimizer);

	_result.a = gsl_vector_get(out, 0);
	_result.b = gsl_vector_get(out, 1);

}//FitLineByHuber

void mv::LineFit::FitLineByTukey()
{

}//FitLineByTukey

void mv::LineFit::FitLineByDrop()
{

}//FitLineByDrop


void mv::LineFit::FitLineByGauss()
{

}//FitLineByGauss


mv::LineFitResult mv::LineFit::GetResult() const
{
    return this->_result;
}//GetResult