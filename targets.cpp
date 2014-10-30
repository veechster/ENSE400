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


///////////need to put this in a class.........................../////////////////////////
//function processes frame  and updates target datatype
void Tracking::processFrame(cv::Mat &imgRGB)
{
	crosshair(imgRGB,FRAME_WIDTH/2, FRAME_HEIGHT/2,"target_test");

	//create HSV image for color filtering
	cv::cvtColor(imgRGB,imgHSV,cv::COLOR_BGR2HSV);
	inRange(imgHSV,cv::Scalar(H_MIN,S_MIN,V_MIN),cv::Scalar(H_MAX,S_MAX,V_MAX),imgBIN);//creates binary threshold image

	/*
	cv::HoughCircles(imgBIN,circles,CV_HOUGH_GRADIENT,1,5);

	//input circles into targets ADT
	while(!circles.empty())
	{
		point = circles.back();
		targetList.add(point[0],point[1],"target_" + targetList.numFoundTargets());
		circles.pop_back();
	}
	*/

	//draw crosshairs on them////////////////////////////////////////////////////////////////////////////////////////////////////////


	if(debuggingmode)//DEBUGGING MODE
	{
		imshow("HSV_Image", imgHSV);
		imshow("Editted_Image", imgBIN);
	}

	cv::circle(imgRGB,cv::Point(FRAME_WIDTH/2-25,FRAME_HEIGHT/2-25),5,cv::Scalar(0,255,0),1);//laser target

	return;
}


#endif