/**
 * @file box_filter.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "box_filter.hpp"
#include "integral_image.hpp"
#include <cmath>

namespace mvk
{
    int BoxFilter(Image& src, Image& dst, const size_t kernel_size, const BORDER_TYPE& border_type)
    {
        size_t half_kernel = kernel_size / 2;
        size_t border_size = half_kernel;
        size_t window_size = 2 * half_kernel + 1;
        size_t window_area = window_size * window_size;
        //1. 边界扩充
        auto src_padding = src.CopyWithBorder(border_size, border_type);

        //2. 计算积分图
        Matrix<uint64_t> integral;
        if(auto ret = ComputeIntegral(src_padding, integral); ret != 0)
        {
            return ret;
        }

        //3. 计算滤波值
        dst = src.Clone();

        if(half_kernel > 0)
        {
            if(auto channels = src.Channels(); channels == 1)
            {
                for(size_t i = 0; i < dst.GetSize().height; i++) //row
                {
                    for(size_t j = 0 ; j < dst.GetSize().width; j++)//col
                    {
                        //--------------
                        // |  A  |  B |
                        //   ----p ----
                        // |  C  |  D |
                        // Sum_abcd = Sat_d - Sat_b - Sat_c + Sat_a
                        auto sum = integral(border_size + i + half_kernel, border_size + j + half_kernel) 
                                 - integral(border_size + i - half_kernel, border_size + j + half_kernel) 
                                 - integral(border_size + i + half_kernel, border_size + j - half_kernel) 
                                 + integral(border_size + i - half_kernel, border_size + j - half_kernel);
                        dst.Ptr<std::uint8_t>(j, i)[0] = static_cast<uint8_t>(std::round(1.0 * sum / window_area));
                    }
                }
            }else
            {
                for(size_t i = 0; i < dst.GetSize().height; i++) //row
                {
                    for(size_t j = 0; j < dst.GetSize().width; j++)//col
                    {
                        for(size_t c = 0; c < channels; c++)
                        {
                            //--------------
                            // |  A  |  B |
                            //   ----p ----
                            // |  C  |  D |
                            // Sum_abcd = Sat_d - Sat_b - Sat_c + Sat_a
                            auto sum = integral(border_size + i + half_kernel, (border_size + j + half_kernel) * channels + c) 
                                     - integral(border_size + i - half_kernel, (border_size + j + half_kernel) * channels + c) 
                                     - integral(border_size + i + half_kernel, (border_size + j - half_kernel) * channels + c) 
                                     + integral(border_size + i - half_kernel, (border_size + j - half_kernel) * channels + c);
                            dst.Ptr<std::uint8_t>(j, i)[c] = static_cast<uint8_t>(std::round(1.0 * sum / window_area));
                        }
                    }
                }
            }
        }
   
        return 0;
    }
}//namespace mvk

