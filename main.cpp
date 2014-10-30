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


/*

HOUGH CIRCLES EXAMPLE CODE FROM OPENCV

#include <cv.h>
#include <highgui.h>
#include <math.h>

using namespace cv;

int main(int argc, char** argv)
{
    Mat img, gray;
    if( argc != 2 && !(img=imread(argv[1], 1)).data)
        return -1;
    cvtColor(img, gray, CV_BGR2GRAY);
    // smooth it, otherwise a lot of false circles may be detected
    GaussianBlur( gray, gray, Size(9, 9), 2, 2 );
    vector<Vec3f> circles;
    HoughCircles(gray, circles, CV_HOUGH_GRADIENT,
                 2, gray->rows/4, 200, 100 );
    for( size_t i = 0; i < circles.size(); i++ )
    {
         Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
         int radius = cvRound(circles[i][2]);
         // draw the circle center
         circle( img, center, 3, Scalar(0,255,0), -1, 8, 0 );
         // draw the circle outline
         circle( img, center, radius, Scalar(0,0,255), 3, 8, 0 );
    }
    namedWindow( "circles", 1 );
    imshow( "circles", img );
    return 0;
}

*/