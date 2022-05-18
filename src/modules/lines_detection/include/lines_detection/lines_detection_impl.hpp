/**
 * @file lines_detection_impl.h
 * @author mango (2321544362@qq.com)
 * @brief 直线检测类实现类声明
 * @version 0.1
 * @date 2021-08-24
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_LINES_DETECTION_IMPL_HPP_
#define MVK_LINES_DETECTION_IMPL_HPP_

#include "lines_detection/lines_defines.h"
#include "image/image.h"
#include "common/rotate_rectangle.h"
#include "common/line.h"

#include <vector>

namespace mvk
{
    class MVK_LINES_EXPORT LinesDetectionImpl
    {
    private:
        Line line_;                                                     ///< 拟合直线结果
        std::vector<Point> inliers_;                                    ///< 参与直线拟合的内点
        std::vector<Point> outliers_;                                   ///< 不参与直线拟合的离群点
    public:
        LinesDetectionImpl(/* args */);
        ~LinesDetectionImpl();

        
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

#endif //MVK_LINES_DETECTION_IMPL_H_
