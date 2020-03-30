//
// Created by mango on 3/28/2020.
//

#include "blobdetect.h"


void mv::BlobDetect::Run()
{
    if(input_image.empty())
    {
        throw "Input image is empty.";
        return;
    }
    this->detect(input_image, keypoints);
}//Run

void mv::BlobDetect::SetParams(std::string name, float value)
{
    if("minThreshold" == name)
    {
        params.minThreshold = value;
    } else if("maxThreshold" == name)
    {
        params.maxThreshold = value;
    } else if("thresholdStep" == name)
    {
        params.thresholdStep = value;
    } else if("minRepeatability" == name)
    {
        params.minRepeatability = static_cast<size_t>(value);
    } else if("minDistBetweenBlobs" == name)
    {
        params.minDistBetweenBlobs = value;
    } else if("filterByColor" == name)
    {
        params.filterByColor == static_cast<bool>(value);
    } else if("filterByArea" == name)
    {
        params.filterByArea == static_cast<bool>(value);
    } else if("minArea" == name)
    {
        params.minArea = value;
    } else if("maxArea" == name)
    {
        params.maxArea = value;
    } else if("filterByCircularity" == name)
    {
        params.filterByCircularity = value;
    } else if("minCircularity" == name)
    {
        params.minCircularity = value;
    } else if("maxCircularity" == name)
    {
        params.maxCircularity = value;
    } else if("filterByInertia" == name)
    {
        params.filterByInertia = static_cast<bool>(value);
    } else if("minInertiaRatio" == name)
    {
        params.minInertiaRatio = value;
    } else if("maxInertiaRatio" == name)
    {
        params.maxInertiaRatio = value;
    } else if("filterByConvexity" == name)
    {
        params.filterByConvexity = static_cast<bool>(value);
    } else if("minConvexity" == name)
    {
        params.minConvexity = value;
    } else if("maxConvexity" == name)
    {
        params.maxConvexity = value;
    }
}//SetParams