/**
 * @file caliper_impl.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "caliper/caliper_impl.hpp"
#include <iostream>

namespace mvk
{
    CaliperImpl::CaliperImpl(const CALIPER_MODE& mode)
    {

    }

    void CaliperImpl::SetInputImage(const Image& image)
    {
        input_image_ = image;
    }

    void CaliperImpl::SetROI(const RotateRectf& roi)
    {
        roi_ = roi;
    }

    int CaliperImpl::Measure()
    {
        //----------测量流程------------
        if(nullptr == input_image_.GetData()) {return -1;}
        int ret = 0;
        //1. 基于ROI和扫描-投影方向计算投影结果，投影结果为灰度值分布曲线
        std::vector<float> project_curve;
        ret = ComputeProjectCurve(input_image_, roi_, project_curve);
        if(0 != ret) {return ret;}
        result_.project_curve = project_curve;
        //2. 基于差分思想，卷积滤波投影曲线(求导)

        //滤波
        std::vector<float> derivative;
        ret = CurveConv(project_curve, derivative, config_.filter_kernel_size);
        if(0 != ret) {return ret;}
    
        //二阶导数
        std::vector<float> derivative1;
        ret = CurveConv(derivative, derivative1, config_.filter_kernel_size);
        if(0 != ret) {return ret;}
        std::vector<float> derivative2;
        ret = CurveConv(derivative1, derivative2, config_.filter_kernel_size);
        if(0 != ret) {return ret;}
        

        //3. 计算滤波后的灰度值分布曲线峰值点
        std::vector<int> project_peaks;
        ret = FindPeaks(derivative1, derivative2, project_peaks);
        if(0 != ret) {return ret;}

        //4. 基于扫描方向极性：白到黑或者黑到白过滤峰值点
        std::vector<int> filter_peaks;
        ret = FilterByPolarity(derivative1, project_peaks, filter_peaks, config_.polarity);
        if(0 != ret) {return ret;}

        //5. 峰值点逆映射回ROI中对应的图像坐标点
        std::vector<Point2f> remap_peaks;
        ret = ReMaptoImage(roi_, filter_peaks, remap_peaks);
        if(0 != ret) {return ret;}

        for(auto& p: remap_peaks)
        {
            Peak peak;
            peak.p = p;
            result_.peaks.push_back(peak);
        }

        //6. 峰值点评分

        return 0;
    }

    CaliperResult CaliperImpl::GetResult() const
    {
        return result_;
    }

    int CaliperImpl::ComputeProjectCurve(const Image& image, const RotateRectf& roi, std::vector<float>& project_curve)
    {
        //参数判断
        int ret = 0;
        if(nullptr == image.GetData()) {return -1;}
        project_curve.clear();

        //基于扫描-投影方向将灰度值投影至一维
        auto scan_direct = roi.GetDirection();              //扫描方向
        auto project_direct = roi.points[3] - roi.points[0];//投影方向
        project_direct.Normalize();

        int scan_range = static_cast<int>(roi.GetWidth());
        int project_range = static_cast<int>(roi.GetHeight());

        //roi在二维坐标系下的数据
        std::vector<std::vector<double>> roi_table(project_range, std::vector<double>(scan_range, 0.0));
        std::vector<double> project(scan_range, 0.0);
        

        //计算投影过程
        for(int i = 0; i < project_range; ++i)
        {
            Point2f row_start(roi.points[0].x + i * project_direct.x, roi.points[0].y + i * project_direct.y);
            for(int j = 0; j < scan_range; ++j)
            {
                int px = row_start.x + j * scan_direct.x;
                int py = row_start.y + j * scan_direct.y;
                roi_table[i][j] = *image.GetPixel(py, px);
                project[j] +=  roi_table[i][j];
            }
        }

        //取投影后像数值均值
        project_curve.resize(scan_range);
        for(int i = 0; i < scan_range; ++i)
        {
            project_curve[i] = project[i] / project_range;
        }

        return 0;
    }

    int CaliperImpl::CurveConv(const std::vector<float>& project_curve, std::vector<float>& project_curve_conv, const size_t filter_kernel_size)
    {
        //参数判断
        if(project_curve.size() < filter_kernel_size * 2 || filter_kernel_size < 3)
        {
            project_curve_conv = project_curve;
            return -1;
        }

        //构造滤波核: [-1,-1...0...1,1]
        std::vector<float> kernel(filter_kernel_size, 1.0f);
        int half = filter_kernel_size / 2;
        for(int i = 0; i < half; i++)
        {
            kernel[i] = -1.0f;
        }
        kernel[half] = 0.0f;

        //一维卷积滤波
        int len = project_curve.size();
        int conv_len = len + half + half;
        std::vector<float> front_padding(half, project_curve.front());
        std::vector<float> back_padding(half, project_curve.back());
        std::vector<float> src_padding = front_padding;
        src_padding.insert(src_padding.end(), project_curve.begin(), project_curve.end());
        src_padding.insert(src_padding.end(), back_padding.begin(), back_padding.end());
        
        project_curve_conv = project_curve;
        for(int m = half; m < conv_len - half; ++m)
        {
            float sum = 0.0f;
            for(int n = -half; n <= half; ++n)
            {
                sum += src_padding[m + n] * kernel[n + half];
            }
            project_curve_conv[m - half] = sum / filter_kernel_size;
        }

        return 0;
    }

    int CaliperImpl::FindPeaks(const std::vector<float>& derivative1, const std::vector<float>& derivative2, std::vector<int>& peaks)
    {
        //参数检查
        if(derivative1.size() < 3) {return -1;}
        assert(derivative1.size() == derivative2.size());

        //思路，一阶导数左右两侧异号，二阶导数接近0
        int size = derivative1.size();
        for(int i = 1; i < size - 1; ++i)
        {
            if(derivative1[i - 1] * derivative1[i + 1] < 0)
            {
                peaks.push_back(i);
            }
        }
        return 0;
    }

    int CaliperImpl::FilterByPolarity(const std::vector<float>& derivative1, const std::vector<int>& peaks, std::vector<int>& filter_peaks, const Polarity& polarity)
    {
        //参数检查
        if(derivative1.size() < 3) {return -1;}

        switch (polarity)
        {
            case Polarity::ANY:
            {
                filter_peaks = peaks;
                break;
            }
            case Polarity::WHITE_TO_BLACK:
            {   
                //白到黑
                for(auto& p: peaks)
                {
                    if(derivative1[p - 1] > derivative1[p + 1])
                    {
                        filter_peaks.push_back(p);
                    }
                }
                break;
            }
            case Polarity::BLACK_TO_WHITE:
            {
                //黑到白
                for(auto& p: peaks)
                {
                    if(derivative1[p - 1] < derivative1[p + 1])
                    {
                        filter_peaks.push_back(p);
                    }
                }
                break;
            }
        }
        return 0;
    }

    int CaliperImpl::GradePeaks(const GRADE_MODE& grade_mode, const std::vector<int>& peaks, std::vector<Point2f>& grade_peaks)
    {
        return 0;
    }

    int CaliperImpl::ReMaptoImage(const RotateRectf& roi, const std::vector<int>& project_peaks, std::vector<Point2f>& image_peaks)
    {
        if(project_peaks.empty()) {return -1;}

        auto scan_direct = roi.GetDirection();              //扫描方向
        auto project_direct = roi.points[3] - roi.points[0];//投影方向
        project_direct.Normalize();
        int scan_range = static_cast<int>(roi.GetWidth());
        int project_range = static_cast<int>(roi.GetHeight());

        //映射回去扫描方向的中线位置
        Point2f mid_start((roi.points[0].x + roi.points[3].x) / 2.0, (roi.points[0].y + roi.points[3].y) / 2.0);
        image_peaks.clear();
        for(auto& p: project_peaks)
        {
            float px = mid_start.x + p * scan_direct.x;
            float py = mid_start.y + p * scan_direct.y;
            image_peaks.emplace_back(px, py);
        }
        return 0;
    }
}//namespace mvk

