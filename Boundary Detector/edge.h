//
//  edge.h
//  Boundary Detector
//
//  Created by Hasan Akgün on 18/05/14.
//  Copyright (c) 2014 Hasan Akgün. All rights reserved.
//

#ifndef Boundary_Detector_edge_h
#define Boundary_Detector_edge_h

#include <iostream>
#include <fstream>
#include <vector>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
class EdgeChangeRatio
{
private:
    int threshold;
    string sourcePath;
    vector<string> transitions;
    bool isTransition(cv::Mat, cv::Mat);
public:
    EdgeChangeRatio(string, int);
    void doJob();
    void exportToFile();
};

#endif
