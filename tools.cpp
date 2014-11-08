#ifndef TOOLS_CPP
#define TOOLS_CPP

#include "header.h"


Tools::Tools()
{
	//initalize the filtering values
	int H_MIN = 0;
	int H_MAX = 256;
	int S_MIN = 0;
	int S_MAX = 256;
	int V_MIN = 0;
	int V_MAX = 256;
	//for houghcircles debugging
	int dp = 2;
	int min_dist = 100;
	int param_1 = 100;
	int param_2 = 100 ;
	int min_radius = 0;
	int max_radius = 200;
}

//draws a crosshair cenetered at (x,y)
void Tools::crosshair(cv::Mat &frame, int x, int y, int r, cv::Vec3i colour,std::string targetName)
{
	if(y<0 || y>FRAME_HEIGHT || x<0 || x>FRAME_WIDTH){std::cout<<"error1";return;}

    cv::line(frame,cv::Point(x+15,y),cv::Point(x-15,y),cv::Scalar(colour[0],colour[1],colour[2]),2);
	cv::line(frame,cv::Point(x,y+15),cv::Point(x,y-15),cv::Scalar(colour[0],colour[1],colour[2]),2);

	if(r==0)
		cv::circle(frame, cv::Point(x,y), cvRound(r), cv::Scalar(colour[0],colour[1],colour[2]), 2);

	cv::putText(frame,targetName,cv::Point(x+2,y+12),cv::FONT_HERSHEY_SIMPLEX,0.35,cv::Scalar(200,200,200),1);
}

void Tools::enabledebugging()
{
	debuggingmode = true;
	cvStartWindowThread();
	cvNamedWindow("HSV_Image", cv::WINDOW_AUTOSIZE);
	cvNamedWindow("Editted_Image", cv::WINDOW_AUTOSIZE);
	cvNamedWindow("Adjustors",0);
    cvCreateTrackbar( "H_MIN", "Adjustors", &H_MIN, 256, 0 );
    cvCreateTrackbar( "H_MAX", "Adjustors", &H_MAX, 256, 0 );
    cvCreateTrackbar( "S_MIN", "Adjustors", &S_MIN, 256, 0 );
    cvCreateTrackbar( "S_MAX", "Adjustors", &S_MAX, 256, 0 );
    cvCreateTrackbar( "V_MIN", "Adjustors", &V_MIN, 256, 0 );
    cvCreateTrackbar( "V_MAX", "Adjustors", &V_MAX, 256, 0 );
    cvCreateTrackbar( "dp", "Adjustors", &dp, 5, 0 );
    cvCreateTrackbar( "min_dist", "Adjustors", &min_dist, 400, 0 );
    cvCreateTrackbar( "param_1", "Adjustors", &param_1, 300, 0 );
    cvCreateTrackbar( "param_2", "Adjustors", &param_2, 300, 0 );
    cvCreateTrackbar( "min_radius", "Adjustors", &min_radius, 100, 0 );
    cvCreateTrackbar( "max_radius", "Adjustors", &max_radius, 400, 0 );

}
void Tools::disabledebugging()
{
	debuggingmode = false;
	cvDestroyWindow("HSV_Image");
	cvDestroyWindow("Editted_Image");
	cvDestroyWindow("Adjustors");
}


#endif