/**
 * @file threshold.cpp
 * @author mango (2321544362@qq.com)
 * @brief 阈值化处理实现
 * @version 0.1
 * @date 2022-04-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "filter/threshold.hpp"
#include <cassert>
#include "opencv2/core/simd_intrinsics.hpp"
#include "omp.h"
#include <tuple>
#include <thread>
#include <execution>

namespace mvk
{
    static int ThresholdBinary(Image& src, Image& dst, const uint8_t thresh)
    {
        //simd参数初始化
        int rows = src.GetSize().height;
        int cols = src.GetSize().width;
        int data_size = rows * cols;

        int simd_size = cv::v_uint8::nlanes;
        int vec_size = data_size - data_size % simd_size;
        cv::v_uint8 v_zero = cv::vx_setzero_u8();
        cv::v_uint8 v_maxval = cv::vx_setall_u8(255);
        cv::v_uint8 v_thresh = cv::vx_setall_u8(thresh);

        //图像指针
        uint8_t* src_ptr = src.Ptr<std::uint8_t>(0, 0);
        uint8_t* dst_ptr = dst.Ptr<std::uint8_t>(0, 0);

        //并行+simd优化
#pragma omp parallel for
        for(int i = 0; i < vec_size; i += simd_size)
        {
            cv::v_uint8 v_src = cv::vx_load(src_ptr + i);
            cv::v_uint8 v_dst = cv::v_select(v_src > v_thresh, v_maxval, v_zero);
            cv::vx_store(dst_ptr + i, v_dst);
        }
        //处理不满足simd优化部分
        for(int i = vec_size; i < data_size; ++i)
        {
            dst_ptr[i] = src_ptr[i] > thresh ? 255 : 0;
        }
        return 0;
    }

    static int ThresholdBinaryInv(Image& src, Image& dst, const uint8_t thresh)
    {
        //simd参数初始化

        int rows = src.GetSize().height;
        int cols = src.GetSize().width;
        int data_size = rows * cols;

        constexpr std::size_t simd_size = cv::v_uint8::nlanes;
        int vec_size = data_size - data_size % simd_size;
        cv::v_uint8 v_zero = cv::vx_setzero_u8();
        cv::v_uint8 v_maxval = cv::vx_setall_u8(255);
        cv::v_uint8 v_thresh = cv::vx_setall_u8(thresh);

        //图像指针
        uint8_t* src_ptr = src.Ptr<std::uint8_t>(0, 0);
        uint8_t* dst_ptr = dst.Ptr<std::uint8_t>(0, 0);

        //并行+simd优化
#pragma omp parallel for
        for(int i = 0; i < vec_size; i += simd_size)
        {
            cv::v_uint8 v_src = cv::vx_load(src_ptr + i);
            cv::v_uint8 v_dst = cv::v_select(v_src > v_thresh, v_zero, v_maxval);
            cv::vx_store(dst_ptr + i, v_dst);
        }
        //处理不满足simd优化部分
        for(int i = vec_size; i < data_size; ++i)
        {
            dst_ptr[i] = src_ptr[i] > thresh ? 255 : 0;
        }
        return 0;
    }

    static int ThresholdTrunc(Image& src, Image& dst, const uint8_t thresh)
    {
        //simd参数初始化
        int rows = src.GetSize().height;
        int cols = src.GetSize().width;
        int data_size = rows * cols;
        constexpr std::size_t simd_size = cv::v_uint8::nlanes;
        int vec_size = data_size - data_size % simd_size;
        cv::v_uint8 v_zero = cv::vx_setzero_u8();
        cv::v_uint8 v_maxval = cv::vx_setall_u8(255);
        cv::v_uint8 v_thresh = cv::vx_setall_u8(thresh);

        //图像指针
        uint8_t* src_ptr = src.Ptr<std::uint8_t>(0, 0);
        uint8_t* dst_ptr = dst.Ptr<std::uint8_t>(0, 0);

        //并行+simd优化
#pragma omp parallel for
        for(int i = 0; i < vec_size; i += simd_size)
        {
            cv::v_uint8 v_src = cv::vx_load(src_ptr + i);
            cv::v_uint8 v_dst = cv::v_select(v_src > v_thresh, v_thresh, v_src);
            cv::vx_store(dst_ptr + i, v_dst);
        }
        //处理不满足simd优化部分
        for(int i = vec_size; i < data_size; ++i)
        {
            dst_ptr[i] = src_ptr[i] > thresh ? 255 : 0;
        }
        return 0;
    }

    static int ThresholdZero(Image& src, Image& dst, const uint8_t thresh)
    {
        //simd参数初始化

        int rows = src.GetSize().height;
        int cols = src.GetSize().width;
        int data_size = rows * cols;
        constexpr std::size_t simd_size = cv::v_uint8::nlanes;
        int vec_size = data_size - data_size % simd_size;
        cv::v_uint8 v_zero = cv::vx_setzero_u8();
        cv::v_uint8 v_maxval = cv::vx_setall_u8(255);
        cv::v_uint8 v_thresh = cv::vx_setall_u8(thresh);

        //图像指针
        uint8_t* src_ptr = src.Ptr<std::uint8_t>(0, 0);
        uint8_t* dst_ptr = dst.Ptr<std::uint8_t>(0, 0);

        //并行+simd优化
#pragma omp parallel for
        for(int i = 0; i < vec_size; i += simd_size)
        {
            cv::v_uint8 v_src = cv::vx_load(src_ptr + i);
            cv::v_uint8 v_dst = cv::v_select(v_src > v_thresh, v_src, v_zero);
            cv::vx_store(dst_ptr + i, v_dst);
        }
        //处理不满足simd优化部分
        for(int i = vec_size; i < data_size; ++i)
        {
            dst_ptr[i] = src_ptr[i] > thresh ? 255 : 0;
        }
        return 0;
    }

    static int ThresholdZeroInv(Image& src, Image& dst, const uint8_t thresh)
    {
        //simd参数初始化
        int rows = src.GetSize().height;
        int cols = src.GetSize().width;
        int data_size = rows * cols;
        constexpr std::size_t simd_size = cv::v_uint8::nlanes;
        int vec_size = data_size - data_size % simd_size;
        cv::v_uint8 v_zero = cv::vx_setzero_u8();
        cv::v_uint8 v_maxval = cv::vx_setall_u8(255);
        cv::v_uint8 v_thresh = cv::vx_setall_u8(thresh);

        //图像指针
        uint8_t* src_ptr = src.Ptr<std::uint8_t>(0, 0);
        uint8_t* dst_ptr = dst.Ptr<std::uint8_t>(0, 0);

        //并行+simd优化
#pragma omp parallel for
        for(int i = 0; i < vec_size; i += simd_size)
        {
            cv::v_uint8 v_src = cv::vx_load(src_ptr + i);
            cv::v_uint8 v_dst = cv::v_select(v_src > v_thresh, v_zero, v_src);
            cv::vx_store(dst_ptr + i, v_dst);
        }
        //处理不满足simd优化部分
        for(int i = vec_size; i < data_size; ++i)
        {
            dst_ptr[i] = src_ptr[i] > thresh ? 255 : 0;
        }
        return 0;
    }

    int Threshold(Image src, Image& dst, const uint8_t thresh, const THRESHOLD_TYPE type)
    {
        //参数检查
        if(src.IsEmpty()) {return -1;}

        //参数检查
        if(1 != src.Channels()) {return -1;}
        //todo: 如果是rgb三通道的，需要转为单通道
        //构造dst
        if(src.GetSize() != dst.GetSize())
        {
            src.CopyTo(dst);
        }

        //基于阈值化类型，做阈值化处理
        switch(type)
        {
            case THRESHOLD_TYPE::THRESH_BINARY:
            {
                return ThresholdBinary(src, dst, thresh);
            }
            case THRESHOLD_TYPE::THRESH_BINARY_INV:
            {
                return ThresholdBinaryInv(src, dst, thresh);
            }
            case THRESHOLD_TYPE::THRESH_TRUNC:
            {
                return ThresholdTrunc(src, dst, thresh);
            }
            case THRESHOLD_TYPE::THRESH_TOZERO:
            {
                return ThresholdZero(src, dst, thresh);
            }
            case THRESHOLD_TYPE::THRESH_TOZERO_INV:
            {
                return ThresholdZeroInv(src, dst, thresh);
            }
            default:
            {
                assert(false);
            }
        }
        return 0;
    }
}// namespace mvk
