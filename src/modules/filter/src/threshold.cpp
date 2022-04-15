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
#include "xsimd/xsimd.hpp"
#include "omp.h"


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
        uint8_t* data = new uint8_t[data_size];
        dst = Image(data, rows, cols, IMAGE_FORMAT::MONO_8_BIT);

        //simd参数初始化
        constexpr std::size_t simd_size = xsimd::simd_type<uint8_t>::size;
        int vec_size = data_size - data_size % simd_size;
        std::vector<uint8_t> zero(simd_size, 0);   
        std::vector<uint8_t> maxval(simd_size, 255);   
        std::vector<uint8_t> thresh_vec(simd_size, thresh);   
        auto v_zero = xsimd::load_unaligned(&zero[0]);
        auto v_maxval = xsimd::load_unaligned(&maxval[0]);  
        auto v_thresh = xsimd::load_unaligned(&thresh_vec[0]);  

        //图像指针
        uint8_t* src_ptr = src.GetData();
        uint8_t* dst_ptr = dst.GetData();

        //并行+simd优化
        #pragma omp parallel for 
        for(int i = 0; i < vec_size; i += simd_size)
        {
            auto v_src = xsimd::load_unaligned(src_ptr + i);
            auto v_dst = xsimd::select(v_src > v_thresh, v_maxval, v_zero);
            v_dst.store_unaligned(dst_ptr + i);
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
        uint8_t* data = new uint8_t[data_size];
        dst = Image(data, rows, cols, IMAGE_FORMAT::MONO_8_BIT);

        //simd参数初始化
        constexpr std::size_t simd_size = xsimd::simd_type<uint8_t>::size;
        int vec_size = data_size - data_size % simd_size;
        std::vector<uint8_t> zero(simd_size, 0);   
        std::vector<uint8_t> maxval(simd_size, 255);   
        std::vector<uint8_t> thresh_vec(simd_size, thresh);   
        auto v_zero = xsimd::load_unaligned(&zero[0]);
        auto v_maxval = xsimd::load_unaligned(&maxval[0]);  
        auto v_thresh = xsimd::load_unaligned(&thresh_vec[0]);  

        //图像指针
        uint8_t* src_ptr = src.GetData();
        uint8_t* dst_ptr = dst.GetData();

        //并行+simd优化
        #pragma omp parallel for 
        for(int i = 0; i < vec_size; i += simd_size)
        {
            auto v_src = xsimd::load_unaligned(src_ptr + i);
            auto v_dst = xsimd::select(v_src < v_thresh, v_maxval, v_zero);
            v_dst.store_unaligned(dst_ptr + i);
        }
        //处理不满足simd优化部分
        for(int i = vec_size; i < data_size; ++i)
        {
            dst_ptr[i] = src_ptr[i] < thresh ? 255 : 0;
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
        uint8_t* data = new uint8_t[data_size];
        dst = Image(data, rows, cols, IMAGE_FORMAT::MONO_8_BIT);

        //simd参数初始化
        constexpr std::size_t simd_size = xsimd::simd_type<uint8_t>::size;
        int vec_size = data_size - data_size % simd_size;
        std::vector<uint8_t> zero(simd_size, 0);   
        std::vector<uint8_t> maxval(simd_size, 255);   
        std::vector<uint8_t> thresh_vec(simd_size, thresh);   
        auto v_zero = xsimd::load_unaligned(&zero[0]);
        auto v_maxval = xsimd::load_unaligned(&maxval[0]);  
        auto v_thresh = xsimd::load_unaligned(&thresh_vec[0]);  

        //图像指针
        uint8_t* src_ptr = src.GetData();
        uint8_t* dst_ptr = dst.GetData();

        //并行+simd优化
        #pragma omp parallel for 
        for(int i = 0; i < vec_size; i += simd_size)
        {
            auto v_src = xsimd::load_unaligned(src_ptr + i);
            auto v_dst = xsimd::select(v_src > v_thresh, v_thresh, v_src);
            v_dst.store_unaligned(dst_ptr + i);
        }
        //处理不满足simd优化部分
        for(int i = vec_size; i < data_size; ++i)
        {
            dst_ptr[i] = src_ptr[i] > thresh ? thresh : src_ptr[i];
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
        uint8_t* data = new uint8_t[data_size];
        dst = Image(data, rows, cols, IMAGE_FORMAT::MONO_8_BIT);

        //simd参数初始化
        constexpr std::size_t simd_size = xsimd::simd_type<uint8_t>::size;
        int vec_size = data_size - data_size % simd_size;
        std::vector<uint8_t> zero(simd_size, 0);   
        std::vector<uint8_t> maxval(simd_size, 255);   
        std::vector<uint8_t> thresh_vec(simd_size, thresh);   
        auto v_zero = xsimd::load_unaligned(&zero[0]);
        auto v_maxval = xsimd::load_unaligned(&maxval[0]);  
        auto v_thresh = xsimd::load_unaligned(&thresh_vec[0]);  

        //图像指针
        uint8_t* src_ptr = src.GetData();
        uint8_t* dst_ptr = dst.GetData();

        //并行+simd优化
        #pragma omp parallel for 
        for(int i = 0; i < vec_size; i += simd_size)
        {
            auto v_src = xsimd::load_unaligned(src_ptr + i);
            auto v_dst = xsimd::select(v_src > v_thresh, v_src, v_zero);
            v_dst.store_unaligned(dst_ptr + i);
        }
        //处理不满足simd优化部分
        for(int i = vec_size; i < data_size; ++i)
        {
            dst_ptr[i] = src_ptr[i] > thresh ? src_ptr[i] : 0;
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
        uint8_t* data = new uint8_t[data_size];
        dst = Image(data, rows, cols, IMAGE_FORMAT::MONO_8_BIT);

        //simd参数初始化
        constexpr std::size_t simd_size = xsimd::simd_type<uint8_t>::size;
        int vec_size = data_size - data_size % simd_size;
        std::vector<uint8_t> zero(simd_size, 0);   
        std::vector<uint8_t> maxval(simd_size, 255);   
        std::vector<uint8_t> thresh_vec(simd_size, thresh);   
        auto v_zero = xsimd::load_unaligned(&zero[0]);
        auto v_maxval = xsimd::load_unaligned(&maxval[0]);  
        auto v_thresh = xsimd::load_unaligned(&thresh_vec[0]);  

        //图像指针
        uint8_t* src_ptr = src.GetData();
        uint8_t* dst_ptr = dst.GetData();

        //并行+simd优化
        #pragma omp parallel for 
        for(int i = 0; i < vec_size; i += simd_size)
        {
            auto v_src = xsimd::load_unaligned(src_ptr + i);
            auto v_dst = xsimd::select(v_src > v_thresh, v_zero, v_src);
            v_dst.store_unaligned(dst_ptr + i);
        }
        //处理不满足simd优化部分
        for(int i = vec_size; i < data_size; ++i)
        {
            dst_ptr[i] = src_ptr[i] > thresh ? 0 : src_ptr[i];
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
