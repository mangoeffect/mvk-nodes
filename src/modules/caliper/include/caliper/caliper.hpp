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

#ifndef MVK_CALIPER_HPP_
#define MVK_CALIPER_HPP_

#include "caliper/caliper_defines.hpp"


namespace mvk
{
    class CaliperImpl;
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

        void SetROI(const RotateRectf& roi);

        int Measure();

        CaliperResult GetResult() const;
    };
}//namespace mvk

#endif //MVK_CALIPER_HPP_
