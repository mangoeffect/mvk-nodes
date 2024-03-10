//
// Created by mango on 2024/3/8.
//

#ifndef MANGO_BEAUTY_SMOOTH_H
#define MANGO_BEAUTY_SMOOTH_H

#include "core/task.hpp"

enum SMOOTH_TYPE
{
    COLOR_SPACE = 0
};

class BeautySmoothTask: public  Task
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
    BeautySmoothTask(const std::string& name);
    int InitTask() final;
    int UpdateParams(const std::string& name, const std::any value) final;
    int RunTask() final;

    std::vector<std::pair<std::string, std::string>> GetInputDefines() const final;
    std::vector<std::pair<std::string, std::string>> GetOutputDefines() const final;
private:
    int SmoothByColorSpace(Image& src, Image& dst, const float intensity);
    std::uint32_t  face_handle_ = 0;
};

#endif //MANGO_BEAUTY_SMOOTH_H
