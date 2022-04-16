/**
 * @file sobel.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "filter/sobel.hpp"
#include <cmath>
#include "omp.h"
#include "xsimd/xsimd.hpp"

namespace mvk
{
    int Sobel(const Image& src, Image& dst, Matrix<float>& Gx, Matrix<float>& Gy)
    {   
        //参数检查、初始化
        if(nullptr == src.GetData() || 1 != src.GetChannel()) {return -1;}
        int rows = src.GetHeight();
        int cols = src.GetWidth();

        dst = src.Copy();

        constexpr std::size_t simd_size = xsimd::simd_type<float>::size;
        int vec_size1 = cols - (cols - 2) % simd_size - 2;
        int vec_size2 = cols - cols % simd_size;
        float* tx = new float[rows * cols];
        float* ty = new float[rows * cols];

        //1x3行方向卷积处理
        #pragma omp parallel for
        for(int i = 0; i < rows; i++)
        {
            uint8_t* src_ptr = src.GetRow(i);
            float* tx_ptr = tx + cols * i;
            float* ty_ptr = ty + cols * i;
            for(int j = 1; j < vec_size1; j += simd_size)
            {
                auto v_src0 = xsimd::load_as<float>(src_ptr + j - 1, xsimd::unaligned_mode());
                auto v_src1 = xsimd::load_as<float>(src_ptr + j,     xsimd::unaligned_mode());
                auto v_src2 = xsimd::load_as<float>(src_ptr + j + 1, xsimd::unaligned_mode());
                // sxx -1 0 1
                auto v_gx = (v_src2 - v_src0) / 3;
                v_gx.store_unaligned(tx_ptr + j);
                
                // syx 1 2 1
                auto v_gy = (v_src0 + v_src1 + v_src1 + v_src2) / 3;
                v_gy.store_unaligned(ty_ptr + j);
            }
            for(int j = vec_size1; j < cols - 1; j++)
            {
                // sxx -1 0 1
                tx_ptr[j] = static_cast<float>(-*(src_ptr + j - 1) + *(src_ptr + j + 1)) / 3.0;
                // syx 1 2 1
                ty_ptr[j] = static_cast<float>( *(src_ptr + j- 1) + 2.0 * (*(src_ptr + j)) + *(src_ptr + j + 1)) / 3.0;
            }
        }

        //3x1列方向卷积处理
        #pragma omp parallel for
        for(int i = 1; i < rows - 1; i++)
        {
            uint8_t* dst_ptr = dst.GetRow(i);
            float* tx_ptr0 = tx + cols * (i - 1);
            float* tx_ptr1 = tx + cols * i;
            float* tx_ptr2 = tx + cols * i + 1;
            float* ty_ptr0 = ty + cols * (i - 1) ;
            float* ty_ptr1 = ty + cols * i;
            float* ty_ptr2 = ty + cols * (i + 1);

            for(int j = 0; j < vec_size2; j += simd_size)
            {
                 // sxy 1 2 1
                 auto v_tx0 = xsimd::load_unaligned(tx_ptr0 + j);
                 auto v_tx1 = xsimd::load_unaligned(tx_ptr1 + j);
                 auto v_tx2 = xsimd::load_unaligned(tx_ptr2 + j);
                 auto v_gx = (v_tx0 + v_tx1 + v_tx1 + v_tx2) / 3;
                 v_gx.store_unaligned(&Gx(i, j));

                 // syy -1 0 1
                 auto v_ty0 = xsimd::load_unaligned(ty_ptr0 + j);
                 auto v_ty2 = xsimd::load_unaligned(ty_ptr2 + j);
                 auto v_gy = (v_ty2 - v_ty0) / 3;
                 v_gy.store_unaligned(&Gy(i, j));

                 //梯度幅值
                 auto v_mag = xsimd::sqrt(v_gx * v_gx + v_gy * v_gy);
                 xsimd::store_as<uint8_t>(dst_ptr + j, v_mag, xsimd::unaligned_mode());
            }

            for(int j = vec_size2; j < cols; j++)
            {
                // sxy 1 2 1
                Gx(i, j) = (tx_ptr0[j] + 2.0 * tx_ptr1[j] + tx_ptr2[j]) / 3.0;
                // syy -1 0 1
                Gy(i, j) = (ty_ptr2[j] - ty_ptr0[j]) / 3.0;
                dst_ptr[j] = static_cast<uint8_t>(std::sqrt(Gx(i, j) * Gx(i, j) + Gy(i, j) * Gy(i, j)));
            }
        }
        delete[] tx;
        tx = nullptr;
        delete[] ty;
        ty = nullptr;
        return 0;
    }
}//namespace mvk
