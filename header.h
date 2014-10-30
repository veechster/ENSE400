#ifndef HEADER_H
#define HEADER_H

#include <sstream>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>


//width and height of playback screen.
#define FRAME_WIDTH 640
#define FRAME_HEIGHT 480

//debugging variables
extern bool debuggingmode;
extern int H_MIN;
extern int H_MAX;
extern int S_MIN;
extern int S_MAX;
extern int V_MIN;
extern int V_MAX;

/***
ADT: time
Purpose: provides a way of keeping track how "long" a program has been iterating
***/
class ptime
{
	long unsigned count; //program loop counter
	void reset(){count=0;}//private to avoid misuse
public:
	ptime(){count=0;}
	void tick(){count++;}
	long unsigned getTime(){return count;}
};

extern ptime clock;

void createTrackbars();
extern void crosshair(cv::Mat&,int,int,std::string);
void enabledebugging();
void disabledebugging(); 

#endif