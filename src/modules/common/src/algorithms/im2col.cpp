/**
 * @file im2col.cpp
 * @author mango (2321544362@qq.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */


 namespace mvk
 {

    template<typename DataType>
    DataType Im2colGetPixel(DataType *im, int height, int width, int channels,
                            int row, int col, int channel, int pad)
    {
        row -= pad;
        col -= pad;

        if (row < 0 || col < 0 || row >= height || col >= width) return 0;
        return im[col + width*(row + height*channel)];
    }

    void Im2col(
        uint8_t* data_im,// 输入图片数量
        int channels,  // 单张图片的 通道数量
        int height,    // 图片高度
        int width,     // 宽度
        int ksize,     // 卷积核尺寸
        int stride,    // 步长
        uint8_t* data_col)// 输出 展开
    {
        int pad = 0；
        int c,h,w;

        int height_col = (height + 2*pad - ksize) / stride + 1;
        int width_col = (width + 2*pad - ksize) / stride + 1;
        int channels_col = channels * ksize * ksize;// 特征图展开  列长度 总行数

        for (c = 0; c < channels_col; ++c) 
        {
            //  caffe源码实现是一行一行来实现的
            //  下面的三个坐标表示在卷积核里面的位置。存储是一个通道，一行一行的存储。
            //  因此wide_offset是ksize的取余，h_offset是ksize(核的宽)的倍数然后对ksize（每个核的高）的取余。
            //  c_im，每个核的通道为ksize*ksize。
            int w_offset = c % ksize;
            int h_offset = (c / ksize) % ksize;
            int c_im = c / ksize / ksize;
            
            for (h = 0; h < height_col; ++h) 
            {
                for (w = 0; w < width_col; ++w) 
                {
                    int im_row = h_offset + h * stride;
                    int im_col = w_offset + w * stride;
                    int col_index = (c * height_col + h) * width_col + w;
                    data_col[col_index] = Im2colGetPixel<uint8_t>(data_im, height, width, channels, im_row, im_col, c_im, pad);
                }
            }
        }
    }
 }//namespace mvk
