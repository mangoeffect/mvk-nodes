//
// Created by mango on 4/10/2020.
//

#include "linefit.h"

#include <cassert>


cv::Ptr<mv::LineFit> mv::LineFit::CreateInstance(const std::vector<cv::Point2d> &points, const FitAlgorithms &fitAlgorithms)
{
    return  cv::makePtr<mv::LineFit>(points, fitAlgorithms);
}//CreateInstance

void mv::LineFit::Run()
{
    switch (_fitAlgorithms)
    {
        case FitAlgorithms ::REGRESSION:
            break;
        case FitAlgorithms ::HUBER:
            break;
        case FitAlgorithms ::TUKEY:
            break;
        case FitAlgorithms ::DROP:
            break;
        case FitAlgorithms ::GAUSS:
            break;
        default:
            assert(false);
    }
}//Run

void mv::LineFit::FitLineByRegression()
{

}//FitLineByRegression

void mv::LineFit::FitLineByHuber()
{

}//FitLineByHuber

void mv::LineFit::FitLineByTukey()
{

}//FitLineByTukey

void mv::LineFit::FitLineByDrop()
{

}//FitLineByDrop


void mv::LineFit::FitLineByGauss()
{

}//FitLineByGauss