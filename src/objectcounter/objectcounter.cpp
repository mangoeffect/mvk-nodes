
#include "objectcounter.h"

namespace mvp
{
        ObjectCounterTool::ObjectCounterTool(/* args */)
        {
        }
        
        ObjectCounterTool::~ObjectCounterTool()
        {
        }

        static std::shared_ptr<ObjectCounterTool> ObjectCounterTool::CreateObjectCounterTool()
        {

        }


        int ObjectCounterTool::Init(const std::string& config_json_str)
        {
                return 0;
        } 


        int ObjectCounterTool::Run()
        {
                return 0;
        }     
        

        int ObjectCounterTool::SetInputImage(const cv::Mat& image)
        {
                return 0;
        }

        int ObjectCounterTool::PreProcess()
        {
                return 0;
        }
}//namespace mvp
