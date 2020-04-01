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
        cv::Point2d location;                        //center point's coordinate
        std::vector<cv::Point2d> outline;            //outline
        double area;                                 //area
        double radius;                               //radius
        double confidence;                           //blob detection confidence
    };//BlobInfo

    struct BlobDetectResult
    {
        std::vector<BlobInfo> blobList;
    };//BlobDetectResult

    class BlobDetect: protected SimpleBlobDetector
    {
    public:
        explicit BlobDetect(const SimpleBlobDetector::Params &parameters = SimpleBlobDetector::Params());

        static Ptr<BlobDetect> CreateInstance(const SimpleBlobDetector::Params &parameters = SimpleBlobDetector::Params());


        // Workflow
        // 1.
        void Init(cv::Mat& inputImage);                                // input image
        // 2.
        void SetParams();                                              // default value
        void SetParams(std::string name, float value);                 // set value by param name
        // 3. detection
        // ....

        void Run();                                                    // run detection processing

        // --------------debug---------------------------
        void PrintResultInfo() const;                                        // print result information of detection
        void PrintParameter() const;



        // class members for user
        cv::Mat inputImage;
        BlobDetectResult result;
    protected:

    private:
        void FindBlobs(InputArray image, InputArray binaryImage, std::vector<BlobInfo> &centers) const;
        void Detect( InputArray image, InputArray mask=noArray() );

        std::vector<cv::KeyPoint> keyPoints;
        Params params;
    };//BlobDetect
}//namespace mv
#endif //MACHINE_VISION_LIBRARY_BLOBDETECT_H
