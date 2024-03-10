
#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include "task.hpp"
#include <unordered_map>
#include <vector>
#include <stack>
#include <string>

class Graph;

struct GraphContext
{
    std::shared_ptr<TaskDataManager> graph_data_manager;
    std::shared_ptr<TaskDataManager> global_data_manager;
    std::unordered_map<std::string, std::shared_ptr<Task>> task_list;
    std::shared_ptr<Graph> graph;
    std::string graph_name;
};

struct AppContext
{
    std::shared_ptr<TaskDataManager> global_data_manager;
    std::unordered_map<std::string, std::shared_ptr<GraphContext>> graph_context;
};

class Graph
{
private:
    std::string name_;
    std::unordered_map<std::string , std::vector<std::string>> adjList;
    std::vector<std::string> sorted_;
    std::unordered_map<std::string, std::shared_ptr<Task>> task_list_;
    void AddEdge(std::string u, std::string v);
    void topologicalSortUtil(std::string v, std::unordered_map<std::string , bool>& visited, std::stack<std::string>& stack);
public:
    Graph(const std::string& name);
    int AddEdge(std::shared_ptr<Task> task1, std::shared_ptr<Task> task2);
    bool HasdEdge(const std::string& front, const std::string& back);
    void topologicalSort();
    std::vector<std::string> GetTaskNames() const;
};



class GraphManager
{
private:
    std::shared_ptr<AppContext> app_context_;
    GraphManager();
    bool HavedGraph(const std::string& graph_name);
    int PushTask(const std::string& graph_name, std::shared_ptr<Task> task);
public:
    static GraphManager& Instance();
    GraphManager(const GraphManager& ) = delete;
    GraphManager& operator=(const GraphManager&) = delete;

    int CreateGraph(const std::string& graph_name);
    template <typename T>
    void CreateTask(const std::string& graph_name,const std::string& task_name, std::shared_ptr<Task>& task)
    {
        if(HavedGraph(graph_name))
        {
            task = std::make_shared<T>(task_name);
            PushTask(graph_name, task);
        }
    }

    int CreateDataSource(const std::string& graph_name, const std::string& data_name, const std::vector<std::any>& value);

    int RemoveGraph(const std::string& graph_name);
    int AddEdge(const std::string& graph_name, const TaskDataConnect& data_link);
    int AddEdge(const std::string& graph_name, std::shared_ptr<Task> front, std::shared_ptr<Task> back, const TaskDataConnect& data_link);
    int RunGraph(const std::string& graph_name);
    int RunAllGraph();
};

#endif //GRAPH_GRAPH_H
