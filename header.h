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

//ADD LASER POSITION ON SCREEN TO MACRO DEFINITIONS ...................................................................

/***
ADT: Ptime
Purpose: provides a way of keeping track how "long" a program has been iterating
Notes:
***/
class Ptime
{
	long unsigned count; //program loop counter
	void reset(){count=0;}//private to avoid misuse
public:
	Ptime(){count=0;}
	void tick(){count++;}
	long unsigned getTime(){return count;}
};



/***
ADT: Target
Purpose: provides a way of keeping track of a targets location and previous 10 locations 
Notes: this class will be used to keep track of an individual target and information about it
***/
//MAY HAVE TO CHANGE STORAGE TYPE TO FLOAT
//MAY HAVE TO CHANGE CLASS INTERFACES
/*
this class will develop as the program does and will eventually require a more
complicated way of keeping track of targets in the 3d AO, instead of just the frame.
*/
class Target
{
	friend class TargetList;

	cv::Vec3i position[10];//array of last 10 positions (x,y,r) where r is radius
	int cursor;//hold the position of the NEXT place in the array of positions to be used.
	bool full;//hold whether or not position array is fully used.
	std::string name;//holds the name of the target
	long unsigned lastSeen;//last "time" the target was updated
public:
	Target(){position[0][0]=position[0][1]=position[0][2]=0;cursor=0;full=false;}
	Target(int a, int b, int r,  long unsigned time,std::string c){position[0][0]=position[0][1]=position[0][2]=0;cursor=1;name=c;lastSeen=time;full=false;}
	void add(int a, int b, int r, long unsigned time){position[cursor][0]=a;position[cursor][1]=b;position[cursor][2]=r;cursor=(cursor+1)%10;lastSeen=time;if(cursor==0)full=true;}//adds a position to the array of past positions
	bool isTarget(int,int,int,long unsigned);
};



/***
ADT: TargetList
Purpose: keep track of several targets (allows differentiation between targets)
Notes:
***/
class TargetList
{
	friend class ProgramData;

	Target* list;//stores all current targets
	int num;//size of list
	int foundTargets;//total targets found 
	
public:
	TargetList();

	void clean();
	void add(Target);
	void add(int,int,int,std::string);
	Target getTarget();
	bool removeTarget(Target);
	Target search(int,int);
	int numCurrentTargets(){return num;}//returns size of list (num)
	std::string getFoundTargets();//returns total number of found targets (x) in string form: "target x"

};


/***
ADT: Tools
Purpose: helper for TargettingController, most notably, contains all the logic for debugging
Notes: any drawing and so-forth functions for ProgramData will be contained in this class
***/
class Tools
{
	friend class TargettingController;

	void createTrackbars();//for debugging - adjusting filters
	void crosshair(cv::Mat&,int,int,int,cv::Vec3i,std::string);
	void enabledebugging();//for debugging mode
	void disabledebugging();//for debugging mode

	//temporary storage variables:
	cv::Mat imgHSV;//an image in HSVS
	cv::Mat imgBIN;//an image in binary threshold
	cv::vector<cv::Vec3f> circle;//temporary storage space for a circle (x,y,r)

	//debugging/filtering variables:
	bool debuggingmode;
	int H_MIN;
	int H_MAX;
	int S_MIN;
	int S_MAX;
	int V_MIN;
	int V_MAX;
	int dp;// = 1: The inverse ratio of resolution
	int min_dist;// = src_gray.rows/8: Minimum distance between detected centers
	int param_1;//= 200: Upper threshold for the internal Canny edge detector
	int param_2;//= 1/00*: Threshold for center detection.
	int min_radius;//= 0: Minimum radio to be detected. If unknown, put zero as default.
	int max_radius;

public:
	Tools();


};



/***
ADT: TargettingController
Purpose: all of the main data and functions for the processing of frames and tracking of targets therein
Notes: 
***/
class TargettingController
{

	TargetList targets;//list of all current targets

public:
	char key;//for getting user input

	Ptime clock;//for keeping track of program time
	Tools debuggingTools;//tools to control the tracking, etc


	void processFrame(cv::Mat &);//process a frame for targets
	void killTarget();////////////////////////////////////interface incomplete..........................................

	void enabledebugging(){debuggingTools.debuggingmode=true;}
	void disabledebugging(){debuggingTools.debuggingmode=false;}
	bool debuggingModeActive(){return debuggingTools.debuggingmode;}

	TargettingController();
};


#endif