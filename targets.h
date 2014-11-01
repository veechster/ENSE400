#ifndef TARGETS_H
#define TARGETS_H

#include "header.h"

class Target
{
	int x,y;
	std::string name;
	long unsigned lastSeen;
public:
	Target(){x=y=0;}
	Target(int a, int b, std::string c){x=a,y=b,name=c;lastSeen=clock.getTime();}
};

class Targets
{
	friend class Target;

	Target* list;
	int num;
	int foundTargets;
	
public:
	Targets();

	void clean();
	void add(Target);
	void add(int,int,std::string);
	Target getTarget();
	bool removeTarget(Target);
	Target search(int,int);
	int numFoundTargets();

};

class Tracking
{
	cv::Mat imgHSV;
	cv::Mat imgBIN;
	cv::vector<cv::Vec3f> circles;//////////////needs 3 points
	cv::Vec3f point;/////////////////////fix this///////////////////////////////////////////////////
	cv::Point center;
	int radius;
	Targets targetList;

public:

	void processFrame(cv::Mat &);
};

#endif