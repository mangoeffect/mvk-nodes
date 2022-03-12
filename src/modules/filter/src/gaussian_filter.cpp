/**
 * @file gaussian_filter.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "filter/gaussian_filter.hpp"
#include <cmath>
#include <iostream>

namespace mvk
{
     int GaussianFilter(const Image& src, 
                       Image& dst, const size_t kernel_size, 
                       const double sigma_x,
                       const double sigma_y,
                       const BORDER_TYPE& border_type)
    {
        int ksize = kernel_size;
        if(ksize % 2 == 0)
        {
            ksize += 1;
        }
        int half_kernel = ksize / 2;
        int border_size = half_kernel;
        int window_size = 2 * half_kernel + 1;

        if(kernel_size <= 1)
        {
            dst = src.Copy();
            return 0;
        }

        //1. 边界填充
        auto src_padding = src.CopyWithBorder(border_size, border_type);

        //2. 计算高斯核
        double sigma_xx =  sigma_x;
        double sigma_yy =  sigma_y;
        if(std::fabs(sigma_x) < 1e-15)
        {
            sigma_xx = (ksize - 1) / 2.0 * 0.3 + 0.8;
        }
        if(std::fabs(sigma_y) < 1e-15)
        {
            sigma_yy = (ksize - 1) / 2.0 * 0.3 + 0.8;
        }
        std::vector<double> x_kernel(ksize, 0.0);
        std::vector<double> y_kernel(ksize, 0.0);

        double sum_x = 0;
        double sum_y = 0;
        int origin = ksize / 2;
        for (int i = 0; i < ksize; i++)
        {
            // 高斯函数前的常数可以不用计算，会在归一化的过程中给消去
            double gx = std::exp(-(i - origin) * (i - origin) / (2 * sigma_xx * sigma_xx));
            double gy = std::exp(-(i - origin) * (i - origin) / (2 * sigma_yy * sigma_yy));
            sum_x += gx;
            sum_y += gy;
            x_kernel[i] = gx;
            y_kernel[i] = gy;
        }
        //归一化
        for(int i = 0; i < kernel_size; i++)
        {
            x_kernel[i] /= sum_x;
            y_kernel[i] /= sum_y;
        }

        //3. x行方向高斯滤波
        dst = src.Copy();
        auto tmp = src_padding.Copy();
        int channels = src.GetChannel();
        if(channels == 1)
        {
            for(int i = 0; i < dst.GetHeight(); i++)//row
            {
                for(int j = border_size; j < dst.GetWidth(); j++)//col
                {
                    double sum = 0;
                    for(int k = -border_size; k < border_size; k++)
                    {
                        sum += x_kernel[border_size + k] * src_padding.GetPixel(i, j + k)[0];
                    }
                    tmp.GetPixel(i, j)[0] = static_cast<uint8_t>(sum);
                }
            }
            //4. y列方向高斯滤波
            for(int i = 0; i < dst.GetHeight(); i++)//row
            {
                for(int j = 0; j < dst.GetWidth(); j++)//col
                {
                    double sum = 0;
                    for(int k = -border_size; k < border_size; k++)
                    {
                        sum += y_kernel[border_size + k] * tmp.GetPixel(i + border_size + k, j + border_size)[0];
                    }
                    dst.GetPixel(i, j)[0] = static_cast<uint8_t>(sum);
                }
            }
        }
        else
        {
            for(int i = 0; i < dst.GetHeight(); i++)//row
            {
                for(int j = border_size; j < dst.GetWidth(); j++)//col
                {
                    double sum_r = 0;
                    double sum_g = 0;
                    double sum_b = 0;
                    for(int k = -border_size; k < border_size; k++)
                    {
                        sum_r += x_kernel[border_size + k] * src_padding.GetPixel(i, j + k)[0];
                        sum_g += x_kernel[border_size + k] * src_padding.GetPixel(i, j + k)[1];
                        sum_b += x_kernel[border_size + k] * src_padding.GetPixel(i, j + k)[2];
                    }
                    tmp.GetPixel(i, j)[0] = static_cast<uint8_t>(sum_r);
                    tmp.GetPixel(i, j)[1] = static_cast<uint8_t>(sum_g);
                    tmp.GetPixel(i, j)[2] = static_cast<uint8_t>(sum_b);
                }
            }
            //4. y列方向高斯滤波
            for(int i = 0; i < dst.GetHeight(); i++)//row
            {
                for(int j = 0; j < dst.GetWidth(); j++)//col
                {
                    double sum_r = 0;
                    double sum_g = 0;
                    double sum_b = 0;
                    for(int k = -border_size; k < border_size; k++)
                    {
                        sum_r += y_kernel[border_size + k] * tmp.GetPixel(i + border_size + k, j + border_size)[0];
                        sum_g += y_kernel[border_size + k] * tmp.GetPixel(i + border_size + k, j + border_size)[1];
                        sum_b += y_kernel[border_size + k] * tmp.GetPixel(i + border_size + k, j + border_size)[2];
                    }
                    dst.GetPixel(i, j)[0] = static_cast<uint8_t>(sum_r);
                    dst.GetPixel(i, j)[1] = static_cast<uint8_t>(sum_g);
                    dst.GetPixel(i, j)[2] = static_cast<uint8_t>(sum_b);
                }
            }
        }
        return 0;
    }
}//namespace mvk
