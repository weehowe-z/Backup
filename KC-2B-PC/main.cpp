/**
 *	Entrance & Operation of Program
 *	程序入口及主要操作
 */


#include <iostream>
#include <core/core.hpp>
#include <cv.h>
#include <highgui/highgui.hpp>
#include "image.h"
#include "function.h"

using namespace std;
using namespace cv;

////////	Gloal Variable	////////

CvPoint2D32f originpoints[4];
CvPoint2D32f newpoints[4];
CvMat* transmat = cvCreateMat(3, 3, CV_32FC1);
extern bool has[];
int total_dots = 0;
CvPoint RouteDot[1000];

////////		End			////////

int main()
{

for (int i=0;i<641*481;i++)
{
    has[i]=false;
}
    CvCapture* cam = cvCreateCameraCapture(0);
    IplImage* CameraImg = NULL;

	InitCamera(cam, CameraImg);
	InitPerspectivePoints(CameraImg);

	GetCameraImage("Camera", CameraImg, cam);
	IplImage* RouteImg = cvCloneImage(CameraImg);
	GetPerspectivePoints("Camera", CameraImg);
	cvGetPerspectiveTransform(originpoints, newpoints, transmat);
	cvWarpPerspective(RouteImg, RouteImg, transmat);
	cout<<endl<<"Route Perspective READY!"<<endl;

    RouteBinaryzationThin(RouteImg);

	RgbImage RgbRoute(RouteImg);
    RouteDot[0].x=0;
    RouteDot[0].y=300;

////////////	Testing		////////////

	while(1) {
		cvShowImage("Camera", CameraImg);
		cvShowImage("Route", RouteImg);
		if(cvWaitKey(1)==KEY_ENTER) break;
	}

	for (int i=0;i<30;i++) route(RouteDot[total_dots], RgbRoute);

	display("Route", RouteImg, RgbRoute);

////////////		End		////////////

    while(1)
    {
		cvShowImage("Camera", CameraImg);
		cvShowImage("Route", RouteImg);
		if(cvWaitKey(1)==KEY_ENTER) break;
	}

	cvReleaseCapture(&cam);
	return 0;
}
