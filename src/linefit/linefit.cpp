
/**
* @file linefit.cpp
* @brief 直线拟合源文件
* @details 基于最小二乘、huber、tukey等方法拟合直线
* @author 芒果
* @date 2020-4-10
* @version 1.0.0
*/


#include "linefit.h"

#include <cassert>

namespace mvp
{
	std::shared_ptr<LineFit> LineFit::CreateLineFitTool()
	{
		return std::make_shared<LineFit>();
	}
	      
	int LineFit::SetParam(const std::string& json_str)
	{
        return 0;
	}


	int LineFit::SetInputPointArray(const std::vector<cv::Point_>& point_array)
	{
        return 0;
	}

	
	int LineFit::Run()
	{
		
		RunRansac();

		return 0;
	}

	int LineFit::SampleMnimumData()
	{
		return 0;
	}

	int LineFit::FitModel()
	{
		return 0;
	}

	int LineFit::ComputeCurrentInliers()
	{
		return 0;
	}

	int LineFit::RecordBestModel()
	{
		return 0;
	}

	int LineFit::IsGoodEnough()
	{
		return 0;
	}

	int LineFit::SetOutliersDistanceThreshold(const double& threshold)
    {
		return 0;
	}


	int LineFit::SetForceRemoveRatio(const double& ratio)
	{
		return 0;
	}


	int LineFit::SetForceRemoveNum(const int& num)
	{
		return 0;
	}

    
	int LineFit::SetMaxIterNum(const int& num)
	{
        return 0;
	}
}//namespace mvp


