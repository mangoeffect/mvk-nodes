/**
 * @file lines_detection_impl.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "lines_detection/lines_detection_impl.h"

namespace mvk
{
    LinesDetectionImpl::LinesDetectionImpl()
    : line_(Line(Point(), Vector()))
    {

    }
    
    LinesDetectionImpl::~LinesDetectionImpl()
    {
    }

    int LinesDetectionImpl::SetImage(const Image& image)
    {
        return 0;
    }

    int LinesDetectionImpl::SetAllDetectionParameters(const std::string& json_format_paramters)
    {
        return 0;
    }

    int LinesDetectionImpl::SetDetectionRoi(const RotateRectangle& rect_roi)
    {
        return 0;
    }

    int LinesDetectionImpl::SetCaliperNumber(const size_t& number)
    {
        return 0;
    }

    int LinesDetectionImpl::SetEdgePolarity(const Polarity& polarity)
    {
        return 0;
    }

    int LinesDetectionImpl::SetLineFitMethod(const LineFitMethod& method)
    {
        return 0;
    }

    int LinesDetectionImpl::Detect()
    {
        return 0;
    }

    Line LinesDetectionImpl::GetLine() const
    {
        return  line_;
    }

    int LinesDetectionImpl::GetInlierPoints(std::vector<Point>& inliers) const
    {
        inliers = inliers_;
        return 0;
    }

    int LinesDetectionImpl::GetOutlierPoints(std::vector<Point>& outliers) const
    {
        outliers = outliers_;
        return 0;
    }
} // namespace mvk


