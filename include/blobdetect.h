//
// Created by mango on 3/28/2020.
//

#ifndef MACHINE_VISION_LIBRARY_BLOBDETECT_H
#define MACHINE_VISION_LIBRARY_BLOBDETECT_H

#include "opencv2/features2d.hpp"

using namespace cv;
namespace mv
{
    // Single blob info
    struct BlobInfo
    {
    public:
        float area;                                 //面积
        std::vector<cv::Point> outline;             //轮廓
        float radius;                               //质心半径
        cv::Point center;                           //质心坐标
    };//BlobInfo

    struct BlobDetectResult
    {
        std::vector<BlobInfo> bloblist;
    };//BlobDetectResult

    class BlobDetect: public SimpleBlobDetector
    {
    public:
        explicit BlobDetect(const SimpleBlobDetector::Params &parameters = SimpleBlobDetector::Params());

        virtual void read( const FileNode& fn ) CV_OVERRIDE;
        virtual void write( FileStorage& fs ) const CV_OVERRIDE;

        static Ptr<BlobDetect> create(const SimpleBlobDetector::Params &parameters = SimpleBlobDetector::Params());

    private:
        BlobDetectResult result;
        std::vector<cv::KeyPoint> keypoints;
        Params params;
    };//BlobDetect
}//namespace mv
#endif //MACHINE_VISION_LIBRARY_BLOBDETECT_H
