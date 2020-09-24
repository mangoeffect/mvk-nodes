//
// Created by mango on 4/10/2020.
//

#include"linefit.h"

#include<iostream>
#include<vector>
#include<cmath>

enum class OutlierType
{
	RANDOM = 0,
	GAUSS,
	SINGLE_DIRECTION
};

// 构造拟合点
void CreatePoints(const cv::Size& planeSize, std::vector<cv::Point2d>& points, const cv::Point2d& lineStart, const int& angle, const size_t& len, const size_t& outlierNum = 10, const size_t& distance = 0, const OutlierType& type = OutlierType::RANDOM);

int main()
{
	std::vector<cv::Point2d> pts;
	CreatePoints({ 1000,800 }, pts, { 200.0 , 120.0 }, 30, 350, 20, 35);

	cv::Mat img = cv::Mat(800, 1000, CV_8UC3, cv::Scalar::all(255));


	for (size_t i = 0; i < pts.size(); i++)
	{
		cv::circle(img, pts.at(i), 1, cv::Scalar(255, 0, 0));
	}

	cv::Ptr<mv::LineFit> lineFit = mv::LineFit::CreateInstance(pts,mv::FitAlgorithms::REGRESSION);
	
	lineFit->Run();

	mv::LineFitResult res = lineFit->GetResult();
	
	cv::Point2d lineStart, lineEnd;
	lineStart = { 200, 120 };
	lineEnd.x = 200 + 350;
	lineEnd.y = res.a * lineEnd.x + res.b;

	cv::line(img, lineStart, lineEnd, cv::Scalar(0, 255, 0), 2);

	cv::imshow("Create points", img);
	cv::waitKey(0);

	return 0;
}


void CreatePoints(const cv::Size& planeSize, std::vector<cv::Point2d>& points, const cv::Point2d& lineStart, const int& angle, const size_t& len, const size_t& outlierNum, const size_t& distance, const OutlierType& type)
{
	points.clear();
	const double PI = std::acos(-1);

	// 创建聚合点
	srand((unsigned)time(nullptr));
	for (int i = 0; i < len; i++)
	{
		double x = lineStart.x + i;
		double yOffset = static_cast<double>(i) * std::tan(static_cast<double>(angle) * PI / 180) + rand() % distance - 0.5*distance;
		double y = lineStart.y + yOffset;

		if (x > 0 && x < planeSize.width && y > 0 && y < planeSize.height)
		{
			points.push_back({ x, y });
		}
	}

	// 创建离群点

	switch (type)
	{
	case OutlierType::GAUSS:
		break;
	case OutlierType::RANDOM:
		srand((unsigned)time(nullptr));
		for (size_t i = 0; i < outlierNum; i++)
		{
			double x = rand() % planeSize.width;
			double y = rand() % planeSize.height;
			points.push_back({ x, y });
		}
		break;
	case OutlierType::SINGLE_DIRECTION:
		break;
	default:
		break;
	}
}