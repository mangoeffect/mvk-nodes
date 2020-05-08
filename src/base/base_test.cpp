//
// Created by mango on 5/08/2020.
//

//#include"base.h"
#include"multimin.h"
#include"opencv2/opencv.hpp"

#include<iostream>

using namespace mv;

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

class HuberFit : public MultiMin
{
public:
	HuberFit();
	~HuberFit();

	double Func(const std::vector<cv::Point2d>& points, std::vector<double>& weights, const std::vector<double>& funcParameters, const std::vector<double>& otherData) override;

private:

};

double HuberFit::Func(const std::vector<cv::Point2d>& points, std::vector<double>& weights, const std::vector<double>& funcParameters, const std::vector<double>& otherData)
{
	int N = points.size();
	double a = funcParameters.at(0);
	double b = funcParameters.at(1);
	double outlierThreshold = otherData.at(0);

	double sum = 0;
	for (int i = 0; i < N; i++)
	{
		double yi = points.at(i).y;
		double fi = a * points.at(i).x + b;
		double dist = std::fabs(yi - fi);
		// huber loss
		if (dist <= outlierThreshold)
		{
			dist = 0.5 * dist * dist;
			// 更新权重
			weights.at(i) = 1;
		}
		else
		{
			dist = outlierThreshold * dist - 0.5 * outlierThreshold * outlierThreshold;
			// 更新权重
			weights.at(i) = outlierThreshold / std::fabs(dist);
		}
		sum += std::fabs(dist);
	}

	return sum / N;
}

HuberFit::HuberFit()
{
}

HuberFit::~HuberFit()
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

	HuberFit  huber;
	double a, b;
	LeastSquareLineFit(pts, w, a, b );

	std::cout << a << " " << b << std::endl;

	huber.SetStart({ a, b });
	huber.SetMaxtIter(3000);
	//huber.SetStepSize(0.1 * a);

	bool res = huber.Run(pts, w, { 2 });
   
	if (res)
	{
		std::vector<double> result = huber.GetResult();
		std::cout << result.at(0) << " " << result.at(1) << std::endl;
	}

	std::cout << huber.GetIeterNum() << std::endl;

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