//
// Created by mango on 5/08/2020.
//

#include"multimin.h"
#include<iostream>

using namespace mv;

MultiMin::MultiMin()
{
	// 参数默认值
	_maxIter = 100;
	_learningRate = _stepSize = 0.001;
	_convergeThreshold = 1e-10;
	_status = false;
}

MultiMin::~MultiMin()
{

}


void MultiMin::SetStart(const std::vector<double>& starts)
{
	_start = starts;
}

void MultiMin::SetMaxtIter(const unsigned int& maxIetr)
{
	_maxIter = maxIetr;
}

void MultiMin::SetStepSize(const double& stepSize)
{
	_stepSize = stepSize;
	_learningRate = stepSize;
}

void MultiMin::SetLearningRate(const double& learningRate)
{
	_learningRate = learningRate;
	_stepSize = learningRate;
}

void MultiMin::SetConvergeThreshold(const double& convergeThreshold)
{
	_convergeThreshold = convergeThreshold;
}

void MultiMin::CalculateGradient(const std::vector<cv::Point2d>& points, std::vector<double>& weights,
	const std::vector<double>& funcParameters, const std::vector<double>& otherData, std::vector<double>& funcGradient)
{
	funcGradient.clear();
	double h = 1e-5;
	double gradient = 0;
	
	std::vector<double> fhv = funcParameters;
	for (size_t i = 0; i < funcParameters.size(); i++)
	{
		fhv.at(i) += h;
		double f = Func(points, weights, funcParameters, otherData);
		double fh = Func(points, weights, fhv, otherData);
		// 第i个函数变量方向的梯度
		gradient = (fh - f) / h;
		funcGradient.push_back(gradient);
	}
}

//
bool MultiMin::Run(const std::vector<cv::Point2d>& points, std::vector<double>& weights, const std::vector<double>& otherData)
{
	// 迭代起始位置
	std::vector<double> iterVale = _start;
	std::vector<double> gradient(iterVale.size(), 0);

	double funcValue = 0;				//当前函数值
	double lastFuncValue = 1e10;		//上一次函数值
	int stayConvergeTimes = 0;			//驻留收敛次数

	// 开始迭代
	_iterationNum = 0;
	for (size_t i = 0; i < _maxIter; i++)
	{
		_iterationNum++;
		// 计算梯度
		CalculateGradient(points, weights, iterVale, otherData, gradient);

		// 梯度下降公式迭代修正
		for (size_t j = 0; j < iterVale.size(); j++)
		{
			iterVale.at(j) -= _stepSize * gradient.at(j);
		}

		// 重新计算当前函数值
		funcValue = Func(points, weights, iterVale, otherData);
		
		double difference = std::abs(funcValue - lastFuncValue);
		
		if (difference < _convergeThreshold)
		{
			stayConvergeTimes++;
		}
		else
		{
			stayConvergeTimes = 0;
		}
		
		lastFuncValue = funcValue;

		if (stayConvergeTimes > 10)
		{
			_result = iterVale;
			_status = true;
			return _status;
		}
	}
	std::cout << iterVale.at(0) << " " << iterVale.at(1) << std::endl;
	_result = iterVale;

	_status = false;
	return _status;
}