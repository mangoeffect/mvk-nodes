//
// Created by mango on 2024/2/26.
//

#include "gaussian_filter_task.hpp"
#include "filter/gaussian_filter.hpp"

GaussianFilterTask::GaussianFilterTask(const std::string &name) : Task(name)
{

}

int GaussianFilterTask::InitTask()
{
    //init
    param_.insert(std::make_pair("kernel_size", std::make_any<int>(5)));
    param_.insert(std::make_pair("border_type", std::make_any<int>(BORDER_TYPE::MIRROR)));
    param_.insert(std::make_pair("sigma_x", std::make_any<float>(0.0f)));
    param_.insert(std::make_pair("sigma_y", std::make_any<float>(0.0f)));
}

int GaussianFilterTask::UpdateParams(const std::string& name, const std::any value)
{
    if(param_.find(name) != param_.end())
    {
        param_[name] = value;
    }
    return 0;
}

int GaussianFilterTask::RunTask()
{
    //get input data and params
    auto input_data = GetInputData();
    for(auto& data: input_data)
    {
        if(!data.has_value()) {return  -1;}
    }


    //process
    auto src = std::any_cast<Image>(input_data[0]);
    Image dst = std::any_cast<Image>(output_data_[output_defines_[0].first]);

    int ret = mvk::GaussianFilter(src, dst, std::any_cast<int>(param_["kernel_size"]),
                                  std::any_cast<float>(param_["sigma_x"]),
                                  std::any_cast<float>(param_["sigma_y"]),
                                  std::any_cast<BORDER_TYPE>(param_["border_type"]));

    //set output data
    output_data_[output_defines_[0].first] = dst;

    return ret;
}

std::vector<std::pair<std::string, std::string>> GaussianFilterTask::GetInputDefines() const
{
    return input_defines_;
}

std::vector<std::pair<std::string, std::string>> GaussianFilterTask::GetOutputDefines() const
{
    return output_defines_;
}

