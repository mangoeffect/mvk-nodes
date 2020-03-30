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
        float area;                                 //area
        std::vector<cv::Point> outline;             //outline
        float radius;                               //radius
        cv::Point location;                         //center point's coordinate
        float confidence;                           //blob detection confidence
    };//BlobInfo

    struct BlobDetectResult
    {
        std::vector<BlobInfo> blobList;
    };//BlobDetectResult

    class BlobDetect: public SimpleBlobDetector
    {
    public:
        explicit BlobDetect(const SimpleBlobDetector::Params &parameters = SimpleBlobDetector::Params());

        virtual void read( const FileNode& fn ) CV_OVERRIDE;
        virtual void write( FileStorage& fs ) const CV_OVERRIDE;

        static Ptr<BlobDetect> create(const SimpleBlobDetector::Params &parameters = SimpleBlobDetector::Params());

        // Workflow
        // 1.
        void Init(cv::Mat& inputImage);                               // input image
        // 2.
        void SetParams();                                              // default value
        void SetParams(std::string name, float value);                 // set value by param name
        // 3. detection
        // ....

        void Run();                                                    // run detection processing

        // class members for user
        cv::Mat inputImage;
        BlobDetectResult result;

    private:
        // 4.
        virtual void FindBlobs(InputArray image, InputArray binaryImage, BlobDetectResult& blobResult);
        void ParseKeyPoint();                                          // parse keypoints to result

        //
        std::vector<cv::KeyPoint> keyPoints;
        Params params;
    };//BlobDetect
}//namespace mv
#endif //MACHINE_VISION_LIBRARY_BLOBDETECT_H
