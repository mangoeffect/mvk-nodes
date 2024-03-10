
#include "data_source.hpp"
#include "graph.hpp"

DataSource::DataSource(const std::string &name)
: Task(name)
{

}

void DataSource::SetData(const std::vector<std::any> &data, std::shared_ptr<GraphContext>& graph_context)
{
    data_ = data;
    for(int i = 0; i < data_.size(); ++i)
    {
        //auto name_in_manager = name_ + "_input_" + std::to_string(i);
        //graph_context->graph_data_manager->CreateData(name_in_manager, data_[i]);
    }
}

int DataSource::InitTask()
{
    return 0;
}

std::vector<std::pair<std::string, std::string>> DataSource::GetDefines() const
{
    std::vector<std::pair<std::string, std::string>> defines(data_.size());
    for(int i = 0; i < data_.size(); ++i)
    {
        defines[i].first = "input_" + std::to_string(i);//name;
        defines[i].second =  data_[i].type().name();//type;
    }
    return defines;
}

std::vector<std::pair<std::string, std::string>> DataSource::GetInputDefines() const
{
    return {};//no input config
}

std::vector<std::pair<std::string, std::string>> DataSource::GetOutputDefines() const
{
    return GetDefines();
}

int DataSource::RunTask()
{
    for(int i = 0; i < data_.size(); ++i)
    {
        output_data_[GetDefines()[i].first] = data_[i];
        if(data_[i].has_value() && data_[i].type().name() == typeid(Image).name())
        {
            auto img  = std::any_cast<Image>(data_[i]);
        }
    }
}

int DataSource::UpdateParams(const std::string &name, const std::any value)
{
    return 0;
}

int DataSource::Release()
{
    data_.clear();
    return 0;
}
