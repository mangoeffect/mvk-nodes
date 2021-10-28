/**
 * @file lines_detection.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "lines_detection/lines_detection.h"
#include "lines_detection/lines_detection_impl.h"

namespace mvk
{
    LinesDetection::LinesDetection()
    : lines_impl_(new LinesDetectionImpl())
    {
    }
    
    LinesDetection::~LinesDetection()
    {
    }

    int LinesDetection::SetImage(const Image& image)
    {
        return lines_impl_->SetImage(image);
    }

    int LinesDetection::SetAllDetectionParameters(const std::string& json_format_paramters)
    {
        return lines_impl_->SetAllDetectionParameters(json_format_paramters);
    }

    int LinesDetection::SetDetectionRoi(const RotateRectangle& rect_roi)
    {
        return lines_impl_->SetDetectionRoi(rect_roi);
    }

    int LinesDetection::SetCaliperNumber(const size_t& number)
    {
        return lines_impl_->SetCaliperNumber(number);
    }

    int LinesDetection::SetEdgePolarity(const Polarity& polarity)
    {
        return lines_impl_->SetEdgePolarity(polarity);
    }

    int LinesDetection::SetLineFitMethod(const LineFitMethod& method)
    {
        return lines_impl_->SetLineFitMethod(method);
    }

    int LinesDetection::Detect()
    {
        return lines_impl_->Detect();
    }

    Line LinesDetection::GetLine() const
    {
        return lines_impl_->GetLine();
    }

    int LinesDetection::GetInlierPoints(std::vector<Point>& inliers) const
    {
        return lines_impl_->GetInlierPoints(inliers);
    }

    int LinesDetection::GetOutlierPoints(std::vector<Point>& outliers) const
    {
        return lines_impl_->GetOutlierPoints(outliers);
    }
} // namespace mvk
