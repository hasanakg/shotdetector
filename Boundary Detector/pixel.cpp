//
//  pixel.cpp
//  Boundary Detector
//
//  Created by Hasan Akgün on 18/05/14.
//  Copyright (c) 2014 Hasan Akgün. All rights reserved.
//

#include "pixel.h"

PixelDifference::PixelDifference(string sourcePath, int threshold)
{
    PixelDifference::threshold = threshold;
    PixelDifference::sourcePath = sourcePath;
    PixelDifference::doJob();
}

void PixelDifference::doJob()
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

bool PixelDifference::isTransition(cv::Mat first_img, cv::Mat second_img)
{
    int difPixels = 0;
    for (int i = 0; i < first_img.rows; i++)
    {
        for (int j = 0; j < first_img.cols; j++)
        {
            if(abs((int)first_img.at<uchar>(i,j)
                   - (int)second_img.at<uchar>(i,j)) >= 5)
                difPixels++;
        }
    }
    
    if(difPixels >= threshold)
        return true;
    else
        return false;
}

void PixelDifference::exportToFile()
{
    ofstream file(sourcePath + "PixelDifference.txt");

    for(int i = 0; i < transitions.size(); i++)
    {
        file << transitions[i] << endl;
    }
    
    return;
}



