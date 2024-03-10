//
// Created by mango on 2024/2/28.
//

#include "blend.hpp"
#include <iostream>

int AddWeighted(Image src1, const float alpha, Image src2, const float beta, Image dst ,const float gamma)
{
    if(src1.IsEmpty() || src2.IsEmpty())
    {
        std::cerr<< "AddWeighted error, src1 or src2 is empty!" << std::endl;
        return -1;
    }
    if(src1.GetSize() != src2.GetSize() || src2.Channels() != src1.Channels())
    {
        std::cerr<< "AddWeighted error, src1 size != src2 size" << std::endl;
        return -1;
    }

    if(dst.GetSize() != src1.GetSize() || dst.Channels() != src1.Channels())
    {
        dst = src1.Clone();
    }

    int w = src1.GetSize().width;
    int h = src1.GetSize().height;
    int c = src1.Channels();

    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w;  j++)
        {
            for(int k = 0; k < c; k++)
            {
                dst.Ptr<std::uint8_t>(j, i)[k] = std::round(src1.Ptr<std::uint8_t>(j, i)[k] * alpha + src2.Ptr<std::uint8_t>(j, i)[k] * beta + gamma);
            }
        }
    }
    return 0;
}

int NormalBlend(Image src, Image blend, Image& dst)
{
    assert(src.Channels() == 4);
    if(src.IsEmpty() )
    {
        std::cerr<< "NormalBlend error, src1 is empty!" << std::endl;
        return -1;
    }
    if(blend.IsEmpty() || blend.GetSize() != src.GetSize())
    {
        std::cerr<< "NormalBlend error, blend" << std::endl;
    }

    if(src.Channels() != 4)
    {
        std::cerr<< "NormalBlend error, src not have alpha channel" << std::endl;
        return -1;
    }
    if(dst.GetSize() != src.GetSize() != dst.Channels() != src.Channels())
    {
        dst = src.Clone();
    }

    int w = src.GetSize().width;
    int h = src.GetSize().height;

    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w;  j++)
        {
            float alpha = src.Ptr<std::uint8_t>(j, i)[3] / 255.0;
            for(int k = 0; k < 3; k++)
            {
                dst.Ptr<std::uint8_t>(j, i)[k] = src.Ptr<std::uint8_t>(j, i)[k] * (1.0 - alpha)  + blend.Ptr<std::uint8_t>(j, i)[k] * alpha;
            }
            //src.Ptr<std::uint8_t>(j, i)[3] = 255;
        }
    }
    return 0;
}