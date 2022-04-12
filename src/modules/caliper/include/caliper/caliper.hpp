/**
 * @file caliper.hpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2021-08-25
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MVK_COMMON_CALIPER_HPP_
#define MVK_COMMON_CALIPER_HPP_

#ifndef BUILD_STATIC_LIB
    #include "mvk_caliper_export.hpp"
#endif

#include "image/image.hpp"
#include "common/rotate_rectangle.hpp"

namespace mvk
{
    class CaliperImpl;

    struct CaliperParameters
    {

    };

    struct CaliperResult
    {
        float length;
        std::vector<Point2f> extreme_points;
    };

    enum class CALIPER_MODE
    {
        SINGLE_EDGE = 0,
        DOUBLE_EDGE = 1
    };

    /**
     * @brief 卡尺工具类
     * 
     */
    class MVK_CALIPER_EXPORT Caliper
    {
    private:
        std::shared_ptr<CaliperImpl> caliper_impl_;
    public:
        Caliper(const CALIPER_MODE& mode);

        void SetInputImage(const Image& image);

        void SetROI(const RotateRect& roi);

        int Measure();

        CaliperResult GetResult() const;
    };
}//namespace mvk

#endif //MVK_COMMON_CALIPER_HPP_
