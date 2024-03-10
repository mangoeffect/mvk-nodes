//
// Created by mango on 2024/2/26.
//


#include "face_task.hpp"
#include "vnn_face.h"

FaceTask::FaceTask(const std::string& name): Task(name)
{

}

int FaceTask::InitTask()
{
    return 0;
}

int FaceTask::UpdateParams(const std::string& name, const std::any value)
{

}

int FaceTask::RunTask()
{

}

std::vector<std::pair<std::string, std::string>> FaceTask::GetInputDefines() const
{
    return input_defines_;
}

std::vector<std::pair<std::string, std::string>> FaceTask::GetOutputDefines() const
{
    return output_defines_;
}