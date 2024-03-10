
#include "graph.hpp"
#include "data_source.hpp"
#include <iostream>

Graph::Graph(const std::string &name): name_(name)
{

}

void Graph::AddEdge(std::string u, std::string v)
{
    adjList[u].push_back(v);
}

void Graph::topologicalSortUtil(std::string v, std::unordered_map<std::string , bool>& visited, std::stack<std::string>& stack)
{
    visited[v] = true;

    for (auto i : adjList[v])
    {
        if (!visited[i])
        {
            topologicalSortUtil(i, visited, stack);
        }
    }
    stack.push(v);
}

void Graph::topologicalSort()
{
    std::unordered_map<std::string , bool> visited;
    std::stack<std::string> stack;

    // Initialize all vertices as not visited
    for (auto& pair : adjList)
    {
        visited[pair.first] = false;
    }

    for (auto& pair : adjList)
    {
        auto vertex = pair.first;
        if (!visited[vertex]) {
            topologicalSortUtil(vertex, visited, stack);
        }
    }

    // Print contents of the stack
    sorted_.clear();
    while (!stack.empty())
    {
        sorted_.push_back(stack.top());
        stack.pop();
    }
    std::cout << "---------------\n sort: ";
    for(auto& s: sorted_)
    {
        std::cout << s << " ";
    }
    std::cout << "\n";
}

int Graph::AddEdge(std::shared_ptr<Task> task1, std::shared_ptr<Task> task2)
{
    AddEdge(task1->GetName(), task2->GetName());
    topologicalSort();
    return 0;
}

bool Graph::HasdEdge(const std::string &front, const std::string &back)
{
    if(adjList.find(front) != adjList.end())
    {
        return std::find(adjList[front].begin(), adjList[front].end(), back) != adjList[front].end();
    }
    return false;
}

std::vector<std::string> Graph::GetTaskNames() const
{
    return sorted_;
}

GraphManager::GraphManager()
{
    app_context_ = std::make_shared<AppContext>();
    app_context_->global_data_manager = std::make_shared<TaskDataManager>("glabal", std::make_shared<ImageManager>());
}

GraphManager& GraphManager::Instance()
{
    static GraphManager manager;
    return manager;
}

bool GraphManager::HavedGraph(const std::string &graph_name)
{
    if(app_context_ != nullptr)
    {
        return app_context_->graph_context.find(graph_name) != app_context_->graph_context.end();
    }
    return false;
}

int GraphManager::CreateGraph(const std::string& graph_name)
{
    if(!HavedGraph(graph_name))
    {
        app_context_->graph_context[graph_name] = std::make_shared<GraphContext>();
        app_context_->graph_context[graph_name]->graph_name = graph_name;
        app_context_->graph_context[graph_name]->graph = std::make_shared<Graph>(graph_name);
        app_context_->graph_context[graph_name]->global_data_manager = app_context_->global_data_manager;
        app_context_->graph_context[graph_name]->graph_data_manager = std::make_shared<TaskDataManager>(graph_name, std::make_shared<ImageManager>());
        return 0;
    }
    return -1;
}

int GraphManager::PushTask(const std::string &graph_name, std::shared_ptr<Task> task)
{
    if(HavedGraph(graph_name))
    {
        app_context_->graph_context[graph_name]->task_list[task->GetName()] = task;
        task->Init(app_context_->graph_context[graph_name]);
    }
}

int GraphManager::CreateDataSource(const std::string &graph_name,const std::string &data_name, const std::vector<std::any> &value)
{
    if(HavedGraph(graph_name))
    {
        auto datasource = std::make_shared<DataSource>(data_name);
        if(datasource != nullptr)
        {
            datasource->SetData(value, app_context_->graph_context[graph_name]);
            PushTask(graph_name, datasource);
            return 0;
        }
    }
    return -1;
}

int GraphManager::RemoveGraph(const std::string& graph_name)
{
    if(HavedGraph(graph_name))
    {
        for(auto& task: app_context_->graph_context[graph_name]->task_list)
        {
            task.second->Release();
        }

        app_context_->graph_context[graph_name]->graph_data_manager->ClearData();
        auto g = app_context_->graph_context.find(graph_name);
        app_context_->graph_context.erase(g);
    }
    return 0;
}

int GraphManager::AddEdge(const std::string &graph_name, const TaskDataConnect &data_link)
{
    //1. check whether the task exists.
    if(!HavedGraph(graph_name)){return -1;}

    auto& task_list = app_context_->graph_context[graph_name]->task_list;
    if(task_list.find(data_link.back_task_name) == task_list.end()) {return  -1;}
    for(auto& [name, index]: data_link.front_info)
    {
        if(task_list.find(name) == task_list.end()) {return -1;}
    }

    //2. check the connected data type
    auto& back_task = task_list[data_link.back_task_name];
    if(back_task->GetInputDefines().size() != data_link.front_info.size())
    {
        return  -1;
    }

    for(int i = 0; i < data_link.front_info.size(); ++i)
    {
        int back_task_input_index = i;
        int front_task_output_index = data_link.front_info[i].second;
        std::string front_task_name = data_link.front_info[i].first;
        auto& front_task = task_list[front_task_name];
        auto front_type = front_task->GetOutputDefines()[front_task_output_index].second;
        auto back_type = back_task->GetInputDefines()[back_task_input_index].second;
        if(front_type != back_type) {return -1;}
    }

    //3. add edge
    auto back_task_input_defines = back_task->GetInputDefines();
    for(int i = 0; i < data_link.front_info.size(); ++i)
    {
        std::string front_task_name = data_link.front_info[i].first;
        auto& front_task = task_list[front_task_name];
        //3.1 connect data
        auto front_output_name = front_task->GetOutputDefines()[data_link.front_info[i].second].first;
        auto ret = back_task->SetInputDataConfig(back_task_input_defines[i].first,front_task->GetGlobalDataName(front_output_name));
        if(ret != 0){return ret;}

        auto& graph = app_context_->graph_context[graph_name]->graph;
        if(!graph->HasdEdge(front_task_name, data_link.back_task_name))
        {
            //3.2 add edge
            graph->AddEdge(front_task, back_task);
        }
    }

    return 0;
}

int GraphManager::AddEdge(
        const std::string& graph_name, std::shared_ptr<Task> front,
        std::shared_ptr<Task> back,
        const TaskDataConnect& data_link)
{
    if(HavedGraph(graph_name))
    {
        //check data link is valid
        auto& task_list = app_context_->graph_context[graph_name]->task_list;
        task_list[front->GetName()] = front;
        task_list[back->GetName()] = back;
        if(Task::CheckLinkValid(graph_name,task_list, data_link))
        {
            app_context_->graph_context[graph_name]->graph->AddEdge(front, back);
        }else
        {
            return -1;
        }
    }
    return 0;
}

int GraphManager::RunGraph(const std::string& graph_name)
{
    if(HavedGraph(graph_name))
    {
        for(auto& current_name: app_context_->graph_context[graph_name]->graph->GetTaskNames())
        {
            auto& task = app_context_->graph_context[graph_name]->task_list[current_name];
            if(int ret = task->Run(app_context_->graph_context[graph_name]); ret != 0)
            {
                return  ret;
            }
        }
    }
    return 0;
}

int GraphManager::RunAllGraph()
{
    for(auto& [name,graph]: app_context_->graph_context)
    {
        if(graph != nullptr)
        {
            RunGraph(name);
        }
    }
    return 0;
}
