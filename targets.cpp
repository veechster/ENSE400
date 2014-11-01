#ifndef TARGETS_CPP
#define TARGETS_CPP

#include "targets.h"

Targets::Targets(){}
void Targets::clean(){}
void Targets::add(Target){}
void Targets::add(int,int,std::string){}
Target Targets::getTarget(){return Target();}
bool Targets::removeTarget(Target){return 0;}
Target Targets::search(int,int){return Target();}
int Targets::numFoundTargets(){return 0;}


//function processes frame and updates target datatype
void Tracking::processFrame(cv::Mat &imgRGB)
{
	crosshair(imgRGB,FRAME_WIDTH/2, FRAME_HEIGHT/2,"target_test");

	//create HSV image for color filtering
	cv::cvtColor(imgRGB,imgHSV,cv::COLOR_BGR2HSV);
	//inRange(imgHSV,cv::Scalar(H_MIN,S_MIN,V_MIN),cv::Scalar(H_MAX,S_MAX,V_MAX),imgBIN);//creates binary threshold image
	inRange(imgHSV,cv::Scalar(10,40,180),cv::Scalar(60,210,256),imgBIN);//yellow with moderate tolerance
	//ABOVE LINE IS FOR DEBUGGING//////////////////////////////////////////////////////////////////////////////////////////////////////////

	//cv::cvtColor(imgRGB, imgHSV, CV_BGR2GRAY );//////////////////////////////////////////////////////////////////////////////////////////
	cv::GaussianBlur( imgBIN, imgBIN, cv::Size(13, 13), 2, 2 );
	HoughCircles(imgBIN, circles, CV_HOUGH_GRADIENT, 2, 100, 80, 110, 0, 0 );

	for( size_t i = 0; i < circles.size(); i++ )
    {
		//ADD TARGETS TO TARGET CONTAINER/////////////////////////////////////////////////////////////////////////////////////////////////
		//SMOOTH OUT CROSSHAIR POSITION (BOUNCING)

		crosshair(imgRGB,cvRound(circles[i][0]), cvRound(circles[i][1]), "target");

    }

	for( size_t i = 0; i < circles.size(); i++ )
		circles.pop_back();

	if(debuggingmode)//DEBUGGING MODE
	{
		imshow("HSV_Image", imgHSV);
		imshow("Editted_Image", imgBIN);
	}

	cv::circle(imgRGB,cv::Point(FRAME_WIDTH/2-25,FRAME_HEIGHT/2-25),5,cv::Scalar(0,255,0),1);//laser target

	return;
}


#endif