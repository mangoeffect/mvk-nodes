//
// Created by mango on 3/28/2020.
//

#include <iostream>
#include "blobdetect.h"
#include "opencv2/imgproc.hpp"
#ifdef DEBUG_BLOB_DETECTOR
#include "opencv2/highgui.hpp"
#endif

void mv::BlobDetect::Run()
{
    if(inputImage.empty())
    {
//        throw "Input image is empty.";
        CV_Error(Error::StsNullPtr, "Input image is empty!");
//        return;
    }
    this->Detect(inputImage);
}//Run

void mv::BlobDetect::SetParams(std::string name, float value)
{
    if("minThreshold" == name)
    {
        params.minThreshold = value;
    } else if("maxThreshold" == name)
    {
        params.maxThreshold = value;
    } else if("thresholdStep" == name)
    {
        params.thresholdStep = value;
    } else if("minRepeatability" == name)
    {
        params.minRepeatability = static_cast<size_t>(value);
    } else if("minDistBetweenBlobs" == name)
    {
        params.minDistBetweenBlobs = value;
    } else if("filterByColor" == name)
    {
        params.filterByColor == static_cast<bool>(value);
    } else if("filterByArea" == name)
    {
        params.filterByArea == static_cast<bool>(value);
    } else if("minArea" == name)
    {
        params.minArea = value;
    } else if("maxArea" == name)
    {
        params.maxArea = value;
    } else if("filterByCircularity" == name)
    {
        params.filterByCircularity = value;
    } else if("minCircularity" == name)
    {
        params.minCircularity = value;
    } else if("maxCircularity" == name)
    {
        params.maxCircularity = value;
    } else if("filterByInertia" == name)
    {
        params.filterByInertia = static_cast<bool>(value);
    } else if("minInertiaRatio" == name)
    {
        params.minInertiaRatio = value;
    } else if("maxInertiaRatio" == name)
    {
        params.maxInertiaRatio = value;
    } else if("filterByConvexity" == name)
    {
        params.filterByConvexity = static_cast<bool>(value);
    } else if("minConvexity" == name)
    {
        params.minConvexity = value;
    } else if("maxConvexity" == name)
    {
        params.maxConvexity = value;
    }
}//SetParams

Ptr<mv::BlobDetect> mv::BlobDetect::CreateInstance(const SimpleBlobDetector::Params &parameters)
{
    return cv::makePtr<mv::BlobDetect>(parameters);
}//CreateInstance

void mv::BlobDetect::Detect(const _InputArray &image, const _InputArray &mask)
{
    keyPoints.clear();
    CV_Assert(params.minRepeatability != 0);
    Mat grayscaleImage;
    if (image.channels() == 3 || image.channels() == 4)
        cvtColor(image, grayscaleImage, COLOR_BGR2GRAY);
    else
        grayscaleImage = image.getMat();

    if (grayscaleImage.type() != CV_8UC1) {
        CV_Error(Error::StsUnsupportedFormat, "Blob detector only supports 8-bit images!");
    }

    std::vector < std::vector<BlobInfo> > centers;

    for (double thresh = params.minThreshold; thresh < params.maxThreshold; thresh += params.thresholdStep)
    {
        Mat binarizedImage;
        threshold(grayscaleImage, binarizedImage, thresh, 255, THRESH_BINARY);

        std::vector < BlobInfo > curCenters;
        FindBlobs(grayscaleImage, binarizedImage, curCenters);
        std::vector < std::vector<BlobInfo> > newCenters;
        for (size_t i = 0; i < curCenters.size(); i++)
        {
            bool isNew = true;
            for (size_t j = 0; j < centers.size(); j++)
            {
                double dist = norm(centers[j][ centers[j].size() / 2 ].location - curCenters[i].location);
                isNew = dist >= params.minDistBetweenBlobs && dist >= centers[j][ centers[j].size() / 2 ].radius && dist >= curCenters[i].radius;
                if (!isNew)
                {
                    centers[j].push_back(curCenters[i]);

                    size_t k = centers[j].size() - 1;
                    while( k > 0 && curCenters[i].radius < centers[j][k-1].radius )
                    {
                        centers[j][k] = centers[j][k-1];
                        k--;
                    }
                    centers[j][k] = curCenters[i];

                    break;
                }
            }
            if (isNew)
                newCenters.push_back(std::vector<BlobInfo> (1, curCenters[i]));
        }
        std::copy(newCenters.begin(), newCenters.end(), std::back_inserter(centers));
    }

    // parse centers to result
    result.blobList.clear();
    for (size_t i = 0; i < centers.size(); i++)
    {
        if (centers[i].size() < params.minRepeatability)
            continue;
        Point2d sumPoint(0, 0);
        double normalizer = 0;
        for (size_t j = 0; j < centers[i].size(); j++)
        {
            sumPoint += centers[i][j].confidence * centers[i][j].location;
            normalizer += centers[i][j].confidence;
        }
        sumPoint *= (1. / normalizer);
        KeyPoint kpt(sumPoint, (float)(centers[i][centers[i].size() / 2].radius) * 2.0f);
        // parse centers to result
        BlobInfo bi = centers[i][centers[i].size() / 2];
        bi.location = sumPoint;
        result.blobList.push_back(bi);
        keyPoints.push_back(kpt);
    }

    if (!mask.empty())
    {
        KeyPointsFilter::runByPixelsMask(keyPoints, mask.getMat());
    }
}//Detect

void mv::BlobDetect::FindBlobs(const _InputArray &_image, const _InputArray &_binaryImage,
                               std::vector<BlobInfo> &centers) const
{
    Mat image = _image.getMat(), binaryImage = _binaryImage.getMat();
    CV_UNUSED(image);
    centers.clear();

    std::vector < std::vector<Point> > contours;
    findContours(binaryImage, contours, RETR_LIST, CHAIN_APPROX_NONE);

#ifdef DEBUG_BLOB_DETECTOR
    Mat keypointsImage;
cvtColor(binaryImage, keypointsImage, COLOR_GRAY2RGB);

Mat contoursImage;
cvtColor(binaryImage, contoursImage, COLOR_GRAY2RGB);
drawContours( contoursImage, contours, -1, Scalar(0,255,0) );
imshow("contours", contoursImage );
#endif

    for (size_t contourIdx = 0; contourIdx < contours.size(); contourIdx++)
    {
        BlobInfo center;
        center.confidence = 1;
        Moments moms = moments(contours[contourIdx]);
        if (params.filterByArea)
        {
            double area = moms.m00;
            if (area < params.minArea || area >= params.maxArea)
                continue;
        }

        if (params.filterByCircularity)
        {
            double area = moms.m00;
            double perimeter = arcLength(contours[contourIdx], true);
            double ratio = 4 * CV_PI * area / (perimeter * perimeter);
            if (ratio < params.minCircularity || ratio >= params.maxCircularity)
                continue;
        }

        if (params.filterByInertia)
        {
            double denominator = std::sqrt(std::pow(2 * moms.mu11, 2) + std::pow(moms.mu20 - moms.mu02, 2));
            const double eps = 1e-2;
            double ratio;
            if (denominator > eps)
            {
                double cosmin = (moms.mu20 - moms.mu02) / denominator;
                double sinmin = 2 * moms.mu11 / denominator;
                double cosmax = -cosmin;
                double sinmax = -sinmin;

                double imin = 0.5 * (moms.mu20 + moms.mu02) - 0.5 * (moms.mu20 - moms.mu02) * cosmin - moms.mu11 * sinmin;
                double imax = 0.5 * (moms.mu20 + moms.mu02) - 0.5 * (moms.mu20 - moms.mu02) * cosmax - moms.mu11 * sinmax;
                ratio = imin / imax;
            }
            else
            {
                ratio = 1;
            }

            if (ratio < params.minInertiaRatio || ratio >= params.maxInertiaRatio)
                continue;

            center.confidence = ratio * ratio;
        }

        if (params.filterByConvexity)
        {
            std::vector < Point > hull;
            convexHull(contours[contourIdx], hull);
            double area = contourArea(contours[contourIdx]);
            double hullArea = contourArea(hull);
            if (fabs(hullArea) < DBL_EPSILON)
                continue;
            double ratio = area / hullArea;
            if (ratio < params.minConvexity || ratio >= params.maxConvexity)
                continue;
        }

        if(moms.m00 == 0.0)
            continue;
        center.location = Point2d(moms.m10 / moms.m00, moms.m01 / moms.m00);

        if (params.filterByColor)
        {
            if (binaryImage.at<uchar> (cvRound(center.location.y), cvRound(center.location.x)) != params.blobColor)
                continue;
        }
        // area
        center.area = moms.m00;
        //compute blob radius
        {
            std::vector<double> dists;
            //get blob outline
            center.outline.clear();
            for (size_t pointIdx = 0; pointIdx < contours[contourIdx].size(); pointIdx++)
            {
                Point2d pt = contours[contourIdx][pointIdx];
                dists.push_back(norm(center.location - pt));
                // save blob outline
                center.outline.push_back(pt);
            }
            std::sort(dists.begin(), dists.end());
            center.radius = (dists[(dists.size() - 1) / 2] + dists[dists.size() / 2]) / 2.;
        }

        centers.push_back(center);
#ifdef DEBUG_BLOB_DETECTOR
        circle( keypointsImage, center.location, 1, Scalar(0,0,255), 1 );
#endif
    }
#ifdef DEBUG_BLOB_DETECTOR
    imshow("bk", keypointsImage );
waitKey();
#endif
}//FindBlobs


mv::BlobDetect::BlobDetect(const SimpleBlobDetector::Params &parameters): params(parameters)
{

}//BlobDetect

// Set parameters as default values
void mv::BlobDetect::SetParams()
{
//    -----------default values------------
//    thresholdStep = 10;
//    minThreshold = 50;
//    maxThreshold = 220;
//    minRepeatability = 2;
//    minDistBetweenBlobs = 10;
//
//    filterByColor = true;
//    blobColor = 0;
//
//    filterByArea = true;
//    minArea = 25;
//    maxArea = 5000;
//
//    filterByCircularity = false;
//    minCircularity = 0.8f;
//    maxCircularity = std::numeric_limits<float>::max();
//
//    filterByInertia = true;
//    //minInertiaRatio = 0.6;
//    minInertiaRatio = 0.1f;
//    maxInertiaRatio = std::numeric_limits<float>::max();
//
//    filterByConvexity = true;
//    //minConvexity = 0.8;
//    minConvexity = 0.95f;
//    maxConvexity = std::numeric_limits<float>::max();
    const SimpleBlobDetector::Params &parameters = SimpleBlobDetector::Params();
    params = parameters;
}//SetParams

void mv::BlobDetect::Init(cv::Mat &_inputImage)
{
    inputImage = _inputImage;
}//Init

void mv::BlobDetect::PrintResultInfo() const
{
    if(result.blobList.empty())
        std::cout<<"The result is empty."<<std::endl;

    std::cout<<"Blob num: "<<result.blobList.size()<<std::endl;
    int i = 0;
    for (const auto& r: result.blobList)
    {
        ++i;
        std::cout<<i
                <<": location:("<<r.location.x<<","<<r.location.y
                <<") radius: "<<r.radius
                <<" area: "<<r.area <<std::endl;
    }
}//PrintResultInfo

void mv::BlobDetect::PrintParameter() const
{
    std::cout<<"Parameter:"<<std::endl;
    std::cout<<"thresholdStep:"<<params.thresholdStep<<std::endl;
    std::cout<<"minThreshold:"<<params.minThreshold<<std::endl;
    std::cout<<"maxThreshold:"<<params.maxThreshold<<std::endl;

    std::cout<<"minDistBetweenBlobs:"<<params.minDistBetweenBlobs<<std::endl;
    std::cout<<"minRepeatability:"<<params.minRepeatability<<std::endl;


    std::cout<<"filterByConvexity:"<<params.filterByConvexity<<std::endl;
    std::cout<<"maxConvexity:"<<params.maxConvexity<<std::endl;
    std::cout<<"minConvexity:"<<params.minConvexity<<std::endl;

    std::cout<<"filterByInertia:"<<params.filterByInertia<<std::endl;
    std::cout<<"maxInertiaRatio:"<<params.maxInertiaRatio<<std::endl;
    std::cout<<"minInertiaRatio:"<<params.minInertiaRatio<<std::endl;

    std::cout<<"filterByCircularity:"<<params.filterByCircularity<<std::endl;
    std::cout<<"maxCircularity:"<<params.maxCircularity<<std::endl;
    std::cout<<"minCircularity:"<<params.minCircularity<<std::endl;

    std::cout<<"filterByArea:"<<params.filterByArea<<std::endl;
    std::cout<<"maxArea:"<<params.maxArea<<std::endl;
    std::cout<<"minArea:"<<params.minArea<<std::endl;

    std::cout<<"filterByColor:"<<params.filterByColor<<std::endl;
    std::cout<<"blobColor:"<<params.blobColor<<std::endl;
}//PrintParameter