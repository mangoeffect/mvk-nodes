/**
 * @file integral_image.cpp
 * @author mango (2321544362@qq.com)
 * @brief 积分图
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "integral_image.hpp"

namespace mvk
{
    int ComputeIntegralMultiChannels(Image& src, Matrix<uint64_t>& integral)
    {
        size_t  height = src.GetSize().height;
        size_t  width = src.GetSize().width;
        size_t channels = src.Channels();
        
        integral = Matrix<uint64_t>(height, width * channels);

        //左上角首个元素
        for(size_t i  = 0; i < channels; i++)
        {
            integral(0, i) = src.Ptr<std::uint8_t>(0, 0)[i];
        }

        //处理首行
        for(size_t i = 1; i < width; i++)
        {
            for(size_t j = 0; j < channels; j++)
            {
                integral(0, i * channels + j) = integral(0, (i - 1) * channels + j) + src.Ptr<std::uint8_t>(i, 0)[j];
            }
        }

        //处理首列
        for(size_t i = 1; i < height; i++)
        {
            for(size_t j = 0; j < channels; j++)
            {
                integral(i, j) = integral(i -1, j) + src.Ptr<std::uint8_t>(0, i)[j];
            }
        }

        for(size_t i = 1; i < height; i++) // row
        {
            for(size_t j = 1; j < width; j++) //col
            {
                for(size_t k = 0; k < channels; k++)
                {
                    integral(i, j * channels + k) = integral(i - 1, j * channels + k) +  integral(i, (j - 1)* channels + k) - integral(i - 1, (j - 1) * channels + k) + src.Ptr<std::uint8_t>(j, i)[k];
                }
            }
        }
        return 0;
    }

    int ComputeIntegral(Image& src, Matrix<uint64_t>& integral)
    {
        if(src.IsEmpty()){return -1;}

        if(src.Channels() > 1)
        {
            return ComputeIntegralMultiChannels(src, integral);
        }

        size_t  height = src.GetSize().height;
        size_t  width = src.GetSize().width;

        integral = Matrix<uint64_t>(height, width);

        //左上角首个元素
        integral(0, 0) = src.At<std::uint8_t>(0, 0);

        //处理首行
        for(size_t i = 1; i < width; i++)
        {
            integral(0, i) = integral(0, i - 1) + src.At<std::uint8_t>( i, 0);
        }
        //处理首列
        for(size_t i = 1; i < height; i++)
        {
            integral(i, 0) = integral(i -1, 0) + src.At<std::uint8_t>( 0, i);
        }

        for(size_t i = 1; i < height; i++) // row
        {
            for(size_t j = 1; j < width; j++) //col
            {
                integral(i, j) = integral(i - 1, j) +  integral(i, j - 1) - integral(i - 1, j - 1) + src.At<std::uint8_t>(j, i);
            }
        }
        return 0;
    }
}//namespace mvk

