/**
 * @file caliper_impl.hpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MVK_CALIPER_IMPL_HPP_
#define MVK_CALIPER_IMPL_HPP_

#include "caliper/caliper_defines.hpp"

namespace mvk
{
    /**
     * @brief 卡尺工具实现类
     * 
     */
    class CaliperImpl
    {
    private:
        //--------------data------------------------
        Image input_image_;                               ///< 输入图像
        RotateRectf roi_;
        CaliperResult result_;

        //------------- config ---------------------
        CaliperParameters config_;                        ///< 配置参数
    public:
        CaliperImpl(const CALIPER_MODE& mode);

        int ComputeProjectCurve(const Image& image, const RotateRectf& roi, std::vector<float>& project_curve);

        int CurveConv(const std::vector<float>& project_curve, std::vector<float>& project_curve_conv, const size_t filter_kernel_size);

        int FindPeaks(const std::vector<float>& derivative1, const std::vector<float>& derivative2, std::vector<int>& peaks);

        int FilterByPolarity(const std::vector<float>& derivative1, const std::vector<int>& peaks, std::vector<int>& filter_peaks, const Polarity& polarity);

        int GradePeaks(const GRADE_MODE& grade_mode, const std::vector<int>& peaks, std::vector<Point2f>& grade_peaks);

        int ReMaptoImage(const RotateRectf& roi, const std::vector<int>& project_peaks, std::vector<Point2f>& image_peaks);

        void SetInputImage(const Image& image);

        void SetROI(const RotateRectf& roi);

        int Measure();

        CaliperResult GetResult() const;
    };
}//namespace mvk

#endif //MVK_CALIPER_IMPL_HPP_
