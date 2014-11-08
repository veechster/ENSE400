#include "header.h"




int main()
{
	cv::Mat frame;//holds a frame from camera
	TargettingController controller;

	cvStartWindowThread();
	cvNamedWindow("Camera_Output", cv::WINDOW_AUTOSIZE);//Create window
	
	cv::VideoCapture capture;
	capture.open(1);//capture using usb camera (not default)
	
	capture.set(CV_CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);//set height and width of capture frame
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);

    while(1)//Create infinte loop for live streaming
	{ 
		capture.read(frame);//get a frame

		controller.processFrame(frame);//process the frame looking for targets

		imshow("Camera_Output", frame);

        controller.key = cvWaitKey(30);//Capture Keyboard stroke
        if (char(controller.key) == 27)
            break;//If you hit ESC key loop will break.
		else if (char(controller.key) == 100)//enable debugging mode
		{ 
			if(!controller.debuggingModeActive())
				controller.enabledebugging();
			else
				controller.disabledebugging(); 
        }

		controller.clock.tick();
    }
    cvDestroyWindow("Camera_Output"); //Destroy Window

    return 0;

}