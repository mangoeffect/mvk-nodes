

#ifndef FILTER_DATASOURCE_H
#define FILTER_DATASOURCE_H

#include "task.hpp"


class DataSource: public Task
{
    std::vector<std::any> data_;
    std::vector<std::pair<std::string, std::string>> GetDefines() const;
public:
    DataSource(const std::string& name);
    void SetData(const std::vector<std::any>& data, std::shared_ptr<GraphContext>& graph_context);
    int InitTask() final;
    int UpdateParams(const std::string& name, const std::any value) final;
    int RunTask() final;
    int Release() final;

    std::vector<std::pair<std::string, std::string>> GetInputDefines() const final;
    std::vector<std::pair<std::string, std::string>> GetOutputDefines() const final;
};


#endif //FILTER_DATASOURCE_H
