//
// Created by mango on 5/08/2020.
//

#include"multimin.h"
#include"opencv2/opencv.hpp"
#include"matplotlibcpp.h"

#include<iostream>

using namespace mv;
namespace plt = matplotlibcpp;


bool LeastSquareLineFit(const std::vector<cv::Point2d>& points, const std::vector<double>& weights, double&a, double& b);

enum class PointType
{
	LINE = 0,
	LINE_WITH_OUTLIER,
	CIRCLE,
	CIRCLE_WITH_OUTLIER
};

void CreateData(std::vector<cv::Point2d>& pts, PointType pointType)
{
	cv::Point2d center = { 500, 500 };

	int radius = 200;

	cv::Point2d lineStart = { 100, 100 };


	pts.clear();

	cv::Point2d pt;
	srand((unsigned)time(nullptr));

	switch (pointType)
	{
	case PointType::LINE:
		for (size_t i = 0; i < 300; i++)
		{
			pt.x = lineStart.x + i;
			pt.y = lineStart.x + i + (rand() % 30) - 15;
			pts.push_back(pt);
		}
		break;
	case PointType::LINE_WITH_OUTLIER:
		for (size_t i = 0; i < 300; i++)
		{
			pt.x = lineStart.x + i;
			pt.y = lineStart.x + i + (rand() % 30) - 15;
			pts.push_back(pt);
		}
		lineStart = { 300, 200 };
		for (size_t i = 0; i < 50; i++)
		{
			pt.x = lineStart.x + i;
			pt.y = lineStart.x + i + (rand() % 30) - 15 - 70;
			pts.push_back(pt);
		}
		break;
	case PointType::CIRCLE:
		for (size_t i = 0; i < 360; i++)
		{
			pt.x = center.x + radius * std::cos(i) + (rand() % 30) - 15;
			pt.y = center.y + radius * std::sin(i) + (rand() % 30) - 15;
			pts.push_back(pt);
		}
		break;
	case PointType::CIRCLE_WITH_OUTLIER:
		for (size_t i = 0; i < 360; i++)
		{
			pt.x = center.x + radius * std::cos(i) + (rand() % 30) - 15;
			pt.y = center.y + radius * std::sin(i) + (rand() % 30) - 15;
			pts.push_back(pt);
		}
		// 干扰数据
		center = { 300, 300 };
		radius = 50;
		for (size_t i = 0; i < 36; i++)
		{
			pt.x = center.x + radius * std::cos(i) + (rand() % 30) - 15;
			pt.y = center.y + radius * std::sin(i) + (rand() % 30) - 15;
			pts.push_back(pt);
		}
		break;
	default:
		break;
	}
}

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


class MultiminTest: public MultiMin
{
public:
	MultiminTest();
	~MultiminTest();

	double Func(const std::vector<cv::Point2d>& points, std::vector<double>& weights, const std::vector<double>& funcParameters, const std::vector<double>& otherData) override;

private:
	double HuberLoss(const std::vector<cv::Point2d>& points, std::vector<double>& weights, const std::vector<double>& funcParameters, const double& outlierThreshold);
	double MAELoss(const std::vector<cv::Point2d>& points, std::vector<double>& weights, const std::vector<double>& funcParameters);

	FitAlgorithms _fitAlgorithms;
};


double MultiminTest::MAELoss(const std::vector<cv::Point2d>& points, std::vector<double>& weights, const std::vector<double>& funcParameters)
{
	int N = static_cast<int>(points.size());

	double a = funcParameters.at(0);
	double b = funcParameters.at(1);
	//MAELoss
	double sum = 0;
	for (int i = 0; i < N; i++)
	{
		double yi = points.at(i).y;
		double fi = a * points.at(i).x + b;
		double dist = std::abs(yi - fi);

		sum += dist;
	}

	return sum / N;
}//MAELoss

double MultiminTest::HuberLoss(const std::vector<cv::Point2d>& points, std::vector<double>& weights, const std::vector<double>& funcParameters, const double& outlierThreshold)
{
	int N = static_cast<int>(points.size());

	double a = funcParameters.at(0);
	double b = funcParameters.at(1);
	
	double sum = 0;
	for (int i = 0; i < N; i++)
	{
		double yi = points.at(i).y;
		double fi = a * points.at(i).x + b;
		double dist = std::abs(yi - fi);
		// huber loss
		if (dist <= outlierThreshold)
		{
			// 更新权重
			weights.at(i) = 1;
			dist = 0.5 * dist * dist;
		}
		else
		{
			// 更新权重
			weights.at(i) = outlierThreshold / std::abs(dist);
			dist = outlierThreshold * dist - 0.5 * outlierThreshold * outlierThreshold;
			//dist *= weights.at(i);
		}
		sum += std::abs(dist);
	}

	return sum / N;
}//HuberLoss

double MultiminTest::Func(const std::vector<cv::Point2d>& points, std::vector<double>& weights, const std::vector<double>& funcParameters, const std::vector<double>& otherData)
{
	double outlierThreshold = otherData.at(0);

	double sum = 0;

	switch (_fitAlgorithms)
	{
	case FitAlgorithms::REGRESSION:
		break;
	case FitAlgorithms::HUBER:
		sum = HuberLoss(points, weights, funcParameters, outlierThreshold);
		break;
	case FitAlgorithms::TUKEY:
		break;
	case FitAlgorithms::DROP:
		break;
	case FitAlgorithms::GAUSS:
		break;
	default:
		break;
	}
	
	return sum;
}

MultiminTest::MultiminTest()
{

}

MultiminTest::~MultiminTest()
{
}

int main()
{
	cv::Mat img = cv::Mat(800, 1000, CV_8UC3, cv::Scalar::all(255));

	std::vector<cv::Point2d> pts;
	CreateData(pts, PointType::LINE_WITH_OUTLIER);

	for (size_t i = 0; i < pts.size(); i++)
	{
		cv::circle(img, pts.at(i), 1, cv::Scalar(255, 0, 0));
	}
	std::vector<double> w(pts.size(), 1);

	MultiminTest  multimin;
	double a, b;
	LeastSquareLineFit(pts, w, a, b );

	std::cout << a << " " << b << std::endl;

	multimin.SetStart({ a, b });
	multimin.SetMaxtIter(100);
	multimin.SetStepSize(0.0001);
	multimin.SetConvergeThreshold(0.0001);

	bool res = multimin.Run(pts, w, { 4 });
   
	std::vector<double> result;
	if (res)
	{
		result = multimin.GetResult();
		std::cout << result.at(0) << " " << result.at(1) << std::endl;
	}

    result = multimin.GetResult();
	cv::Point2d s1, s2, e1, e2;
	s1 = s2 = { 100, 100 };
	e1.x = e2.x = 100 + 300;
	e1.y = a * e1.x + b;
	e2.y = result.at(0) * e2.x + result.at(1);

	std::cout << multimin.GetIeterNum() << std::endl;

	cv::line(img, s1, e1, cv::Scalar(0, 0, 255), 2);
	cv::line(img, s2, e2, cv::Scalar(0, 255, 0), 2);

	std::vector<double> loss = multimin.GetLossRecord();

	plt::plot(loss);
	plt::show();
	

	cv::imshow("base-multimin-test", img);
	cv::waitKey(0);
	return 0;
}


bool LeastSquareLineFit(const std::vector<cv::Point2d>& points, const std::vector<double>& weights, double&a, double& b)
{
	// AX = B
   // 构造A矩阵 | Construct A mat
	const int N = 2;
	cv::Mat A = cv::Mat::zeros(N, N, CV_64FC1);

	for (int row = 0; row < A.rows; row++)
	{
		for (int col = 0; col < A.cols; col++)
		{
			for (int k = 0; k < points.size(); k++)
			{
				A.at<double>(row, col) = A.at<double>(row, col) + pow(points[k].x, row + col) * weights[k];
			}
		}
	}

	//构造B矩阵 | Construct B mat
	cv::Mat B = cv::Mat::zeros(N, 1, CV_64FC1);
	for (int row = 0; row < B.rows; row++)
	{

		for (int k = 0; k < points.size(); k++)
		{
			B.at<double>(row, 0) = B.at<double>(row, 0) + pow(points[k].x, row)*points[k].y * weights[k];
		}
	}

	// 求解A*X = B | Solve the A*X = B
	cv::Mat X;
	cv::solve(A, B, X, cv::DECOMP_LU);

	// y = b + ax
	b = X.at<double>(0, 0);
	a = X.at<double>(1, 0);

	return true;
}