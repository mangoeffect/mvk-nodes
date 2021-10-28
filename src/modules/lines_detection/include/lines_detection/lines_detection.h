/**
 * @file lines_detection.h
 * @author mango (2321544362@qq.com)
 * @brief 直线检测类声明
 * @version 0.1
 * @date 2021-08-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_LINES_DETECTION_H_
#define MVK_LINES_DETECTION_H_

#include "lines_detection/lines_defines.h"
#include "image/image.h"
#include "common/rotate_rectangle.h"
#include "common/line.h"

#include <vector>

namespace mvk
{   
    class MVK_LINES_EXPORT LinesDetectionImpl;                               ///< 直线检测类实现类前置声明

    /**
     * @brief 直线检测类声明
     * 
     */
    class MVK_LINES_EXPORT LinesDetection
    {
    private:
        std::shared_ptr<LinesDetectionImpl> lines_impl_;                    ///< 实现类对象指针
    public:
        LinesDetection();
        ~LinesDetection();

        int SetImage(const Image& image);

        int SetAllDetectionParameters(const std::string& json_format_paramters);

        int SetDetectionRoi(const RotateRectangle& rect_roi);

        int SetCaliperNumber(const size_t& number);

        int SetEdgePolarity(const Polarity& polarity);

        int SetLineFitMethod(const LineFitMethod& method);

        int Detect();

        Line GetLine() const;

        int GetInlierPoints(std::vector<Point>& inliers) const;

        int GetOutlierPoints(std::vector<Point>& outliers) const;
    };    
} // namespace mvk


#endif //MVK_LINES_DETECTION_H_
