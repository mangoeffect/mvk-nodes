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

#include "xsimd/xsimd.hpp"
#include "omp.h"

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

        #pragma omp parallel for
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

    template<typename T>
    inline void SwapSort(T& a, T& b)
    {
        auto min = xsimd::min(a, b);
        auto max = xsimd::max(a, b);
        a                   = min;
        b                   = max;
    }

    
    int MedianFilter3x3(Image& src, Image& dst)
    {
        //参数检查
        if(src.GetData() == nullptr){ return -1; }
        int rows = src.GetHeight();
        int cols = src.GetWidth();

        //边界只有1无需扩充边界
        dst = src.Copy();

        //遍历进行中值滤波
        constexpr std::size_t simd_size = xsimd::simd_type<uint8_t>::size;
        int vec_size = cols - (cols - 2) % simd_size - 2;

        #pragma omp parallel for
        for(int i = 1; i < rows - 1; i++)
        {
            for(int j = 1; j < vec_size; j += simd_size)
            {
                auto P0 = xsimd::load_unaligned(src.GetPixel(i , j));
                auto P1 = xsimd::load_unaligned(src.GetPixel(i - 1, j));
                auto P2 = xsimd::load_unaligned(src.GetPixel(i - 1, j +1));

                auto P3 = xsimd::load_unaligned(src.GetPixel(i, j -1));
                auto P4 = xsimd::load_unaligned(src.GetPixel(i, j));
                auto P5 = xsimd::load_unaligned(src.GetPixel(i, j +1));

                auto P6 = xsimd::load_unaligned(src.GetPixel(i + 1, j -1));
                auto P7 = xsimd::load_unaligned(src.GetPixel(i + 1, j));
                auto P8 = xsimd::load_unaligned(src.GetPixel(i + 1, j +1));

                //比较交换获取中值
                SwapSort(P1, P2);		SwapSort(P4, P5);		SwapSort(P7, P8);
                SwapSort(P0, P1);		SwapSort(P3, P4);		SwapSort(P6, P7);
                SwapSort(P1, P2);		SwapSort(P4, P5);		SwapSort(P7, P8);
                SwapSort(P0, P3);		SwapSort(P5, P8);		SwapSort(P4, P7);
                SwapSort(P3, P6);		SwapSort(P1, P4);		SwapSort(P2, P5);
                SwapSort(P4, P7);		SwapSort(P4, P2);		SwapSort(P6, P4);
                SwapSort(P4, P2);

                //保存结果
                P4.store_unaligned(dst.GetPixel(i, j));
            }

            for(int j = vec_size; j < cols - 1; j++)
            {
                uint8_t P0 = src.GetPixel(i - 1, j - 1)[0];
                uint8_t P1 = src.GetPixel(i - 1, j)[0];
                uint8_t P2 = src.GetPixel(i - 1, j + 1)[0];

                uint8_t P3 = src.GetPixel(i, j - 1)[0];
                uint8_t P4 = src.GetPixel(i, j)[0];
                uint8_t P5 = src.GetPixel(i, j + 1)[0];

                uint8_t P6 = src.GetPixel(i + 1, j - 1)[0];
                uint8_t P7 = src.GetPixel(i + 1, j)[0];
                uint8_t P8 = src.GetPixel(i + 1, j + 1)[0];

                if (P1 > P2) std::swap(P1, P2);
                if (P4 > P5) std::swap(P4, P5);
                if (P7 > P8) std::swap(P7, P8);
                if (P0 > P1) std::swap(P0, P1);
                if (P3 > P4) std::swap(P3, P4);
                if (P6 > P7) std::swap(P6, P7);
                if (P1 > P2) std::swap(P1, P2);
                if (P4 > P5) std::swap(P4, P5);
                if (P7 > P8) std::swap(P7, P8);
                if (P0 > P3) std::swap(P0, P3);
                if (P5 > P8) std::swap(P5, P8);
                if (P4 > P7) std::swap(P4, P7);
                if (P3 > P6) std::swap(P3, P6);
                if (P1 > P4) std::swap(P1, P4);
                if (P2 > P5) std::swap(P2, P5);
                if (P4 > P7) std::swap(P4, P7);
                if (P4 > P2) std::swap(P4, P2);
                if (P6 > P4) std::swap(P6, P4);
                if (P4 > P2) std::swap(P4, P2);
                
                dst.GetPixel(i , j)[0] = P4;
            }
        }
        return 0;
    }

    int MedianFilter3x34(const Image& src, Image& dst)
    {
        //参数检查
        if(src.GetData() == nullptr){ return -1; }
        int rows = src.GetHeight();
        int cols = src.GetWidth();

        //边界只有1无需扩充边界
        dst = src.Copy();

        //遍历进行中值滤波
        //int simd_size = 32; //avx2-uchar
        //int vec_size = cols - (cols - 1) % simd_size;

        for(int i = 1; i < rows - 1; i++)
        {
            for(int j = 1; j < cols - 1; j++)
            {
                uint8_t P0 = src.GetPixel(i - 1, j - 1)[0];
                uint8_t P1 = src.GetPixel(i - 1, j)[0];
                uint8_t P2 = src.GetPixel(i - 1, j + 1)[0];

                uint8_t P3 = src.GetPixel(i, j - 1)[0];
                uint8_t P4 = src.GetPixel(i, j)[0];
                uint8_t P5 = src.GetPixel(i, j + 1)[0];

                uint8_t P6 = src.GetPixel(i + 1, j - 1)[0];
                uint8_t P7 = src.GetPixel(i + 1, j)[0];
                uint8_t P8 = src.GetPixel(i + 1, j + 1)[0];

                
                if (P1 > P2) std::swap(P1, P2);
                if (P4 > P5) std::swap(P4, P5);
                if (P7 > P8) std::swap(P7, P8);
                if (P0 > P1) std::swap(P0, P1);
                if (P3 > P4) std::swap(P3, P4);
                if (P6 > P7) std::swap(P6, P7);
                if (P1 > P2) std::swap(P1, P2);
                if (P4 > P5) std::swap(P4, P5);
                if (P7 > P8) std::swap(P7, P8);
                if (P0 > P3) std::swap(P0, P3);
                if (P5 > P8) std::swap(P5, P8);
                if (P4 > P7) std::swap(P4, P7);
                if (P3 > P6) std::swap(P3, P6);
                if (P1 > P4) std::swap(P1, P4);
                if (P2 > P5) std::swap(P2, P5);
                if (P4 > P7) std::swap(P4, P7);
                if (P4 > P2) std::swap(P4, P2);
                if (P6 > P4) std::swap(P6, P4);
                if (P4 > P2) std::swap(P4, P2);

                dst.GetPixel(i , j)[0] = P4;
            }
        }
        return 0;
    }
}//namespace mvk
