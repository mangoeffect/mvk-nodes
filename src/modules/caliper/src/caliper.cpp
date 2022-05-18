/**
 * @file caliper.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "caliper/caliper.hpp"
#include "caliper/caliper_impl.hpp"

namespace mvk
{
    Caliper::Caliper(const CALIPER_MODE& mode)
    : caliper_impl_(new CaliperImpl(mode))
    {

    }

    void Caliper::SetInputImage(const Image& image)
    {
        caliper_impl_->SetInputImage(image);
    }   

    void Caliper::SetROI(const RotateRectf& roi)
    {
        caliper_impl_->SetROI(roi);
    }

    int Caliper::Measure()
    {
        return caliper_impl_->Measure();
    }

    CaliperResult Caliper::GetResult() const
    {
        return caliper_impl_->GetResult();
    }
}//namespace mvk
