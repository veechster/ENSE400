#ifndef TARGETS_H
#define TARGETS_H

#include "header.h"

class Target
{
	//MAY HAVE TO CHANGE STORAGE TYPE TO FLOAT

	cv::Vec3i position[10];//array of last 10 positions (x,y,r) where r is radius
	int cursor;//hold the position of the NEXT place in the array of positions to be used.
	bool full;//hold whether or not position array is fully used.
	std::string name;//holds the name of the target
	long unsigned lastSeen;//last "time" the target was updated
public:
	Target(){position[0][0]=position[0][1]=position[0][2]=0;cursor=0;full=false;}
	Target(int a, int b, int r, std::string c){position[0][0]=position[0][1]=position[0][2]=0;cursor=1;name=c;lastSeen=clock.getTime();full=false;}
	void add(int a, int b, int r, long unsigned time){position[cursor][0]=a;position[cursor][1]=b;position[cursor][2]=r;cursor=(cursor+1)%10;lastSeen=time;if(cursor==0)full=true;}//adds a position to the array of past positions
	bool isTarget(int,int,int,long unsigned);
};

class Targets
{
	friend class Target;

	Target* list;//stores all current targets
	int num;//size of list
	int foundTargets;//total targets found 
	
public:
	Targets();

	void clean();
	void add(Target);
	void add(int,int,int,std::string);
	Target getTarget();
	bool removeTarget(Target);
	Target search(int,int);
	int numCurrentTargets(){return num;}//returns size of list (num)
	std::string getFoundTargets();//returns total number of found targets (x) in string form: "target x"

};

class Tracking
{
	cv::Mat imgHSV;//image in HSVS
	cv::Mat imgBIN;//image in binary threshold
	cv::vector<cv::Vec3f> circle;//temporary storage space
	Targets targetList;//list of all current targets

public:

	void processFrame(cv::Mat &);//process a frame for targets
};

#endif