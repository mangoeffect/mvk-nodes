//
// Created by mango on 5/08/2020.
//

#include "multimin.h"
#include <iostream>

namespace mvp
{
	MultiMin::MultiMin():max_iter_(100) , start_({0}), step_size_(0.001), converge_threshold_(1e-5)
	{

	}

	MultiMin::~MultiMin()
	{

	}

	void MultiMin::SetStart(const std::vector<double>& starts)
	{
		starts_ = starts;
	}

	void MultiMin::SetMaxtIter(const unsigned int& max_iter)
	{
		max_iter_ = max_iter;
	}

	void MultiMin::SetStepSize(const double& step_size)
	{
		step_size_ = step_size;
	}

	void MultiMin::SetConvergeThreshold(const double& converge_threshold)
	{
		converge_threshold_ = converge_threshold;
	}


    void CalculateGradient(const std::vector<cv::Point2d>& points, std::vector<double>& weights,
			const std::vector<double>& dependent_variables, const std::vector<double>& other_param, std::vector<double>& function_gradient)
	{
		function_gradient.clear();
		double h = step_size_;
		double gradient = 0;
		
		std::vector<double> fhv = dependent_variables;
		for (size_t i = 0; i < dependent_variables.size(); i++)
		{
			fhv.at(i) += h;
			double f = GetLoss(points, weights, dependent_variables, other_param);
			double fh = GetLoss(points, weights, fhv, other_param);
			gradient = (fh - f) / h;
			function_gradient.push_back(gradient);
		}
	}

	//
	bool MultiMin::Run(const std::vector<cv::Point2d>& points, std::vector<double>& weights, const std::vector<double>& other_param)
	{

		std::vector<double> iterVale = start_;
		std::vector<double> gradient(iterVale.size(), 0);

		double funcValue = 0;			
		double lastFuncValue = 1e9;		
		int stayConvergeTimes = 0;			

		
		loss_record_.clear();
		iteration_count_ = 0;

		for (size_t i = 0; i < max_iter_; i++)
		{
			iteration_count_++;
		
			CalculateGradient(points, weights, iterVale, other_param, gradient);
			
			for (size_t j = 0; j < iterVale.size(); j++)
			{
				iterVale.at(j) -= _stepSize * gradient.at(j);
			}

			
			funcValue = GetLoss(points, weights, iterVale, other_param);
			
			double difference = std::abs(funcValue - lastFuncValue);
			
			if (difference < converge_threshold_)
			{
				stayConvergeTimes++;
			}
			else
			{
				stayConvergeTimes = 0;
			}
			
			loss_record_.push_back(funcValue);
			lastFuncValue = funcValue;

			if (stayConvergeTimes > 10)
			{
				result_ = iterVale;
				status_ = true;
				return status_;
			}
		}
		
		result_ = iterVale;

		status_ = false;

		return status_;
	}
}//namespace mvp

