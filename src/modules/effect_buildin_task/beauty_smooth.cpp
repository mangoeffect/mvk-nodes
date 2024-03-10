//
// Created by mango on 2024/3/8.
//

#include "beauty_smooth.hpp"
#include "filter/skin_detect.hpp"


BeautySmoothTask::BeautySmoothTask(const std::string& name): Task(name)
{

}

int BeautySmoothTask::InitTask()
{
    param_.insert(std::make_pair("smooth_type", std::make_any<SMOOTH_TYPE>(SMOOTH_TYPE::COLOR_SPACE)));
    param_.insert(std::make_pair("smooth_intensity", std::make_any<float>(1.0f)));
    return 0;
}

int BeautySmoothTask::UpdateParams(const std::string& name, const std::any value)
{

}

int BeautySmoothTask::RunTask()
{
    //1. get input data and params
    auto input_data = GetInputData();
    for(auto& data: input_data)
    {
        if(!data.has_value()) {return  -1;}
    }


    //process
    auto src = std::any_cast<Image>(input_data[0]);
    Image dst = std::any_cast<Image>(output_data_[output_defines_[0].first]);
    SMOOTH_TYPE type = std::any_cast<SMOOTH_TYPE>(param_["smooth_type"]);
    float intensity = std::any_cast<float>(param_["smooth_intensity"]);

    int ret = 0;
    switch (type)
    {
        case SMOOTH_TYPE::COLOR_SPACE:
        {
            ret = SmoothByColorSpace(src, dst, intensity);
            break;
        }
        default:
            ret = -1;
    }

    //2. set output data
    output_data_[output_defines_[0].first] = dst;
    return ret;
}

std::vector<std::pair<std::string, std::string>> BeautySmoothTask::GetInputDefines() const
{
    return input_defines_;
}

std::vector<std::pair<std::string, std::string>> BeautySmoothTask::GetOutputDefines() const
{
    return output_defines_;
}

int BeautySmoothTask::SmoothByColorSpace(Image& src, Image& dst, const float intensity)
{
    if(src.IsEmpty()){return -1;}

    if(intensity < 0.00001)
    {
        if(dst.GetSize() == src.GetSize() && dst.GetType() == src.GetType())
        {
            int data_size = dst.GetSize().height * dst.GetSize().width * dst.Channels();
            std::memcmp(src.Ptr<std::uint8_t>(0, 0), dst.Ptr<std::uint8_t>(0, 0), data_size);
        } else
        {
            src.CopyTo(dst);
        }
    }else
    {
        //1. mask
        Image mask;
        SkinDetectByColorSpace(src, mask);
    }

    return 0;
}
