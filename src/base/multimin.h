//
// Created by mango on 5/08/2020.
//

#ifndef MACHINE_VISION_LIBRARY_MULTIMIN_H
#define MACHINE_VISION_LIBRARY_MULTIMIN_H

#include "opencv2/core/core.hpp"



#include <vector>

namespace mv
{
	class MultiMin
	{
	public:
		MultiMin();
		~MultiMin();
		virtual double Func(const std::vector<cv::Point2d>& points, std::vector<double>& weights, const std::vector<double>& funcParameters, const std::vector<double>& otherData) = 0;

		bool Run(const std::vector<cv::Point2d>& points, std::vector<double>& weights, const std::vector<double>& otherData);

		//----------------------------------------�������� | Set property ---------------------------------------------
		void SetStart(const std::vector<double>& starts);
		void SetMaxtIter(const unsigned int& maxIetr);
		void SetStepSize(const double& stepSize);
		void SetLearningRate(const double& learningRate);
		void SetConvergeThreshold(const double& convergeThreshold);

		//----------------------------------------��ȡ���� | Get property ---------------------------------------------
		std::vector<double> GetLossRecord() const { return _lossRecord; }
		std::vector<double> GetResult()const { return _result; }
		double GetIeterNum() const { return _iterationNum; };

	private:
		void CalculateGradient(const std::vector<cv::Point2d>& points, std::vector<double>& weights,
			const std::vector<double>& funcParameters, const std::vector<double>& otherData, std::vector<double>& funcGradient);

		//------------------------------------------������� | input parameters------------------------------------
		unsigned int _maxIter;							// ���������� | max iteration num
		std::vector<double> _start;						// �������	   | iteration start points
		double _stepSize;								// ��������	   | iteration step size
		double _learningRate;							// ѧϰ���ʣ��벽��ͬ�壩 | learning rate (same as step size)
		double _convergeThreshold;						// ������ֵ
	

		//------------------------------------------��� | output---------------------------------------------------
		unsigned int _iterationNum;						// ����ʱ�������� | real iteration num in runtime
		bool _status;									// ����״̬		| iteration status
		std::vector<double> _result;
		std::vector<double> _lossRecord;				// ��ʧֵ�� ��¼������������ | loss value: tracking the iteration
	};


}//namespace  mv

#endif //MACHINE_VISION_LIBRARY_MULTIMIN_H
