/**
 * @file median_filter.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "filter/median_filter.hpp"
#include <vector>
#include <cassert>
#include <iostream>

namespace mvk
{
    int MedianFilter(const Image& src,
                     Image& dst,
                     const size_t kernel_size,
                     const BORDER_TYPE& border_type)
    {
        //参数检查
        if(src.GetData() == nullptr){ return -1; }

        //边界扩充
        int half_size = kernel_size / 2;
        auto src_padding = src.CopyWithBorder(half_size, border_type);

        //滑动窗口计算中值滤波
        dst = src.Copy();
        int rows = src_padding.GetHeight();
        int cols = src_padding.GetWidth();
        int channels = src_padding.GetChannel();
        int mid_flag = kernel_size * kernel_size / 2;

        for(int i = half_size; i < rows - half_size; i++)
        {
            std::vector<std::vector<int>> hist(channels, std::vector<int>(256, 0));
            for(int j = half_size; j < cols - half_size; j++)
            {
                //更新滑动窗口内直方图
                for(int c = 0; c < channels; c++)
                {
                    if(j == half_size)
                    {
                        //初始化直方图
                        for(int m = i - half_size; m <= i + half_size; m++)//rows
                        {
                            for(int n = j - half_size; n <= j + half_size; n++)//cols
                            {
                                hist[c][src_padding.GetPixel(m, n)[0]]++;
                            }
                        }
                    }else
                    {
                        //更新,非第一列，直方图已经初始化，可以直接更新
                        for(int m = i - half_size; m < i + half_size; m++)//rows
                        {
                            //减去前一列
                            hist[c][src_padding.GetPixel(m, j - half_size - 1)[0]]--;
                            //加上当前列
                            hist[c][src_padding.GetPixel(m, j + half_size)[0]]++;
                        }
                    }
                    
                    //基于直方图获取中值
                    int sum = 0;
                    for(int k = 0; k < 256; k++)
                    {
                        sum += hist[c][k];
                        if(sum >= mid_flag)
                        {
                            dst.GetPixel(i - half_size, j - half_size)[0] = static_cast<uint8_t>(k);
                            break;
                        }
                    }
                }
            }
        }
        return 0;
    }
}//namespace mvk
