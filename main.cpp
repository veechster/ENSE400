#include "header.h"
#include "targets.h"


char key;
bool debuggingmode=false;
ptime clock;

int main()
{
	cv::Mat frame;//holds a frame from camera
	Tracking track;//Used for tracking targets

	cvStartWindowThread();
	cvNamedWindow("Camera_Output", 1);//Create window
	
	cv::VideoCapture capture;
	capture.open(1);//capture using usb camera
	
	capture.set(CV_CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);

    while(1){ //Create infinte loop for live streaming
		//set height and width of capture frame
		
		capture.read(frame);//get a frame

		track.processFrame(frame);//process the frame looking for targets

		imshow("Camera_Output", frame);

        key = cvWaitKey(30);     //Capture Keyboard stroke
        if (char(key) == 27){
            break;      //If you hit ESC key loop will break.
        }
		if (char(key) == 100){ //debugging mode
			if(!debuggingmode)
				enabledebugging();
			else if(debuggingmode)
				disabledebugging(); 
        }

		clock.tick();
    }
    cvDestroyWindow("Camera_Output"); //Destroy Window

    return 0;

}