//
// Created by mango on 5/08/2020.
//

#include"multimin.h"
#include<iostream>

using namespace mv;

MultiMin::MultiMin()
{
	// ����Ĭ��ֵ
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
		// ��i����������������ݶ�
		gradient = (fh - f) / h;
		funcGradient.push_back(gradient);
	}
}

//
bool MultiMin::Run(const std::vector<cv::Point2d>& points, std::vector<double>& weights, const std::vector<double>& otherData)
{
	// ������ʼλ��
	std::vector<double> iterVale = _start;
	std::vector<double> gradient(iterVale.size(), 0);

	double funcValue = 0;				//��ǰ����ֵ
	double lastFuncValue = 1e10;		//��һ�κ���ֵ
	int stayConvergeTimes = 0;			//פ����������

	// ��ʼ����
	_iterationNum = 0;
	for (size_t i = 0; i < _maxIter; i++)
	{
		_iterationNum++;
		// �����ݶ�
		CalculateGradient(points, weights, iterVale, otherData, gradient);

		// �ݶ��½���ʽ��������
		for (size_t j = 0; j < iterVale.size(); j++)
		{
			iterVale.at(j) -= _stepSize * gradient.at(j);
		}

		// ���¼��㵱ǰ����ֵ
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