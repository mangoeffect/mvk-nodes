/**
 * @file caliper_defines.hpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MVK_CALIPER_DEFINES_HPP_
#define MVK_CALIPER_DEFINES_HPP_

#ifndef BUILD_STATIC_LIB
    #include "mvk_caliper_export.hpp"
#endif

#include "image/image.hpp"
#include "common/rotate_rectangle.hpp"
#include <vector>

namespace mvk
{
    /**
     * @brief 峰值点
     * 
     */
    struct Peak
    {
        Point2f p;
        float score;
    };

    /**
     * @brief 卡尺工具结果
     * 
     */
    struct CaliperResult
    {
        float length;
        std::vector<Peak> peaks;
        std::vector<float> project_curve;
    };

    /**
     * @brief 卡尺模式
     * 
     */
    enum class CALIPER_MODE
    {
        SINGLE_EDGE = 0,        ///< 单边缘模式
        DOUBLE_EDGE = 1         ///< 双边缘点模式
    };

    /**
     * @brief 评分模式
     * 
     */
    enum class GRADE_MODE
    {
        DEFAULT = 0
    };

    /**
     * @brief 灰度极性
     * 
     */
    enum class Polarity
    {
        ANY = 0,               ///< 任意
        WHITE_TO_BLACK = 1,    ///< 从白到黑
        BLACK_TO_WHITE = 2     ///< 从黑到白
    };

    /**
     * @brief 卡尺工具参数
     * 
     */
    struct CaliperParameters
    {
        Polarity polarity{Polarity::ANY};                       ///< 扫描方向极性
        CALIPER_MODE work_mode{CALIPER_MODE::SINGLE_EDGE};      ///< 工具工作模式
        GRADE_MODE grade_mode{GRADE_MODE::DEFAULT};             ///< 评分模式
        size_t filter_kernel_size{3};                           ///< 滤波核大小，奇数
    };
}//namespace mvk

#endif //MVK_CALIPER_DEFINES_HPP_