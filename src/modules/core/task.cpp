
#include "task.hpp"
#include "graph.hpp"

std::string MergeName(const std::string& graph_name, const std::string& task_name)
{
    return graph_name + "_" + task_name;
}

TaskDataManager::TaskDataManager(const std::string &name, std::shared_ptr<ImageManager> image_manager)
: name_(name), image_manager_(image_manager)
{

}

void TaskDataManager::ClearData()
{
    image_manager_->ClearAllImages();
    data_list_.clear();
}

void TaskDataManager::CreateData(const std::string &name, const std::any value)
{
    data_list_[name] = value;
}

void TaskDataManager::CreateIntData(const std::string& name, const int value)
{
    data_list_[name] = value;
}

void TaskDataManager::CreateFloatData(const std::string& name, const float value)
{
    data_list_[name] = value;
}

void TaskDataManager::CreateStrData(const std::string& name, const std::string value)
{
    data_list_[name] = value;
}


void TaskDataManager::CreateImage(const std::string &name, const std::uint32_t width, const std::uint32_t height,
                                  const std::uint32_t channel)
{
    if(image_manager_ != nullptr)
    {
        auto img = image_manager_->CreateImage(width, height, channel);
        data_list_[name] = img;
    }
}

void
TaskDataManager::CreateImage(const std::string &name, void *data, const std::uint32_t width, const std::uint32_t height,
                             const std::uint32_t channel)
{
    if(image_manager_ != nullptr && data != nullptr)
    {
        data_list_[name] = image_manager_->CreateImage(data, width, height, channel);
    }
}

std::any TaskDataManager::GetData(const std::string& name)
{
    if(data_list_.find(name) != data_list_.end())
    {
        return data_list_[name];
    }else
    {
        return std::any();
    }
}

int TaskDataManager::SetData(const std::string& name, const std::any& value)
{
    if(data_list_.find(name) != data_list_.end())
    {
        data_list_[name] = value;
        return 0;
    }
    return -1;
}

std::string TaskDataManager::GetDataType(const std::string& name)
{
    std::any value = GetData(name);
    std::string type = "";
    if(value.has_value())
    {
        type = value.type().name();
    }
    return type;
}

std::any TaskDataManager::GetDefaultByType(const std::string& name)
{
    if(name == typeid(int).name())
    {
        int value = 0;
        return value;
    }else if(name == typeid(float).name())
    {
        float value = 0.0f;
        return value;
    }else if(name == typeid(double).name())
    {
        double value = 0.0;
        return  value;
    }else if(name == typeid(std::string).name())
    {
        std::string value = "default";
        return value;
    }else if(name == typeid(Image).name())
    {
        Image value;
        return value;
    }
    return  std::any();
}

bool TaskDataManager::DataTypeIsMatch(const std::string &type1, const std::string &type2)
{
    bool t1_is_str =   type1 == typeid(const char*).name() || type1 == typeid(std::string).name();
    bool t2_is_str =   type2 == typeid(const char*).name() || type2 == typeid(std::string).name();

    return (type1 == type2) || (t1_is_str && t2_is_str);
}

std::string Task::GetName() const
{
    return name_;
}

int Task::Init(std::shared_ptr<GraphContext> context)
{
    InitDataConfig(context, GetInputDefines(), GetOutputDefines());
    graph_data_manager_ = context->graph_data_manager;
    return InitTask();
}

int Task::Run(std::shared_ptr<GraphContext> context)
{
    //parse input data
    input_data_.clear();
    for(auto& [name, type] : GetInputDefines())
    {
        if(auto m = input_data_config_.find(name); m != input_data_config_.end())
        {
            auto data = context->graph_data_manager->GetData(m->second.name_in_global);
            if(data.has_value())
            {
                input_data_.emplace_back(data);
            }else
            {
                return -1;
            }
        }
    }
    //ready output data container
    auto output_defines = GetOutputDefines();
    output_data_ = GenerateOutputContainer(output_defines);
    for(int i = 0; i < output_data_.size(); ++i)
    {
        auto type = output_defines[i].second;
        if(type == typeid(Image*).name())
        {
            auto name_in_task = output_defines[i].first;
            output_data_[name_in_task] = context->graph_data_manager->GetData(GetGlobalDataName(name_in_task));
        }
    }

    //run task
    RunTask();

    //write output data
    WriteOutputData(context, output_data_);

    return 0;
}

bool Task::CheckLinkValid(const std::string& graph_name,
                          const std::unordered_map<std::string, std::shared_ptr<Task>> &task_list,
                          const TaskDataConnect &data_link)
{
    if(auto back = task_list.find( data_link.back_task_name); back != task_list.end())
    {
        auto back_input_defines = back->second->GetInputDefines();
        if(back_input_defines.size() == data_link.front_info.size())
        {
            for(int i = 0; i < back_input_defines.size(); i++)
            {
                std::string back_input_name_in_task = back_input_defines[i].first;
                std::string back_input_type = back_input_defines[i].second;
                std::string front_task_name = data_link.front_info[i].first;
                if(auto front_task = task_list.find(front_task_name); front_task != task_list.end())
                {
                    auto front_output_defines = front_task->second->GetOutputDefines();
                    if(std::size_t output_index = data_link.front_info[i].second; output_index < front_output_defines.size())
                    {
                        if(front_output_defines[output_index].second == back_input_type)
                        {
                            std::string front_output_name_in_task = front_output_defines[output_index].first;
                            std::string global_name = front_task->second->GetGlobalDataName(front_output_name_in_task);
                            back->second->SetInputDataConfig(back_input_name_in_task, global_name);
                        }else
                        {
                            return false;
                        }
                    }else
                    {
                        return  false;
                    }
                }else
                {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

std::size_t Task::GetID() const
{
    return id_;
}

int Task::Release()
{
    param_.clear();
    return 0;
}

Task::Task(const std::string &name) : name_(name)
{

}

int Task::InitDataConfig(std::shared_ptr<GraphContext> context, const std::vector<std::pair<std::string, std::string>> &input_defines,
                          const std::vector<std::pair<std::string, std::string>> &output_defines)
{
    if(context == nullptr){return -1;}
    input_data_config_.clear();
    for(auto& [name, type]: input_defines)
    {
        input_data_config_.insert(std::make_pair(name, TaskDataConfig{"default", type}));
    }
    output_data_config_.clear();
    for(auto& [name, type]: output_defines)
    {
        std::string name_in_global = MergeName(GetName(), name);
        if(typeid(Image).name() == type)
        {
            context->graph_data_manager->CreateImage(name_in_global,0, 0, 0);
        }else
        {
            context->graph_data_manager->CreateData(name_in_global, context->graph_data_manager->GetDefaultByType(type));
        }
        output_data_config_.insert(std::make_pair(name, TaskDataConfig{name_in_global, type}));
    }
}

std::vector<std::any> Task::GetInputData() const
{
    return  input_data_;
}

void Task::WriteOutputData(std::shared_ptr<GraphContext> context, const std::unordered_map<std::string , std::any> &output_data)
{
    //check type is valid
    if(output_data.size() != output_data_config_.size()) { return; }

    for(auto& [name, config]: output_data_config_)
    {
        if(auto data = output_data.find(name); data != output_data.end()
                                               && data->second.type().name() == config.type)
        {
            context->graph_data_manager->SetData(config.name_in_global, data->second);
        }
    }
}

std::unordered_map<std::string, std::any> Task::GenerateOutputContainer(const std::vector<std::pair<std::string, std::string>>& output_defines)
{
    std::unordered_map<std::string, std::any> container;
    for(auto& [name, type]: output_defines)
    {
        if(type == typeid(Image).name())
        {
            container.insert(std::make_pair(name, Image()));
        }else
        {
            container.insert(std::make_pair(name, std::any()));
        }
    }
    return container;
}




bool Task::operator==(const Task& other)
{
    return name_ == other.GetName() && id_ == other.GetID();
}

std::size_t Task::HashFunction::operator()(const Task &key)
{
    return std::hash<int>()(key.GetID()) ^ (std::hash<std::string>()(key.GetName()) << 1);
}

int Task::SetInputDataConfig(const std::string& name_in_task, const std::string& name_in_global)
{
    if(input_data_config_.find(name_in_task) != input_data_config_.end())
    {
        if(TaskDataManager::DataTypeIsMatch(input_data_config_[name_in_task].type,
                                            graph_data_manager_->GetDataType(name_in_global)))
        {
            input_data_config_[name_in_task].name_in_global = name_in_global;
            return 0;
        }
    }
    return -1;
}

std::unordered_map<std::string, std::any> Task::GetOutputData() const
{
    std::unordered_map<std::string, std::any> data;
    for(auto& [name, config]: output_data_config_)
    {
        data.insert(std::make_pair(name, graph_data_manager_->GetData(config.name_in_global)));
    }
    return data;
}

int Task::SetOutDataConfig(const std::string &name_in_task, const std::string &name_in_global)
{
    if(output_data_config_.find(name_in_task) != output_data_config_.end())
    {
        if(TaskDataManager::DataTypeIsMatch(output_data_config_[name_in_task].type ,
                                            graph_data_manager_->GetDataType(name_in_global)))
        {
            output_data_config_[name_in_task].name_in_global = name_in_global;
            return 0;
        }
    }
    return -1;
}

std::string Task::GetGlobalDataName(const std::string &name_in_task)
{
    std::string  name = "";
    if(auto n = input_data_config_.find(name_in_task); n != input_data_config_.end())
    {
        name = n->second.name_in_global;
        return name;
    }
    if(auto n = output_data_config_.find(name_in_task); n != output_data_config_.end())
    {
        name = n->second.name_in_global;
        return name;
    }
    return  name;
}


