//
//  edge.cpp
//  Boundary Detector
//
//  Created by Hasan Akgün on 18/05/14.
//  Copyright (c) 2014 Hasan Akgün. All rights reserved.
//

#include "edge.h"

EdgeChangeRatio::EdgeChangeRatio(string sourcePath, int threshold)
{
    EdgeChangeRatio::sourcePath = sourcePath;
    EdgeChangeRatio::threshold = threshold;
    EdgeChangeRatio::doJob();
}

void EdgeChangeRatio::doJob()
{
    for (int i = 1; i < 4600; i++)
    {
        if(i == 1893)
            i = 1893;
        if(isTransition(cv::imread(sourcePath + to_string(i) + ".jpg", CV_LOAD_IMAGE_GRAYSCALE),
                        cv::imread(sourcePath + to_string(i+1) + ".jpg", CV_LOAD_IMAGE_GRAYSCALE)))
        {
            transitions.push_back(std::to_string(i));
        }
    }
    return;
}

bool EdgeChangeRatio::isTransition(cv::Mat first_img, cv::Mat second_img)
{
    double p1, p2, ecf;
    double sum1p1 = 0;
    double sum2p1 = 0;
    double sum1p2 = 0;
    double sum2p2 = 0;
    cv::Mat dilated_first, dilated_sec;
    cv::Canny(first_img, first_img, 50.0, 200.0);
    cv::Canny(first_img, first_img, 50.0, 200.0);
    cv::dilate(first_img, dilated_first, cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3,3)));
    cv::dilate(second_img, dilated_sec, cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3,3)));
    
    for (int i = 0; i < first_img.rows; i++)
    {
        for (int j = 0; j < second_img.rows; j++)
        {
            sum1p1 += first_img.at<uchar>(i,j) * dilated_sec.at<uchar>(i,j);
            sum2p1 += first_img.at<uchar>(i,j);
            
            sum1p2 += dilated_first.at<uchar>(i,j) * second_img.at<uchar>(i,j);
        }
    }
    
    sum2p2 = sum2p1;
    
    p1 = 1.0 - (sum1p1 / sum2p1);
    p2 = 1.0 - (sum1p2 / sum2p2);
    
    ecf = p1 > p2 ? p1 : p2;
    
    if(ecf >= threshold)
        return true;
    else
        return false;
}

void EdgeChangeRatio::exportToFile()
{
    ofstream file(sourcePath + "EdgeChangeRatio.txt");
    
    for(int i = 0; i < transitions.size(); i++)
    {
        file << transitions[i] << endl;
    }
    
    return;
}