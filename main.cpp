#include "header.h"
#include "targets.h"

using namespace std;
char key;
bool debuggingmode=false;
ptime clock;

int main()
{
	//INITALIZE EVERYTHING
	cv::Mat frame;
	Tracking track;
	cvStartWindowThread();
	cvNamedWindow("Camera_Output", 1);    //Create window
	cvNamedWindow("circles", 1);/////////////////////////////////////////////////////////////////////////
	
    //CvCapture* capture = cvCaptureFromCAM(1);//capture using usb camera
	cv::VideoCapture capture;
	capture.open(1);
	
	capture.set(CV_CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);

    while(1){ //Create infinte loop for live streaming
		//set height and width of capture frame
		
		capture.read(frame);

		track.processFrame(frame);

		imshow("Camera_Output", frame);

        key = cvWaitKey(30);     //Capture Keyboard stroke
        if (char(key) == 27){
            break;      //If you hit ESC key loop will break.
        }
		if (char(key) == 100){ //debugging mode
			if(debuggingmode==false)
				enabledebugging();
			else if(debuggingmode==true)
				disabledebugging(); 
        }

		clock.tick();
    }
    cvDestroyWindow("Camera_Output"); //Destroy Window

    return 0;

}