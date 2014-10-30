#ifndef HELPERS_CPP
#define HELPERS_CPP

#include "header.h"

int H_MIN = 0;
int H_MAX = 256;
int S_MIN = 0;
int S_MAX = 256;
int V_MIN = 0;
int V_MAX = 256;

//draws a crosshair cenetered at (x,y)
void crosshair(cv::Mat &frame, int x, int y,std::string targetName)
{
	if(y<0 || y>FRAME_HEIGHT || x<0 || x>FRAME_WIDTH){std::cout<<"error1";return;}

    cv::line(frame,cv::Point(x+20,y),cv::Point(x-20,y),cv::Scalar(0,0,255),1);
	cv::line(frame,cv::Point(x,y+20),cv::Point(x,y-20),cv::Scalar(0,0,255),1);

	cv::putText(frame,targetName,cv::Point(x+2,y+15),cv::FONT_HERSHEY_SIMPLEX,0.4,cv::Scalar(0,255,255),1);
}

void enabledebugging()
{
	debuggingmode = true;
	H_MIN = 0;H_MAX = 256;S_MIN = 0;S_MAX = 256;V_MIN = 0;V_MAX = 256;
	cvStartWindowThread();
	cvNamedWindow("HSV_Image", 1);
	cvNamedWindow("Editted_Image", 1);
	cvNamedWindow("Adjustors",0);
    cvCreateTrackbar( "H_MIN", "Adjustors", &H_MIN, H_MAX, 0 );
    cvCreateTrackbar( "H_MAX", "Adjustors", &H_MAX, H_MAX, 0 );
    cvCreateTrackbar( "S_MIN", "Adjustors", &S_MIN, S_MAX, 0 );
    cvCreateTrackbar( "S_MAX", "Adjustors", &S_MAX, S_MAX, 0 );
    cvCreateTrackbar( "V_MIN", "Adjustors", &V_MIN, V_MAX, 0 );
    cvCreateTrackbar( "V_MAX", "Adjustors", &V_MAX, V_MAX, 0 );
}
void disabledebugging()
{
	debuggingmode = false;
	cvDestroyWindow("HSV_Image");
	cvDestroyWindow("Editted_Image");
	cvDestroyWindow("Adjustors");
}


#endif