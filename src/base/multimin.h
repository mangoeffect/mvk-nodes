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

		//----------------------------------------设置属性 | Set property ---------------------------------------------
		void SetStart(const std::vector<double>& starts);
		void SetMaxtIter(const unsigned int& maxIetr);
		void SetStepSize(const double& stepSize);
		void SetLearningRate(const double& learningRate);
		void SetConvergeThreshold(const double& convergeThreshold);

		//----------------------------------------获取属性 | Get property ---------------------------------------------
		std::vector<double> GetLossRecord() const { return _lossRecord; }
		std::vector<double> GetResult()const { return _result; }
		double GetIeterNum() const { return _iterationNum; };

	private:
		void CalculateGradient(const std::vector<cv::Point2d>& points, std::vector<double>& weights,
			const std::vector<double>& funcParameters, const std::vector<double>& otherData, std::vector<double>& funcGradient);

		//------------------------------------------输入参数 | input parameters------------------------------------
		unsigned int _maxIter;							// 最大迭代次数 | max iteration num
		std::vector<double> _start;						// 迭代起点	   | iteration start points
		double _stepSize;								// 迭代步长	   | iteration step size
		double _learningRate;							// 学习速率（与步长同义） | learning rate (same as step size)
		double _convergeThreshold;						// 收敛阈值
	

		//------------------------------------------输出 | output---------------------------------------------------
		unsigned int _iterationNum;						// 运行时迭代次数 | real iteration num in runtime
		bool _status;									// 迭代状态		| iteration status
		std::vector<double> _result;
		std::vector<double> _lossRecord;				// 损失值： 记录迭代收敛过程 | loss value: tracking the iteration
	};


}//namespace  mv

#endif //MACHINE_VISION_LIBRARY_MULTIMIN_H
