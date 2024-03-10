
#ifndef GRAPH_TASK_H
#define GRAPH_TASK_H

#include "image_manager.hpp"
#include <any>
#include <string>
#include <unordered_map>
#include <vector>

struct GraphContext;

std::string MergeName(const std::string& graph_name, const std::string& task_name);

class TaskDataManager
{
private:
    std::string name_;
    std::shared_ptr<ImageManager> image_manager_ = nullptr;
    std::unordered_map<std::string, std::any> data_list_;
public:
    TaskDataManager(const std::string& name, std::shared_ptr<ImageManager> image_manager);
    void ClearData();
    void CreateData(const std::string& name, const std::any);
    void CreateIntData(const std::string& name, const int value);
    void CreateFloatData(const std::string& name, const float value);
    void CreateStrData(const std::string& name, const std::string value);

    void CreateImage(const std::string& name, const std::uint32_t width, const std::uint32_t height, const std::uint32_t channel);
    void CreateImage(const std::string& name, void* data, const std::uint32_t width, const std::uint32_t height, const std::uint32_t channel);

    std::any GetData(const std::string& name);
    int SetData(const std::string& name, const std::any& value);
    std::string GetDataType(const std::string& name);
    std::any GetDefaultByType(const std::string& name);
    static bool DataTypeIsMatch(const std::string& type1, const std::string& type2);
};

struct TaskDataConfig
{
    std::string name_in_global;
    std::string type;
};

struct TaskDataConnect
{
    //front_info index: back task
    //front info first value: front task name
    //front info second value: front task output index
    std::vector<std::pair<std::string, std::size_t>> front_info;
    std::string back_task_name;
};

class Task
{
    std::shared_ptr<TaskDataManager> graph_data_manager_ = nullptr;
    std::unordered_map<std::string, TaskDataConfig> input_data_config_;
    std::unordered_map<std::string, TaskDataConfig> output_data_config_;
    std::vector<std::any> input_data_;

    void WriteOutputData(std::shared_ptr<GraphContext> context, const std::unordered_map<std::string, std::any>& output_data);
    int InitDataConfig(std::shared_ptr<GraphContext> context, const std::vector<std::pair<std::string, std::string>>& input_defines,
                       const std::vector<std::pair<std::string, std::string>>& output_defines);
protected:
    std::string name_;
    std::size_t id_;
    std::unordered_map<std::string, std::any> param_;
    std::unordered_map<std::string, std::any> output_data_;


    std::vector<std::any> GetInputData() const;
    std::unordered_map<std::string, std::any> GenerateOutputContainer(const std::vector<std::pair<std::string, std::string>>& output_defines);
public:
    Task(const std::string& name);
    std::string GetName() const;
    std::size_t GetID() const;
    static bool CheckLinkValid(const std::string& graph_name, const std::unordered_map<std::string, std::shared_ptr<Task>>& task_list,const TaskDataConnect& data_link);
    bool operator==(const Task& other);
    struct HashFunction
    {
        std::size_t operator()(const Task& key);
    };
    int Init(std::shared_ptr<GraphContext> context);
    int Run(std::shared_ptr<GraphContext> context);
    virtual int InitTask() = 0;
    int SetInputDataConfig(const std::string& name_in_task, const std::string& name_in_global);
    std::unordered_map<std::string, std::any> GetOutputData() const;
    int SetOutDataConfig(const std::string& name_in_task, const std::string& name_in_global);
    std::string GetGlobalDataName(const std::string& name_in_task);
    virtual int UpdateParams(const std::string& name, const std::any value) = 0;
    virtual int RunTask() = 0;
    virtual int Release();
    virtual std::vector<std::pair<std::string, std::string>> GetInputDefines() const = 0;
    virtual std::vector<std::pair<std::string, std::string>> GetOutputDefines() const = 0;
};

#endif //GRAPH_TASK_H
