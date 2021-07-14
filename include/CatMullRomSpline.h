#include <iostream>  
#include <vector>
#include <map>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
 
using namespace std;    
using namespace cv;   
 
double tj(double ti, Point2d Pi, Point2d Pj)
{
    double t = sqrt(sqrt( pow((Pj.x - Pi.x),2) + pow((Pj.y - Pi.y),2)) ) + ti;    
    return t;
}
vector<Point2d> catMullRomSpline(vector<Point2d> inputPoints)
{
    // Number of points to be added between two input points
    int numSpace = 100;
 
    int numPoints = inputPoints.size();
 
    if (numPoints > 4){
        int numSplines = numPoints - 3;
        
        std::vector<Point2d> result;
        std::vector<Point2d> spline;
        
        for (int i = 0 ; i<numSplines ; i++)
        {
            // Starting from the 0th point, take 4 points each time   
            std::vector<Point2d>::const_iterator first = inputPoints.begin() + i;
            std::vector<Point2d>::const_iterator last  = inputPoints.begin() + i+4;
            std::vector<Point2d> inputPoints_part(first, last);
 
            // At this time, the input points are 4, call the function again, and enter the else branch
            spline = catMullRomSpline(inputPoints_part);
 
            // spline is the interpolated point
            std::vector<Point2d>::const_iterator result_first = spline.begin();
            std::vector<Point2d>::const_iterator result_last  = spline.begin() + spline.size() ;
            std::vector<Point2d> result_part(result_first, result_last);
 
            // Every result spline, all put in the result result
            result.insert(result.end(), result_part.begin(), result_part.end());
        }
        // return the final result
        return result;
    }
    // When the number of input points is 4,
    else if (numPoints == 4)
    {
        // Four points entered
        Point2d P0, P1, P2, P3;
        P0.x = inputPoints[0].x;
        P0.y = inputPoints[0].y;
        P1.x = inputPoints[1].x;
        P1.y = inputPoints[1].y;
        P2.x = inputPoints[2].x;
        P2.y = inputPoints[2].y;
        P3.x = inputPoints[3].x;
        P3.y = inputPoints[3].y;
 
        double t0 = 0;
        double t1 = tj(t0, P0, P1);
        double t2 = tj(t1, P1, P2);
        double t3 = tj(t2, P2, P3);
 
        // Can be understood as the interval between points
        double linespace = (t2 - t1)/numSpace;
        
        double t = t1;
        vector<Point2d> C;
        while( t <= t2)
        {
            double A1_x = (t1-t)/(t1-t0)*P0.x + (t-t0)/(t1-t0)*P1.x;
            double A1_y = (t1-t)/(t1-t0)*P0.y + (t-t0)/(t1-t0)*P1.y;
            double A2_x = (t2-t)/(t2-t1)*P1.x + (t-t1)/(t2-t1)*P2.x;
            double A2_y = (t2-t)/(t2-t1)*P1.y + (t-t1)/(t2-t1)*P2.y;
            double A3_x = (t3-t)/(t3-t2)*P2.x + (t-t2)/(t3-t2)*P3.x;
            double A3_y = (t3-t)/(t3-t2)*P2.y + (t-t2)/(t3-t2)*P3.y;
            double B1_x = (t2-t)/(t2-t0)*A1_x + (t-t0)/(t2-t0)*A2_x;
            double B1_y = (t2-t)/(t2-t0)*A1_y + (t-t0)/(t2-t0)*A2_y;
            double B2_x = (t3-t)/(t3-t1)*A2_x + (t-t1)/(t3-t1)*A3_x;
            double B2_y = (t3-t)/(t3-t1)*A2_y + (t-t1)/(t3-t1)*A3_y;
            double C_x = (t2-t)/(t2-t1)*B1_x + (t-t1)/(t2-t1)*B2_x;
            double C_y = (t2-t)/(t2-t1)*B1_y + (t-t1)/(t2-t1)*B2_y;
            C_x = floor(C_x);
            C_y = floor(C_y);
            C.push_back(Point2d( C_x, C_y ) );
            t = t + linespace;
        }
        // C is the interpolated point between the second point and the third point of the 4 input points
        return C;
    }
    // Make sure you input more than 4 points
    else
    {
        cout<<"The Number of Input points must be greater than or equal to 4"<<endl;
        vector<Point2d> nopoint;
        nopoint.push_back(Point2d(0,0));
        return nopoint;
    }
}