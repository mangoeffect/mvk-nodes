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

#include "median_filter.hpp"
#include <vector>
#include <cassert>
#include "omp.h"
#include "opencv2/core/simd_intrinsics.hpp"


namespace mvk
{
    int MedianFilter(Image& src,
                     Image& dst,
                     const size_t kernel_size,
                     const BORDER_TYPE& border_type)
    {
        //参数检查
        if(src.IsEmpty()){ return -1; }

        //边界扩充
        int half_size = kernel_size / 2;
        auto src_padding = src.CopyWithBorder(half_size, border_type);

        //滑动窗口计算中值滤波
        dst = src.Clone();
        int rows = src_padding.GetSize().height;
        int cols = src_padding.GetSize().width;
        int channels = src_padding.Channels();
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
                                hist[c][src_padding.Ptr<std::uint8_t>(n, m)[0]]++;
                            }
                        }
                    }else
                    {
                        //更新,非第一列，直方图已经初始化，可以直接更新
                        for(int m = i - half_size; m < i + half_size; m++)//rows
                        {
                            //减去前一列
                            hist[c][src_padding.Ptr<std::uint8_t>(j - half_size - 1, m)[0]]--;
                            //加上当前列
                            hist[c][src_padding.Ptr<std::uint8_t>(j + half_size, m)[0]]++;
                        }
                    }
                    
                    //基于直方图获取中值
                    int sum = 0;
                    for(int k = 0; k < 256; k++)
                    {
                        sum += hist[c][k];
                        if(sum >= mid_flag)
                        {
                            dst.Ptr<std::uint8_t>(j - half_size, i - half_size)[0] = static_cast<uint8_t>(k);
                            break;
                        }
                    }
                }
            }
        }
        return 0;
    }

    inline void SwapSort(cv::v_uint8& a, cv::v_uint8& b)
    {
        auto min = cv::v_min(a, b);
        auto max = cv::v_max(a, b);
        a                   = min;
        b                   = max;
    }

    inline void Op(uint8_t& a, uint8_t& b)
    {
        uint8_t min = std::min(a, b);
        uint8_t max = std::max(a, b);
        a = min;
        b = max;
    }

    
    int MedianFilter3x3(Image& src, Image& dst)
    {
        //参数检查
        if(src.IsEmpty()){ return -1; }
        int channel = src.Channels();
        int rows = src.GetSize().height;
        int cols = src.GetSize().width * channel;

        //边界只有1无需扩充边界
        uint8_t* data = new uint8_t[rows * cols * channel]();
        if(1 == channel)
        {
            dst = Image(src.GetSize(), IMAGE_TYPE::IMAGE_8UC1, data);
        }else if(3 == channel)
        {
            dst = Image(src.GetSize(), IMAGE_TYPE::IMAGE_8UC3, data);
        }else
        {
            dst = src.Clone();
            return -1;
        }

        //遍历进行中值滤波
        int simd_size = cv::v_uint8::nlanes;
        int vec_size = cols - (cols - 2 * channel) % simd_size - 2 *channel;

        #pragma omp parallel for
        for(int i = 1; i < rows - 1; i++)
        {
            uint8_t* row0 = src.Ptr<std::uint8_t>(0,i - 1);
            uint8_t* row1 = src.Ptr<std::uint8_t>(0,i);
            uint8_t* row2 = src.Ptr<std::uint8_t>(0,i + 1);
            uint8_t* row_dst = dst.Ptr<std::uint8_t>(0,i);

            //simd指令集优化
            for(int j = channel; j < vec_size; j += simd_size)
            {
                auto P0 = cv::vx_load(row0 + j - channel);
                auto P1 = cv::vx_load(row0 + j);
                auto P2 = cv::vx_load(row0 + j + channel);

                auto P3 = cv::vx_load(row1 + j - channel);
                auto P4 = cv::vx_load(row1 + j);
                auto P5 = cv::vx_load(row1 + j + channel);

                auto P6 = cv::vx_load(row2 + j - channel);
                auto P7 = cv::vx_load(row2 + j);
                auto P8 = cv::vx_load(row2 + j + channel);

                //比较交换获取中值
                SwapSort(P1, P2);		SwapSort(P4, P5);		SwapSort(P7, P8);
                SwapSort(P0, P1);		SwapSort(P3, P4);		SwapSort(P6, P7);
                SwapSort(P1, P2);		SwapSort(P4, P5);		SwapSort(P7, P8);
                SwapSort(P0, P3);		SwapSort(P5, P8);		SwapSort(P4, P7);
                SwapSort(P3, P6);		SwapSort(P1, P4);		SwapSort(P2, P5);
                SwapSort(P4, P7);		SwapSort(P4, P2);		SwapSort(P6, P4);
                SwapSort(P4, P2);

                //保存结果
                //P4.store_unaligned(row_dst + j);
                cv::vx_store(row_dst + j, P4);
            }

            //处理不满足simd优化部分
            for(int j = vec_size; j < cols - channel; j++)
            {
                uint8_t P0 = *(row0 + j - channel);
                uint8_t P1 = *(row0 + j);
                uint8_t P2 = *(row0 + j + channel);

                uint8_t P3 = *(row1 + j - channel);
                uint8_t P4 = *(row1 + j);
                uint8_t P5 = *(row1 + j + channel);

                uint8_t P6 = *(row2 + j - channel);
                uint8_t P7 = *(row2 + j);
                uint8_t P8 = *(row2 + j + channel);

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

                *(row_dst + j) = P4;
            }
        }
        return 0;
    }

    int MedianFilter5x5(Image& src, Image& dst)
    {
         //参数检查
        if(src.IsEmpty()){ return -1; }
        int channel = src.Channels();
        int rows = src.GetSize().height;
        int cols = src.GetSize().width * channel;

        //边界只有1无需扩充边界
        dst = src.Clone();

        //遍历进行中值滤波
        constexpr std::size_t simd_size = cv::v_uint8::nlanes;
        int vec_size = cols - (cols - 4 * channel) % simd_size - 4 *channel;

        #pragma omp parallel for
        for(int i = 2; i < rows - 2; i++)
        {
            std::vector<uint8_t*> row_ptr(5, nullptr);
            row_ptr[0] = src.Ptr<std::uint8_t>(0,i - 2);
            row_ptr[1] = src.Ptr<std::uint8_t>(0,i - 1);
            row_ptr[2] = src.Ptr<std::uint8_t>(0,i);
            row_ptr[3] = src.Ptr<std::uint8_t>(0,i + 1);
            row_ptr[4] = src.Ptr<std::uint8_t>(0,i + 2);
            uint8_t* row_dst = dst.Ptr<std::uint8_t>(0,i);

            //simd指令集优化
            for(int j = 2 * channel; j < vec_size; j += simd_size)
            {
                auto p0 = cv::vx_load(row_ptr[0] + j - 2 * channel);
                auto p1 = cv::vx_load(row_ptr[0] + j - channel); 
                auto p2 = cv::vx_load(row_ptr[0] + j); 
                auto p3 = cv::vx_load(row_ptr[0] + j + channel);
                auto p4 = cv::vx_load(row_ptr[0] + j + 2 * channel); 
 
                auto p5 = cv::vx_load(row_ptr[1] + j - 2 * channel);
                auto p6 = cv::vx_load(row_ptr[1] + j - channel); 
                auto p7 = cv::vx_load(row_ptr[1] + j); 
                auto p8 = cv::vx_load(row_ptr[1] + j + channel);
                auto p9 = cv::vx_load(row_ptr[1] + j + 2 * channel); 

                auto p10 = cv::vx_load(row_ptr[2] + j - 2 * channel);
                auto p11 = cv::vx_load(row_ptr[2] + j - channel); 
                auto p12 = cv::vx_load(row_ptr[2] + j); 
                auto p13 = cv::vx_load(row_ptr[2] + j + channel);
                auto p14 = cv::vx_load(row_ptr[2] + j + 2 * channel); 

                auto p15 = cv::vx_load(row_ptr[3] + j - 2 * channel);
                auto p16 = cv::vx_load(row_ptr[3] + j - channel); 
                auto p17 = cv::vx_load(row_ptr[3] + j); 
                auto p18 = cv::vx_load(row_ptr[3] + j + channel);
                auto p19 = cv::vx_load(row_ptr[3] + j + 2 * channel); 

                auto p20 = cv::vx_load(row_ptr[4] + j - 2 * channel);
                auto p21 = cv::vx_load(row_ptr[4] + j - channel); 
                auto p22 = cv::vx_load(row_ptr[4] + j); 
                auto p23 = cv::vx_load(row_ptr[4] + j + channel);
                auto p24 = cv::vx_load(row_ptr[4] + j + 2 * channel); 

                SwapSort(p1, p2); SwapSort(p0, p1); SwapSort(p1, p2); SwapSort(p4, p5); SwapSort(p3, p4);
                SwapSort(p4, p5); SwapSort(p0, p3); SwapSort(p2, p5); SwapSort(p2, p3); SwapSort(p1, p4);
                SwapSort(p1, p2); SwapSort(p3, p4); SwapSort(p7, p8); SwapSort(p6, p7); SwapSort(p7, p8);
                SwapSort(p10, p11); SwapSort(p9, p10); SwapSort(p10, p11); SwapSort(p6, p9); SwapSort(p8, p11);
                SwapSort(p8, p9); SwapSort(p7, p10); SwapSort(p7, p8); SwapSort(p9, p10); SwapSort(p0, p6);
                SwapSort(p4, p10); SwapSort(p4, p6); SwapSort(p2, p8); SwapSort(p2, p4); SwapSort(p6, p8);
                SwapSort(p1, p7); SwapSort(p5, p11); SwapSort(p5, p7); SwapSort(p3, p9); SwapSort(p3, p5);
                SwapSort(p7, p9); SwapSort(p1, p2); SwapSort(p3, p4); SwapSort(p5, p6); SwapSort(p7, p8);
                SwapSort(p9, p10); SwapSort(p13, p14); SwapSort(p12, p13); SwapSort(p13, p14); SwapSort(p16, p17);
                SwapSort(p15, p16); SwapSort(p16, p17); SwapSort(p12, p15); SwapSort(p14, p17); SwapSort(p14, p15);
                SwapSort(p13, p16); SwapSort(p13, p14); SwapSort(p15, p16); SwapSort(p19, p20); SwapSort(p18, p19);
                SwapSort(p19, p20); SwapSort(p21, p22); SwapSort(p23, p24); SwapSort(p21, p23); SwapSort(p22, p24);
                SwapSort(p22, p23); SwapSort(p18, p21); SwapSort(p20, p23); SwapSort(p20, p21); SwapSort(p19, p22);
                SwapSort(p22, p24); SwapSort(p19, p20); SwapSort(p21, p22); SwapSort(p23, p24); SwapSort(p12, p18);
                SwapSort(p16, p22); SwapSort(p16, p18); SwapSort(p14, p20); SwapSort(p20, p24); SwapSort(p14, p16);
                SwapSort(p18, p20); SwapSort(p22, p24); SwapSort(p13, p19); SwapSort(p17, p23); SwapSort(p17, p19);
                SwapSort(p15, p21); SwapSort(p15, p17); SwapSort(p19, p21); SwapSort(p13, p14); SwapSort(p15, p16);
                SwapSort(p17, p18); SwapSort(p19, p20); SwapSort(p21, p22); SwapSort(p23, p24); SwapSort(p0, p12);
                SwapSort(p8, p20); SwapSort(p8, p12); SwapSort(p4, p16); SwapSort(p16, p24); SwapSort(p12, p16);
                SwapSort(p2, p14); SwapSort(p10, p22); SwapSort(p10, p14); SwapSort(p6, p18); SwapSort(p6, p10);
                SwapSort(p10, p12); SwapSort(p1, p13); SwapSort(p9, p21); SwapSort(p9, p13); SwapSort(p5, p17);
                SwapSort(p13, p17); SwapSort(p3, p15); SwapSort(p11, p23); SwapSort(p11, p15); SwapSort(p7, p19);
                SwapSort(p7, p11); SwapSort(p11, p13); SwapSort(p11, p12);

                //保存结果
                cv::vx_store(row_dst + j, p12);
            }

            //处理不满足simd优化部分
            for(int j = vec_size; j < cols - 2 * channel; j++)
            {
                auto p0 = *(row_ptr[0] + j - 2 * channel);
                auto p1 = *(row_ptr[0] + j - channel); 
                auto p2 = *(row_ptr[0] + j); 
                auto p3 = *(row_ptr[0] + j + channel);
                auto p4 = *(row_ptr[0] + j + 2 * channel); 
 
                auto p5 = *(row_ptr[1] + j - 2 * channel);
                auto p6 = *(row_ptr[1] + j - channel); 
                auto p7 = *(row_ptr[1] + j); 
                auto p8 = *(row_ptr[1] + j + channel);
                auto p9 = *(row_ptr[1] + j + 2 * channel); 

                auto p10 = *(row_ptr[2] + j - 2 * channel);
                auto p11 = *(row_ptr[2] + j - channel); 
                auto p12 = *(row_ptr[2] + j); 
                auto p13 = *(row_ptr[2] + j + channel);
                auto p14 = *(row_ptr[2] + j + 2 * channel); 

                auto p15 = *(row_ptr[3] + j - 2 * channel);
                auto p16 = *(row_ptr[3] + j - channel); 
                auto p17 = *(row_ptr[3] + j); 
                auto p18 = *(row_ptr[3] + j + channel);
                auto p19 = *(row_ptr[3] + j + 2 * channel); 

                auto p20 = *(row_ptr[4] + j - 2 * channel);
                auto p21 = *(row_ptr[4] + j - channel); 
                auto p22 = *(row_ptr[4] + j); 
                auto p23 = *(row_ptr[4] + j + channel);
                auto p24 = *(row_ptr[4] + j + 2 * channel); 

                Op(p1, p2); Op(p0, p1); Op(p1, p2); Op(p4, p5); Op(p3, p4);
                Op(p4, p5); Op(p0, p3); Op(p2, p5); Op(p2, p3); Op(p1, p4);
                Op(p1, p2); Op(p3, p4); Op(p7, p8); Op(p6, p7); Op(p7, p8);
                Op(p10, p11); Op(p9, p10); Op(p10, p11); Op(p6, p9); Op(p8, p11);
                Op(p8, p9); Op(p7, p10); Op(p7, p8); Op(p9, p10); Op(p0, p6);
                Op(p4, p10); Op(p4, p6); Op(p2, p8); Op(p2, p4); Op(p6, p8);
                Op(p1, p7); Op(p5, p11); Op(p5, p7); Op(p3, p9); Op(p3, p5);
                Op(p7, p9); Op(p1, p2); Op(p3, p4); Op(p5, p6); Op(p7, p8);
                Op(p9, p10); Op(p13, p14); Op(p12, p13); Op(p13, p14); Op(p16, p17);
                Op(p15, p16); Op(p16, p17); Op(p12, p15); Op(p14, p17); Op(p14, p15);
                Op(p13, p16); Op(p13, p14); Op(p15, p16); Op(p19, p20); Op(p18, p19);
                Op(p19, p20); Op(p21, p22); Op(p23, p24); Op(p21, p23); Op(p22, p24);
                Op(p22, p23); Op(p18, p21); Op(p20, p23); Op(p20, p21); Op(p19, p22);
                Op(p22, p24); Op(p19, p20); Op(p21, p22); Op(p23, p24); Op(p12, p18);
                Op(p16, p22); Op(p16, p18); Op(p14, p20); Op(p20, p24); Op(p14, p16);
                Op(p18, p20); Op(p22, p24); Op(p13, p19); Op(p17, p23); Op(p17, p19);
                Op(p15, p21); Op(p15, p17); Op(p19, p21); Op(p13, p14); Op(p15, p16);
                Op(p17, p18); Op(p19, p20); Op(p21, p22); Op(p23, p24); Op(p0, p12);
                Op(p8, p20); Op(p8, p12); Op(p4, p16); Op(p16, p24); Op(p12, p16);
                Op(p2, p14); Op(p10, p22); Op(p10, p14); Op(p6, p18); Op(p6, p10);
                Op(p10, p12); Op(p1, p13); Op(p9, p21); Op(p9, p13); Op(p5, p17);
                Op(p13, p17); Op(p3, p15); Op(p11, p23); Op(p11, p15); Op(p7, p19);
                Op(p7, p11); Op(p11, p13); Op(p11, p12);

                *(row_dst + j) = p12;
            }
        }
        return 0;
    }
}//namespace mvk
