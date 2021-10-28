//
// Created by mango on 5/08/2020.
//

#ifndef MVP_MULTIMIN_H
#define MVP_MULTIMIN_H

#include "opencv2/core/core.hpp"
#include <vector>

namespace mvp
{
    /**
     * @brief 求解多元函数极小值
     */
	class MultiMin
	{
	public:
	    /**
		 * @brief 构造函数 | constructor 
		 */
		MultiMin();

		/**
		 * @brief 析构函数 | destructor
		 */
		~MultiMin();
 
        /**
		 * @brief 获取目标函数损失值 | Get target function loss
		 * @param points(in) 点集数据 | points set data
		 * @param weights(in) 权重参数 | weigths parameters
		 * @param dependent_variables(in) 函数因变量 | dependent variable of the funciton
		 * @param other_param(in) 其他参数 | other parameters
		 * @return 函数值 | value of function
		 */
		virtual double GetLoss(const std::vector<cv::Point2d>& points, std::vector<double>& weights, const std::vector<double>& dependent_variables, const std::vector<double>& other_param) = 0;

        /**
		 * @brief 运行算法求解使得函数达到最小值的因变量 | running the algorithm to compute the dependent variabbles  that causes the function to reach its minimum value
		 * @param points(in) 点集数据 | points set data
		 * @param weights(in) 权重参数 | weigths parameters
		 * @param dependent_variables(in) 函数因变量 | dependent variable of the funciton
		 * @param other_param(in) 其他参数 | other parameters
		 * @return 函数运行状态 | the state of function running
		 */
		bool Run(const std::vector<cv::Point2d>& points, std::vector<double>& weights, const std::vector<double>& other_param);


		//----------------------------------------设置属性 | Set property ---------------------------------------------

        /**
		 * @brief 设置迭代起点 | Set iteration start points
		 * @param start(in) 迭代起点 | iteration start points
		 */
		void SetStart(const std::vector<double>& start);

		/**
		 * @brief 设置最大迭代次数 | Set the maximum  num of iteration
		 * @param max_iter(in) 最大迭代次数 | maximum num of iteration
		 */
		void SetMaxtIter(const unsigned int& max_iter);
		
		/**
		 * @brief 设置迭代步长 | Set the step size of iteration
		 * @param step_size(in) 迭代步长 | step size of iteration
		 */
		void SetStepSize(const double& stepSize);

        /**
		 * @brief 设置迭代收敛阈值 |  Set the threshold of iteratoin converge
		 * @param converge_threshold(in) 收敛阈值 |  threshold of iteratoin converge
		 */
		void SetConvergeThreshold(const double& convergeThreshold);

		/**
		 * @brief 设置梯度步长 | Set the step size of gradient
		 * @param gradient_step_size(in) 梯度步长 | step size of gradient
		 */
		void SetGradientStepSize(const double& gradient_step_size);


		/**
		 * @brief 设置收敛驻留次数 | Set the stay times of converge
		 * @param stay_converge_times(in) 驻留次数 | stay times
		 */
		void SetStayConvergeTimes(const unsigned int& stay_converge_times);


		//----------------------------------------获取属性 | Get property ---------------------------------------------
		std::vector<double> GetLossRecord() const { return loss_record_; }
		std::vector<double> GetResult()const { return result_; }
		double GetIeterNum() const { return iteration_count_; };

	private:
	    /**
		 * @brief 计算梯度 | calculate the gradient
		 * @param points(in) 点集数据 | points set data
		 * @param weights(in) 权重参数 | weigths parameters
		 * @param dependent_variables(in) 函数因变量 | dependent variable of the funciton
		 * @param other_param(in) 其他参数 | other parameters
		 * @param function_gradient(out) 函数梯度值 | gradients of function
		 */
		 void CalculateGradient(const std::vector<cv::Point2d>& points, std::vector<double>& weights,
			const std::vector<double>& dependent_variables, const std::vector<double>& other_param, std::vector<double>& function_gradient);

		//------------------------------------------输入参数 | input parameters------------------------------------
		unsigned int max_iter_;							///<  最大迭代次数  | max iteration num
		std::vector<double> start_;						///<  迭代起点	    | iteration start points
		double step_size_;								///<  迭代步长	    | iteration step size
		double gradient_step_size_;                     ///<  梯度步长      | gradient step size
		double converge_threshold_;						///<  收敛阈值      | converge threshold
		unsigned int stay_converge_times_;              ///<  收敛驻留次数  | stay converge times
	

		//------------------------------------------输出 | output---------------------------------------------------
		unsigned int iteration_count_;					///< 迭代次数   | real iteration count in runtime
		bool status_;									///< 迭代状态	| iteration status
		std::vector<double>  result_;
		std::vector<double>  loss_record_;				///< 函数损失值：跟踪迭代过程| loss values: tracking the iteration
	};


}//namespace  mvp

#endif //MVP_MULTIMIN_H
