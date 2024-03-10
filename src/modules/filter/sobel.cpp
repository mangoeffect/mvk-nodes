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
#include "opencv2/core/simd_intrinsics.hpp"

namespace mvk
{
    int Sobel(Image src, Image& dst, Matrix<float>& Gx, Matrix<float>& Gy)
    {
        //参数检查、初始化
        if(src.IsEmpty() || 1 != src.Channels()) {return -1;}
        int rows = src.GetSize().height;
        int cols = src.GetSize().width;

        //构造dst
        if(src.GetSize() != dst.GetSize())
        {
            src.CopyTo(dst);
        }

        constexpr std::size_t simd_size = cv::v_int16::nlanes;
        cv::v_float32 v_nine = cv::vx_setall_f32(9.0f);
        int vec_size1 = cols - (cols - 2) % simd_size - 2;
        int vec_size2 = cols - cols % simd_size;
        short* tx = new short[rows * cols]();
        short* ty = new short[rows * cols]();

        //1x3行方向卷积处理
#pragma omp parallel for
        for(int i = 0; i < rows; i++)
        {
            uint8_t* src_ptr = src.Ptr<std::uint8_t>(0, i);
            short* tx_ptr = tx + cols * i;
            short* ty_ptr = ty + cols * i;
            for(int j = 1; j < vec_size1; j += simd_size)
            {
                cv::v_int16 v_src0 = cv::v_reinterpret_as_s16(cv::vx_load_expand(src_ptr + j - 1));
                cv::v_int16 v_src1 = cv::v_reinterpret_as_s16(cv::vx_load_expand(src_ptr + j));
                cv::v_int16 v_src2 = cv::v_reinterpret_as_s16(cv::vx_load_expand(src_ptr + j + 1));

                // sxx -1 0 1
                cv::v_int16 v_gx = (v_src2 - v_src0);
                cv::v_store(tx_ptr + j, v_gx);

                // syx 1 2 1
                cv::v_int16 v_gy = (v_src0 + v_src1 + v_src1 + v_src2);
                cv::v_store(ty_ptr + j, v_gy);
            }
            for(int j = vec_size1; j < cols - 1; j++)
            {
                // sxx -1 0 1
                tx_ptr[j] = static_cast<short>(-src_ptr[j - 1] + src_ptr[j + 1]);
                // syx 1 2 1
                ty_ptr[j] = static_cast<short>(src_ptr[j- 1] + src_ptr[j] + src_ptr[j] + src_ptr[j + 1]);
            }
        }

        //3x1列方向卷积处理
#pragma omp parallel for
        for(int i = 1; i < rows - 1; i++)
        {
            uint8_t* dst_ptr = dst.Ptr<std::uint8_t>(0, i);
            short* tx_ptr0 = tx + cols * (i - 1);
            short* tx_ptr1 = tx + cols * i;
            short* tx_ptr2 = tx + cols * i + 1;
            short* ty_ptr0 = ty + cols * (i - 1) ;
            short* ty_ptr1 = ty + cols * i;
            short* ty_ptr2 = ty + cols * (i + 1);

            float* gx_ptr = &Gx(i, 0);
            float* gy_ptr = &Gy(i, 0);

            for(int j = 0; j < vec_size2; j += simd_size)
            {
                // sxy 1 2 1
                cv::v_int16 v_tx0 = cv::vx_load(tx_ptr0 + j);
                cv::v_int16 v_tx1 = cv::vx_load(tx_ptr1 + j);
                cv::v_int16 v_tx2 = cv::vx_load(tx_ptr2 + j);
                cv::v_int16 v_gx_short = (v_tx0 + v_tx1 + v_tx1 + v_tx2);
                cv::v_int32 v_gx_int1, v_gx_int2;
                cv::v_expand(v_gx_short, v_gx_int1, v_gx_int2);
                cv::v_float32 v_gx1 = cv::v_cvt_f32(v_gx_int1) / v_nine;
                cv::v_float32 v_gx2 = cv::v_cvt_f32(v_gx_int2) / v_nine;
                cv::v_store(&Gx(i, j), v_gx1);
                cv::v_store(&Gx(i, j) + cv::v_float32::nlanes, v_gx2);

                // syy -1 0 1
                cv::v_int16 v_ty0 = cv::vx_load(ty_ptr0 + j);
                cv::v_int16 v_ty2 = cv::vx_load(ty_ptr2 + j);
                cv::v_int16 v_gy_short = (v_ty2 - v_ty0);
                cv::v_int32 v_gy_int1, v_gy_int2;
                cv::v_expand(v_gy_short, v_gy_int1, v_gy_int2);
                cv::v_float32 v_gy1 = cv::v_cvt_f32(v_gy_int1) / v_nine;
                cv::v_float32 v_gy2 = cv::v_cvt_f32(v_gy_int2) / v_nine;
                cv::v_store(&Gy(i, j), v_gy1);
                cv::v_store(&Gy(i, j) + cv::v_float32::nlanes, v_gy2);

                //梯度幅值
                cv::v_float32 v_magf1 = cv::v_magnitude(v_gx1, v_gy1);
                cv::v_float32 v_magf2 = cv::v_magnitude(v_gx2, v_gy2);
                cv::v_uint16 v_mag = cv::v_pack(cv::v_reinterpret_as_u32(cv::v_round(v_magf1)), cv::v_reinterpret_as_u32(cv::v_round(v_magf2)));
                cv::v_pack_store(dst_ptr + j, v_mag);
            }

            for(int j = vec_size2; j < cols; j++)
            {
                // sxy 1 2 1
                gx_ptr[j] = (tx_ptr0[j] +  tx_ptr1[j] + tx_ptr1[j] + tx_ptr2[j]) / 9.0;
                // syy -1 0 1
                gy_ptr[j] = (ty_ptr2[j] - ty_ptr0[j]) / 9.0;
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
