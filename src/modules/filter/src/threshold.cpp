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
    static int ThresholdBinary(const Image& src, Image& dst, const uint8_t thresh)
    {
       //参数检查
        if(nullptr == src.GetData() || 1 != src.GetChannel()) {return -1;}
        int rows = src.GetHeight();
        int cols = src.GetWidth();
        int data_size = rows * cols;

        //构造dst
        uint8_t* data = new uint8_t[data_size]();
        dst = Image(data, rows, cols, IMAGE_FORMAT::MONO_8_BIT);

        //simd参数初始化
        int simd_size = cv::v_uint8::nlanes;
        int vec_size = data_size - data_size % simd_size;
        cv::v_uint8 v_zero = cv::vx_setzero_u8(); 
        cv::v_uint8 v_maxval = cv::vx_setall_u8(255);
        cv::v_uint8 v_thresh = cv::vx_setall_u8(thresh);

        //图像指针
        uint8_t* src_ptr = src.GetData();
        uint8_t* dst_ptr = dst.GetData();

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

    static int ThresholdBinaryInv(const Image& src, Image& dst, const uint8_t thresh)
    {
        //参数检查
        if(nullptr == src.GetData() || 1 != src.GetChannel()) {return -1;}
        int rows = src.GetHeight();
        int cols = src.GetWidth();
        int data_size = rows * cols;

        //构造dst
        uint8_t* data = new uint8_t[data_size]();
        dst = Image(data, rows, cols, IMAGE_FORMAT::MONO_8_BIT);

        //simd参数初始化
        constexpr std::size_t simd_size = cv::v_uint8::nlanes;
        int vec_size = data_size - data_size % simd_size;
        cv::v_uint8 v_zero = cv::vx_setzero_u8(); 
        cv::v_uint8 v_maxval = cv::vx_setall_u8(255);
        cv::v_uint8 v_thresh = cv::vx_setall_u8(thresh);

        //图像指针
        uint8_t* src_ptr = src.GetData();
        uint8_t* dst_ptr = dst.GetData();

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

    static int ThresholdTrunc(const Image& src, Image& dst, const uint8_t thresh)
    { 
        //参数检查
        if(nullptr == src.GetData() || 1 != src.GetChannel()) {return -1;}
        int rows = src.GetHeight();
        int cols = src.GetWidth();
        int data_size = rows * cols;

        //构造dst
        uint8_t* data = new uint8_t[data_size]();
        dst = Image(data, rows, cols, IMAGE_FORMAT::MONO_8_BIT);

        //simd参数初始化
        constexpr std::size_t simd_size = cv::v_uint8::nlanes;
        int vec_size = data_size - data_size % simd_size;
        cv::v_uint8 v_zero = cv::vx_setzero_u8(); 
        cv::v_uint8 v_maxval = cv::vx_setall_u8(255);
        cv::v_uint8 v_thresh = cv::vx_setall_u8(thresh);

        //图像指针
        uint8_t* src_ptr = src.GetData();
        uint8_t* dst_ptr = dst.GetData();

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

    static int ThresholdZero(const Image& src, Image& dst, const uint8_t thresh)
    {
        //参数检查
        if(nullptr == src.GetData() || 1 != src.GetChannel()) {return -1;}
        int rows = src.GetHeight();
        int cols = src.GetWidth();
        int data_size = rows * cols;

        //构造dst
        uint8_t* data = new uint8_t[data_size]();
        dst = Image(data, rows, cols, IMAGE_FORMAT::MONO_8_BIT);

        //simd参数初始化
        constexpr std::size_t simd_size = cv::v_uint8::nlanes;
        int vec_size = data_size - data_size % simd_size;
        cv::v_uint8 v_zero = cv::vx_setzero_u8(); 
        cv::v_uint8 v_maxval = cv::vx_setall_u8(255);
        cv::v_uint8 v_thresh = cv::vx_setall_u8(thresh);

        //图像指针
        uint8_t* src_ptr = src.GetData();
        uint8_t* dst_ptr = dst.GetData();

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

    static int ThresholdZeroInv(const Image& src, Image& dst, const uint8_t thresh)
    {
                //参数检查
        if(nullptr == src.GetData() || 1 != src.GetChannel()) {return -1;}
        int rows = src.GetHeight();
        int cols = src.GetWidth();
        int data_size = rows * cols;

        //构造dst
        uint8_t* data = new uint8_t[data_size]();
        dst = Image(data, rows, cols, IMAGE_FORMAT::MONO_8_BIT);

        //simd参数初始化
        constexpr std::size_t simd_size = cv::v_uint8::nlanes;
        int vec_size = data_size - data_size % simd_size;
        cv::v_uint8 v_zero = cv::vx_setzero_u8(); 
        cv::v_uint8 v_maxval = cv::vx_setall_u8(255);
        cv::v_uint8 v_thresh = cv::vx_setall_u8(thresh);

        //图像指针
        uint8_t* src_ptr = src.GetData();
        uint8_t* dst_ptr = dst.GetData();

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

    int Threshold(const Image& src, Image& dst, const uint8_t thresh, const THRESHOLD_TYPE type)
    {
        //参数检查
        if(nullptr == src.GetData()) {return -1;}

        //todo: 如果是rgb三通道的，需要转为mono单通道
        
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
