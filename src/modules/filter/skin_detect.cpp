//
// Created by mango on 2024/3/7.
//


#include "skin_detect.hpp"

int SkinDetectByColorSpace(Image src, Image& dst)
{
    if(src.IsEmpty()){return -1;}

    dst = Image(src.GetSize(), IMAGE_TYPE::IMAGE_8UC1);
    int w = src.GetSize().width;
    int h = src.GetSize().height;

    auto hsv = src.Convert(CONVERT_TYPE::RGB2HSV);

    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
             auto r = src.Ptr<std::uint8_t>(j ,i)[0];
             auto g = src.Ptr<std::uint8_t>(j ,i)[1];
             auto b = src.Ptr<std::uint8_t>(j ,i)[2];
             auto h = hsv.Ptr<std::uint8_t>(j ,i)[0];
             auto s = hsv.Ptr<std::uint8_t>(j ,i)[1];
             auto v = src.Ptr<std::uint8_t>(j ,i)[2];

             if((h < 17 && 15 <= s && s <= 170)
                 && ((r > 95 && b > 20 && std::max({r , g, b}) - std::min({r, g, b}) > 15 && std::abs(r -g ) > 15 && r > g &&  r > b)
                        || (r > 220 && g > 210 && b > 170 && std::abs(r - g) <= 15 && r > b && g > b)))
             {
                 //is skin
                 dst.Ptr<std::uint8_t>(j, i)[0] = 255;
                 dst.Ptr<std::uint8_t>(j, i)[1] = 255;
                 dst.Ptr<std::uint8_t>(j, i)[2] = 255;
             }else
             {
                 dst.Ptr<std::uint8_t>(j, i)[0] = 0;
                 dst.Ptr<std::uint8_t>(j, i)[1] = 0;
                 dst.Ptr<std::uint8_t>(j, i)[2] = 0;
             }
        }
    }

    return 0;
}