#include <sstream>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>


//initial min and max HSV filter values.
//these will be changed using trackbars
int H_MIN = 0;
int H_MAX = 256;
int S_MIN = 0;
int S_MAX = 256;
int V_MIN = 0;
int V_MAX = 256;
//default capture width and height
const int FRAME_WIDTH = 640;
const int FRAME_HEIGHT = 480;

void createTrackbars(){
	//create window for trackbars
    cvNamedWindow("Adjustors",0);
	//create memory to store trackbar name on window

    cvCreateTrackbar( "H_MIN", "Adjustors", &H_MIN, H_MAX, 0 );
    cvCreateTrackbar( "H_MAX", "Adjustors", &H_MAX, H_MAX, 0 );
    cvCreateTrackbar( "S_MIN", "Adjustors", &S_MIN, S_MAX, 0 );
    cvCreateTrackbar( "S_MAX", "Adjustors", &S_MAX, S_MAX, 0 );
    cvCreateTrackbar( "V_MIN", "Adjustors", &V_MIN, V_MAX, 0 );
    cvCreateTrackbar( "V_MAX", "Adjustors", &V_MAX, V_MAX, 0 );
}

 
using namespace std;
char key;
int main()
{
	cv::Mat imgRGB;
	cv::Mat imgHSV;
	cv::Mat imgBIN;

	createTrackbars();

	cvNamedWindow("Camera_Output", 1);    //Create window
	cvNamedWindow("HSV_image", 1);
	cvNamedWindow("Editted_Image", 1);
    //CvCapture* capture = cvCaptureFromCAM(1);//capture using usb camera
	cv::VideoCapture capture;
	capture.open(1);
	
	capture.set(CV_CAP_PROP_FRAME_WIDTH,FRAME_WIDTH);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,FRAME_HEIGHT);

    while(1){ //Create infinte loop for live streaming
		//set height and width of capture frame
		
		capture.read(imgRGB);

		imshow("Camera_Output", imgRGB);

		cv::cvtColor(imgRGB,imgHSV,cv::COLOR_BGR2HSV);
		inRange(imgHSV,cv::Scalar(H_MIN,S_MIN,V_MIN),cv::Scalar(H_MAX,S_MAX,V_MAX),imgBIN);

		imshow("HSV_Image", imgHSV);
		imshow("Editted_Image", imgBIN);

        key = cvWaitKey(30);     //Capture Keyboard stroke
        if (char(key) == 27){
            break;      //If you hit ESC key loop will break.
        }
    }
    cvDestroyWindow("Camera_Output"); //Destroy Window
	cvDestroyWindow("HSV_Image");
	cvDestroyWindow("Editted_Image");
    return 0;

}
