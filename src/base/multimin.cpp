//
// Created by mango on 5/08/2020.
//

#include "multimin.h"
#include <iostream>

namespace mvp
{
	MultiMin::MultiMin():max_iter_(100) , start_({0}), step_size_(0.001), 
		gradient_step_size_(1e-4),converge_threshold_(1e-5), stay_converge_times_(10)
	{

	}

	MultiMin::~MultiMin()
	{

	}

	void MultiMin::SetStart(const std::vector<double>& start)
	{
		start_ = start;
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

	void MultiMin::SetGradientStepSize(const double& gradient_step_size)
	{
		gradient_step_size_ = gradient_step_size;
	}

	void MultiMin::SetStayConvergeTimes(const unsigned int& stay_converge_times)
	{
		stay_converge_times_ = stay_converge_times;
	}

    void MultiMin::CalculateGradient(const std::vector<cv::Point2d>& points, std::vector<double>& weights,
			const std::vector<double>& dependent_variables, const std::vector<double>& other_param, std::vector<double>& function_gradient)
	{
		function_gradient.clear();
		double h = gradient_step_size_;
		double gradient = 0;
		
		std::vector<double> fhv = dependent_variables;

		auto len = dependent_variables.size();
		for (size_t i = 0; i < len; i++)
		{
			fhv.at(i) += h;
			double f = GetLoss(points, weights, dependent_variables, other_param);
			double fh = GetLoss(points, weights, fhv, other_param);
			gradient = (fh - f) / h;
			function_gradient.emplace_back(gradient);
		}
	}

	//
	bool MultiMin::Run(const std::vector<cv::Point2d>& points, std::vector<double>& weights, const std::vector<double>& other_param)
	{

		std::vector<double> iter_vale = start_;
		std::vector<double> gradient(iter_vale.size(), 0);

		double func_value = 0;			
		double last_func_value = std::numeric_limits<double>::max();		
		uint stay_converge_times = 0;			

		
		loss_record_.clear();
		iteration_count_ = 0;

		for (size_t i = 0; i < max_iter_; i++)
		{
			iteration_count_++;
		
			CalculateGradient(points, weights, iter_vale, other_param, gradient);
			
			for (size_t j = 0; j < iter_vale.size(); j++)
			{
				iter_vale.at(j) -= step_size_ * gradient.at(j);
			}

			func_value = GetLoss(points, weights, iter_vale, other_param);
			
			double difference = std::abs(func_value - last_func_value);
			
			if (difference < converge_threshold_)
			{
				stay_converge_times++;
			}
			else
			{
				stay_converge_times = 0;
			}
			
			loss_record_.emplace_back(func_value);
			last_func_value = func_value;

			if (stay_converge_times > 10)
			{
				result_ = iter_vale;
				status_ = true;
				return status_;
			}
		}
		
		result_ = iter_vale;

		status_ = false;

		return status_;
	}
}//namespace mvp

