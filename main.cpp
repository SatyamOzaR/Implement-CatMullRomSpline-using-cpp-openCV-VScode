#include <iostream>  
#include <vector>
#include <map>
#include <math.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
 
#include "CatMullRomSpline.h"
 
using namespace std;    
using namespace cv;   
 
int main(int argc, char*argv[])  
{    
    vector<Point2d> input;
    //input.push_back(Point2d(-510, -520));
    input.push_back(Point2d(50,50));
    input.push_back(Point2d(300,250));
    input.push_back(Point2d(550,200));
    input.push_back(Point2d(800,600));
    //input.push_back(Point2d(900,900));
 
    // Call the algorithm
    vector<Point2d> Output = catMullRomSpline(input);
         cout<<"Total Number of Interpolated Points : "<<Output.size()<<" points"<<endl;
 
    // draw it
    // defining image of type CV_8UC3 with white background
    Mat img(2000, 2000, CV_8UC3, Scalar(255, 255, 255));

    // mark discrete points with red color
    for (int i = 0 ; i< input.size(); i++)
    {
        int x = 1000 + input[i].x ;
        int y = 1000 - input[i].y ;
        circle(img, Point2d(x, y),1, Scalar(0, 0, 255), 15, 8, 2);
    }

    // mark continuos interpolated path with green color
    for (int i = 0 ; i< Output.size(); i++)
    {
        int x = 1000 + Output[i].x ;
        int y = 1000 - Output[i].y ;
        circle(img, Point2d(x, y),1, Scalar(0, 255, 0), 8, 8, 2);
    }

    // output the final image
    imshow("Output", img);
    waitKey(0);
 
	return 0;
}