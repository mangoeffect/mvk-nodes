/**
 * @file line_fit.cpp
 * @author mango (2321544362@qq.com)
 * @brief 二维平面直线拟合算法实现
 * @version 0.1
 * @date 2021-07-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "line_fit.h"

#include "racsac_implement.hpp"
#include "regression_implement.hpp"
#include "gauss_implement.hpp"
#include "huber_implement.hpp"
#include "tukey_implement.hpp"
#include "orthogonal_implement.hpp"
#include "drop_implement.hpp"

namespace mvk
{
    namespace line_fit
    {
        LineFit::LineFit(/* args */)
        {

        }
        
        LineFit::~LineFit()
        {
            
        }


        int LineFit::SetInputPoints(const std::vector<cv::Point2f>& points)
        {
            points_ = points;
            return 0;
        }

        int LineFit::DoFitting()
        {
            switch (common_paramter_linefit_method_)
            {
            case LineFitMethod::REGRESSION:
            {
                return RegressionLineFit(points_, result_, common_parameter_dist_type_);
            }
            case LineFitMethod::TUKEY:
            {
                break;
            }
            case LineFitMethod::DROP:
            {
                break;
            }
            case LineFitMethod::GAUSS:
            {
                break;
            }
            case LineFitMethod::HUBER:
            {
                break;
            }
            case LineFitMethod::ORTHOGONAL:
            {
                break;
            }
            case LineFitMethod::RACSAC:
            {
                break;
            }
            default:
                assert(false && "Fitting method was not found!");
            }

            return 0;
        }
        

        int LineFit::SetCommonParameterDistType(const DistType& type)
        {
            common_parameter_dist_type_ = type;
            return 0;
        }


        DistType LineFit::GetCommonParameterDistType() const
        {
            return common_parameter_dist_type_;
        }

        LineFitResult LineFit::GetReasult() const
        {
            return result_;
        }
    }// namespace line_fit
}//namespace mvk


