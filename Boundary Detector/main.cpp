//
//  main.cpp
//  Boundary Detector
//
//  Created by Hasan Akgün on 18/05/14.
//  Copyright (c) 2014 Hasan Akgün. All rights reserved.
//

#include <iostream>
#include "pixel.h"

using namespace std;
using namespace cv;

int main(int argc, const char * argv[])
{
    PixelDifference pixelDif("/Users/hasanakg/Downloads/video_seq/", 50170);
    pixelDif.exportToFile();
    
    return 0;
}
