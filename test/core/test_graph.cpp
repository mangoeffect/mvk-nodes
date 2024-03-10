
#define CATCH_CONFIG_MAIN
#include "catch2/catch_test_macros.hpp"
#include "core/graph.hpp"
#include "core/image_manager.hpp"
#include <iostream>


class TestTask: public Task
{
    //定义当前节点输入数据名称、类型
    const std::vector<std::pair<std::string, std::string>> input_defines_ =
            {
                    {"input_0", typeid(int).name()},
                    {"input_1", typeid(float).name()},
            };
    //定义当前节点输出数据名称、类型
    const std::vector<std::pair<std::string, std::string>> output_defines_ =
            {
                    {"output_0", typeid(int).name()},
                    {"output_1", typeid(float).name()},
            };

public:
    //构造函数，节点名称是必须，可扩展其他参数
    TestTask(const std::string& name);

    //初始化节点
    int InitTask() final;

    //更新节点参数
    int UpdateParams(const std::string& name, const std::any value) final;

    //执行节点任务
    int RunTask() final;

    //返回节点输入输出的定义，父类会调用
    std::vector<std::pair<std::string, std::string>> GetInputDefines() const final;
    std::vector<std::pair<std::string, std::string>> GetOutputDefines() const final;
};

TestTask::TestTask(const std::string& name) : Task(name)
{

}

int TestTask::InitTask()
{
    //param
    param_.insert(std::make_pair("int_param", std::make_any<int>(0)));
    param_.insert(std::make_pair("float_param", std::make_any<float>(0.0f)));
    param_.insert(std::make_pair("string_param", std::make_any<std::string>("defaults")));

    return 0;
}

int TestTask::UpdateParams(const std::string& name, const std::any value)
{
    if(param_.find(name) != param_.end())
    {
        param_[name] = value;
    }

    return  0;
}

std::vector<std::pair<std::string, std::string>> TestTask::GetInputDefines() const
{
    return input_defines_;
}

std::vector<std::pair<std::string, std::string>> TestTask::GetOutputDefines() const
{
    return output_defines_;
}

int TestTask::RunTask()
{
    //get input data and params
    auto input_data = GetInputData();
    for(auto& data: input_data)
    {
        if(!data.has_value()) {return  -1;}
    }
    //process
    int input0 = std::any_cast<int>(input_data[0]);
    float input1 = std::any_cast<float>(input_data[1]);
    int param0 =   std::any_cast<int>(param_["int_param"]);
    float param1 =   std::any_cast<float>(param_["float_param"]);
    auto result0 = input0 + param0;
    auto result1 = input1 + param1;

    //set output data
    output_data_[output_defines_[0].first] = result0;
    output_data_[output_defines_[1].first] = result1;

    return  0;
}


int SimpleDataTest()
{
    //task
    std::shared_ptr<Task> t1, t2, t3;
    GraphManager::Instance().CreateGraph("test");
    GraphManager::Instance().CreateTask<TestTask>("test", "t1", t1);
    GraphManager::Instance().CreateTask<TestTask>("test", "t2", t2);
    GraphManager::Instance().CreateTask<TestTask>("test", "t3", t3);


    //data
    std::vector<std::any> data = {1, 1.0f};
    GraphManager::Instance().CreateDataSource("test", "test_data", data);
    TaskDataConnect t1_data_source;
    t1_data_source.back_task_name = "t1";
    t1_data_source.front_info.emplace_back(std::make_pair("test_data", 0));
    t1_data_source.front_info.emplace_back(std::make_pair("test_data", 1));
    if(int ret = GraphManager::Instance().AddEdge("test", t1_data_source); ret != 0)
    {
        return  ret;
    }
    //test_data[1, 1.0]->t1

    //graph
    TaskDataConnect t1_t2_connect;
    t1_t2_connect.back_task_name = "t2";
    t1_t2_connect.front_info.emplace_back(std::make_pair("t1", 0));
    t1_t2_connect.front_info.emplace_back(std::make_pair("t1", 1));
    if(int ret = GraphManager::Instance().AddEdge("test", t1_t2_connect); ret != 0)
    {
        return ret;
    }
    //test_data[1, 1.0]---->t1---->t2

    TaskDataConnect t3_connect;
    t3_connect.back_task_name = "t3";
    t3_connect.front_info.emplace_back(std::make_pair("t1", 0));
    t3_connect.front_info.emplace_back(std::make_pair("t2", 1));
    if(int ret = GraphManager::Instance().AddEdge("test", t3_connect); ret != 0)
    {
        return ret;
    }

    //update parameters
    t1->UpdateParams("int_param", 1);
    t2->UpdateParams("int_param", 1);
    t3->UpdateParams("int_param", 1);
    t1->UpdateParams("float_param", 1.0f);
    t2->UpdateParams("float_param", 1.0f);
    t3->UpdateParams("float_param", 1.0f);

    //                              --->t2[3, 3.0]-->
    //                              |               |
    // test_data[1, 1.0]-t1[2, 2.0]------------------->t3[3, 4.0]


    //run
    if(int ret = GraphManager::Instance().RunAllGraph(); ret != 0)
    {
        return ret;
    }

    //                              --->t2[3, 3.0]-->
    //                              |               |
    // test_data[1, 1.0]-t1[2, 2.0]------------------->t3[3, 4.0]
    auto t1output = t1->GetOutputData();
    if(std::any_cast<int>(t1output["output_0"]) != 2
    || std::any_cast<float>(t1output["output_1"]) != 2.0)
    {
        return -1;
    }
    auto t2output = t2->GetOutputData();
    if(std::any_cast<int>(t2output["output_0"]) != 3
    || std::any_cast<float>(t2output["output_1"]) != 3.0)
    {
        return -1;
    }
    auto t3output = t3->GetOutputData();
    if(std::any_cast<int>(t3output["output_0"]) != 3
    || std::any_cast<float>(t3output["output_1"]) != 4.0)
    {
        return -1;
    }

    return 0;
}

class ImageTask: public Task
{
    const std::vector<std::pair<std::string, std::string>> input_defines_ =
            {
                    {"input_0", typeid(Image).name()},
            };

    const std::vector<std::pair<std::string, std::string>> output_defines_ =
            {
                    {"output_0", typeid(Image).name()},
            };

public:
    ImageTask(const std::string& name):
    Task(name)
    {

    }

    int InitTask() final
    {
        param_.clear();
        param_["r"] = 255;
        param_["g"] = 255;
        param_["b"] = 255;
    }

    int UpdateParams(const std::string& name, const std::any value) final
    {
        if(param_.find(name) != param_.end() && typeid(param_[name]).name() == value.type().name())
        {
            param_[name] = value;
            return 0;
        }
        return -1;
    }

    int RunTask() final
    {
        //get input data and params
        auto input_data = GetInputData();
        for(auto& data: input_data)
        {
            if(!data.has_value()) {return  -1;}
        }

        auto src_img = std::any_cast<Image>(input_data[0]);

        //process
        Image dst_img = std::any_cast<Image>(output_data_[output_defines_[0].first]);

        if(dst_img.GetSize().width != src_img.GetSize().width
        || dst_img.GetSize().height != src_img.GetSize().height
        || dst_img.Channels() != src_img.Channels())
        {
            //rebuild output
            src_img.CopyTo(dst_img);
        }

        std::uint8_t* ptr = dst_img.Ptr<std::uint8_t>(0, 0);
        for(int row = 0; row < dst_img.GetSize().height; ++row)
        {
            for(int col = 0; col < dst_img.GetSize().width; ++col)
            {
                int index = (row * dst_img.GetSize().width + col) * dst_img.Channels();
                ptr[index] = 255;
            }
        }

        //set output data
        output_data_[output_defines_[0].first] = dst_img;
        return 0;
    }

    std::vector<std::pair<std::string, std::string>> GetInputDefines() const final
    {
        return input_defines_;
    }
    std::vector<std::pair<std::string, std::string>> GetOutputDefines() const final
    {
        return output_defines_;
    }
};

int ImageTest()
{
    //task
    std::shared_ptr<Task> t1;
    std::string graph_name = "image_test";
    GraphManager::Instance().CreateGraph(graph_name);
    GraphManager::Instance().CreateTask<ImageTask>(graph_name, "t1",t1);

    //data
    std::uint8_t* data = new std::uint8_t[500*500*3]();
    Image src_img =  Image(Size(500, 500), IMAGE_TYPE::IMAGE_8UC3, data);

    GraphManager::Instance().CreateDataSource(graph_name, "src_img", {src_img});
    TaskDataConnect t1_data_source;
    t1_data_source.back_task_name = "t1";
    t1_data_source.front_info.emplace_back(std::make_pair("src_img", 0));

    if(int ret = GraphManager::Instance().AddEdge(graph_name, t1_data_source); ret != 0)
    {
        std::cout<< "test_core_graph error, AddEdge: "<< ret << std::endl;
        return -1;
    }

    if(GraphManager::Instance().RunAllGraph() != 0)
    {
        return -1;
    }

    auto output = t1->GetOutputData();
    Image dst = std::any_cast<Image>(output["output_0"]);
    if(dst.IsEmpty())
    {
        return -1;
    }
    return 0;
}

TEST_CASE("test mango-core graph", "[mango-core]")
{
    REQUIRE(SimpleDataTest() == 0);
    REQUIRE(ImageTest() == 0);
}


