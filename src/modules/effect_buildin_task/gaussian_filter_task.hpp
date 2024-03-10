//
// Created by mango on 2024/2/26.
//

#ifndef MANGO_GAUSSIAN_FILTER_TASK_HPP
#define MANGO_GAUSSIAN_FILTER_TASK_HPP

#include "core/task.hpp"

class GaussianFilterTask: public  Task
{
    //定义输入输出
    const std::vector<std::pair<std::string, std::string>> input_defines_ =
            {
                    {"input_0", typeid(Image).name()},
            };

    const std::vector<std::pair<std::string, std::string>> output_defines_ =
            {
                    {"output_0", typeid(Image).name()},
            };

public:
    GaussianFilterTask(const std::string& name);
    int InitTask() final;
    int UpdateParams(const std::string& name, const std::any value) final;
    int RunTask() final;

    std::vector<std::pair<std::string, std::string>> GetInputDefines() const final;
    std::vector<std::pair<std::string, std::string>> GetOutputDefines() const final;
};

#endif //MANGO_GAUSSIAN_FILTER_TASK_HPP
