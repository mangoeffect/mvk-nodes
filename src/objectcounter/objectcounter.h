#ifndef MVP_OBJECTCOUNTER_H
#define MVP_OBJECTCOUNTER_H

#include <memory>
#include <string>
#include <vector>

#include "opencv2/opencv.hpp"

namespace mvp
{
    namespace objectcounter
    {
        /**
         * @brief 物体计数工具计算结果
         */
        struct ObjectCounterResult
        {
            uint object_num;                                     ///< 物体个数
            std::vector<cv::Point_> object_locations;            ///< 物体位置
        };
        
        /**
         * @brief 物体计数工具类
         */
        class ObjectCounterTool 
        {
        private:
            ObjectCounterResult result_;                         ///< 算法处理结果
        public:
            ObjectCounterTool
            (/* args */);
            ~ObjectCounterTool
            ();
            
            /**
             * @brief 创建物体计数工具类实例
             * @return 物体计数工具类实例指针
             */
            static std::shared_ptr<ObjectCounterTool> CreateObjectCounterTool()
            {
                
            }

            /**
             * @brief 初始化函数
             * @param config_json_str(in) json格式参数配置字符串
             * @return 函数状态，负数为异常
             */
            int Init(const std::string& config_json_str);      

            /**
             * @brief 执行物体计数算法流程
             * @return 函数状态，负数为异常
             */
            int Run();      
            
            /**
             * @brief 设置算法输入图像
             * @param image(in) 输入图像
             * @return 函数状态，负数为异常
             */
            int SetInputImage(const cv::Mat& image);


        protected:
            /**
             * @brief 预处理
             * @return 函数状态，负数为异常
             */
            int PreProcess();
        };
        
        ObjectCounterTool
        ::ObjectCounterTool
        (/* args */)
        {
        }
        
        ObjectCounterTool
        ::~ObjectCounterTool
        ()
        {
        }
         
    }//namespace objectcounter
}//namespace mvp

#endif //MVP_OBJECTCOUNTER_H