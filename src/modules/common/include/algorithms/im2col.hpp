/**
 * @file im2col.hpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef MVK_COMMON_ALGORITHMS_IM2COL_HPP_
#define MVK_COMMON_ALGORITHMS_IM2COL_HPP_

namespace mvk
{
    /**
     * @brief 卷积转矩阵相乘展开步骤
     * 
     * @param data_im(in) 输入图像 
     * @param channels(in) 图片通道数量 
     * @param height(in) 图片高度 
     * @param width(in) 图片宽度 
     * @param ksize(in) 卷积核尺寸 
     * @param stride(in) 卷积核移动步长 
     * @param data_col 
     */
    void Im2col(
        uint8_t* data_im,
        int channels,  
        int height,    
        int width,     
        int ksize,     
        int stride,    
        uint8_t* data_col);
}//namespace mvk

#endif //MVK_COMMON_ALGORITHMS_IM2COL_HPP_
