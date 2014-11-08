#ifndef TARGETS_CPP
#define TARGETS_CPP

#include "header.h"

TargettingController::TargettingController(){}
void TargettingController::killTarget(){}


TargetList::TargetList(){}
void TargetList::clean(){}
void TargetList::add(Target){}
void TargetList::add(int,int,int,std::string){}
Target TargetList::getTarget(){return Target();}
bool TargetList::removeTarget(Target){return 0;}
Target TargetList::search(int,int){return Target();}
std::string TargetList::getFoundTargets(){return "0";}

//function looks for the current position relative to the past poitions.
//if it is a position of this target, it is atomatically added
bool Target::isTarget(int a, int b, int r,long unsigned time)
{
	if(cursor==0 && full==false)
		return false;//no previous position stored

	if(a<=position[cursor][0]+10 && a>=position[cursor][0]-10 && b<=position[cursor][1]+10 && b>=position[cursor][1]-10 && r<=position[cursor][2]+5 && r>=position[cursor][2]-5)//this algorithm requires refinement -- look for previous positions, patterns, but keep execution time very fast.
	{
		add(a,b,r,time);	
		return true;	
	}

	return 0;
}



//function processes frame and updates target datatype
void TargettingController::processFrame(cv::Mat &imgRGB)
{
	debuggingTools.crosshair(imgRGB,FRAME_WIDTH/2, FRAME_HEIGHT/2,0,cv::Vec3i(100,100,100),"center");

	//create HSV image for color filtering
	cv::cvtColor(imgRGB,debuggingTools.imgHSV,cv::COLOR_BGR2HSV);
	inRange(debuggingTools.imgHSV,cv::Scalar(debuggingTools.H_MIN,debuggingTools.S_MIN,debuggingTools.V_MIN),cv::Scalar(debuggingTools.H_MAX,debuggingTools.S_MAX,debuggingTools.V_MAX),debuggingTools.imgBIN);//creates binary threshold image

	//blur image so HoughCircles argorithm doesnt shit itself
	cv::GaussianBlur(debuggingTools.imgBIN, debuggingTools.imgBIN, cv::Size(13, 13), 2, 2 );
	if(!debuggingModeActive())
		HoughCircles(debuggingTools.imgBIN, this->debuggingTools.circle, CV_HOUGH_GRADIENT, debuggingTools.dp, debuggingTools.min_dist, debuggingTools.param_1, debuggingTools.param_2, debuggingTools.min_radius, debuggingTools.max_radius );//if HoughCircles is running while tuning, it shits itself


	/*
	//TEMPORARY CODE FOR DEMO
	for( size_t i = 0; i < circle.size(); i++ )
    {
		crosshair(imgRGB,cvRound(circle[i][0]), cvRound(circle[i][1]), "target");
		cv::circle(imgRGB, cv::Point(cvRound(circle[i][0]), cvRound(circle[i][1])), cvRound(circle[i][2]), cv::Scalar(0,255,255), 2);
    }

	for( size_t i = 0; i < circle.size(); i++ )
		circle.pop_back();
	//END OF DEMO SNIPPET
	*/


	/*CODE FOR ADDING TARGETS TO ADT
	for( size_t i = 0; i < circle.size(); i++ )
    {
		//add to adt
		this->targetList.add(cvRound(circle.back()[0]),cvRound(circle.back()[1]),cvRound(circle.back()[2]),this->targetList.getFoundTargets());
		circle.pop_back();

		std::cout<<"Target "<<this->targetList.getFoundTargets()<<"Aquired.\n";//outputing may require too much time.
	

		//clear old targets here?
	}

	for(int i = this->targetList.numCurrentTargets();i>0;i--)/////////////////////////////////////////////////////////////////////////////////////////////DEMO//////////////////////////////////////////
	{
		//smooth out target "bouncing"

		//draw crosshair on target
		crosshair(imgRGB,cvRound(circle[i][0]), cvRound(circle[i][1]), "target");        
		
		//draw circle of radius around target
        cv::circle(imgRGB, cv::Point(cvRound(circle[i][0]), cvRound(circle[i][1])), cvRound(circle[i][2]), cv::Scalar(0,255,255), 2);

	}
	*/
		

	if(debuggingModeActive())//DEBUGGING MODE
	{
		imshow("HSV_Image", debuggingTools.imgHSV);
		imshow("Editted_Image", debuggingTools.imgBIN);
	}

	//DRAW LASER TARGET ON SCREEN
	cv::circle(imgRGB,cv::Point(FRAME_WIDTH/2-25,FRAME_HEIGHT/2-25),5,cv::Scalar(0,255,0),1);//(where the laser is aimed)
	
	return;
}


#endif