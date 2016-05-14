/**
 *	Definition of Funtion
 *	函数定义
 */


#include <iostream>
#include <core/core.hpp>
#include <cv.h>
#include <highgui/highgui.hpp>
#include "image.h"
#include "function.h"

using namespace std;
using namespace cv;


void InitCamera(CvCapture* cam, IplImage*& img)
{
	cout<<"Initializing camera, please wait..."<<endl;

    if(!cam) {
		cout<<"Error occurs while opening the camera."<<endl;
		return;
    }

    if(img) {
		cout<<"The Pointer \"img\" is not NULL."<<endl;
		return;
    }

	while(!img)
		img = cvQueryFrame(cam);
}


void InitPerspectivePoints(const IplImage* img)
{
	extern CvPoint2D32f originpoints[4];
	extern CvPoint2D32f newpoints[4];

	cout<<"Setting up the size of camera..."<<endl;

	int wid=img->width, len=img->height;

	originpoints[0] = cvPoint2D32f(0,0);
    originpoints[1] = cvPoint2D32f(wid,0);
    originpoints[2] = cvPoint2D32f(0,len);
    originpoints[3] = cvPoint2D32f(wid,len);

    newpoints[0] = cvPoint2D32f(0,0);
    newpoints[1] = cvPoint2D32f(wid,0);
    newpoints[2] = cvPoint2D32f(0,len);
    newpoints[3] = cvPoint2D32f(wid,len);
}


void on_mouse(int mouseevent, int x, int y, int flags, void* param)
{
	extern CvPoint2D32f originpoints[4];

	MouseEvent* event = (MouseEvent*)param;
	switch(mouseevent)
	{
	case CV_EVENT_RBUTTONDOWN:
		cout<<"Right Button Down. ";
		if(event->event==SET_PERSPECTIVE && event->counter<4) {
			cout<<"Set OriginPoint["<<event->counter<<"] "<<x<<","<<y;
			originpoints[event->counter].x = x;
			originpoints[event->counter].y = y;
			++event->counter;
		}
		cout<<endl;
		break;
	}
}


void VOID_mouse(int mouseevent, int x, int y, int flags, void* param) { /*Do Nothing*/}


void DrawPerspectivePoints(IplImage*& img)
{
	extern CvPoint2D32f originpoints[4];

	for(int i=0; i<4; ++i)
		cvDrawCircle(img, cvPointFrom32f(originpoints[i]), 4, CV_RGB(255,0,0), 2);
}


void GetCameraImage(const char* winName, IplImage*& img, CvCapture* cam)
{
	cout<<endl<<"Now start getting the image. Press \"Enter\" when appropriate."<<endl;
	while(1) {
		img = cvQueryFrame(cam);
		cvShowImage(winName, img);
		if(cvWaitKey(1)==KEY_ENTER) { cout<<"Enter PRESSED."<<endl; break; }
	}
	////////	test	////////
	 img = cvLoadImage("test.jpg");
	////////	end 	////////
	cout<<"Image got! Size: "<<img->width<<" X "<<img->height<<endl;
}


void GetPerspectivePoints(const char* winName, IplImage*& img)
{
	cout<<endl<<"Set Perspective. Right Click the 4 points of the route's border. Enter ends."<<endl;
	MouseEvent ME(0, SET_PERSPECTIVE);
	cvSetMouseCallback(winName, on_mouse, (void*)(&ME));
	while(1) {
		DrawPerspectivePoints(img);
		cvShowImage(winName, img);
		if(cvWaitKey(1)==KEY_ENTER) { cout<<"Enter PRESSED."<<endl; break; }
		/////	Here, instructor can be implemented to help users to RESET the perspective points.
	}
	cvSetMouseCallback(winName, VOID_mouse);
}


void RouteBinaryzationThin(IplImage*& img)
{
	IplImage* tmp=cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
	cvCvtColor(img, tmp, CV_RGB2GRAY);
	cvReleaseImage(&img);
	img = cvCreateImage(cvGetSize(tmp), IPL_DEPTH_8U, 1);
    cvAdaptiveThreshold(tmp, img, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, 85);
	cout<<"Route Binaryzation READY!"<<endl;

	cvErode(img, tmp, NULL, 2);
	cvDilate(tmp, img, NULL, 2);
	cvErode(img, tmp, NULL, 2);
	cvDilate(tmp, img, NULL, 2);
	cvErode(img, tmp, NULL, 8);

	cvThin(tmp, img, 32);
	cvReleaseImage(&tmp);
	tmp = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	cvCvtColor(img, tmp, CV_GRAY2RGB);
	cvReleaseImage(&img);
	img = cvCreateImage(cvGetSize(tmp), IPL_DEPTH_8U, 3);
	cvCopyImage(tmp, img);
	cvReleaseImage(&tmp);
	cout<<"Route cvThin READY!"<<endl;
}

void cvThin(IplImage* src, IplImage* dst, int iterations)
{
    cvCopyImage(src, dst);
    BwImage dstdat(dst);
    IplImage* t_image = cvCloneImage(src);
    BwImage t_dat(t_image);
    for(int n=0; n<iterations; ++n)
		for(int s=0; s<=1; ++s) {
			cvCopyImage(dst, t_image);
			for(int i=0; i<src->height; ++i)
				for(int j=0; j<src->width; ++j)
					if(t_dat[i][j]) {
						int a=0, b=0;
						int d[8][2] = {{-1,0}, {-1, 1}, {0, 1}, {1, 1},{1, 0}, {1, -1}, {0, -1}, {-1, -1}};
						int p[8];
						p[0] = (i == 0) ? 0 : t_dat[i-1][j];
						for(int k=1; k<=8; ++k) {
							if(i+d[k%8][0]<0 || i+d[k%8][0]>=src->height || j+d[k%8][1]<0 || j+d[k%8][1]>=src->width) p[k%8]=0;
							else p[k%8] = t_dat[ i+d[k%8][0] ][ j+d[k%8][1] ];
							if(p[k%8]) {
								++b;
								if(!p[k-1]) ++a;
							}
						}
						if(b>=2 && b<=6 && a==1)
							if(!s && !(p[2] && p[4] && (p[0] || p[6]))) dstdat[i][j]=0;
							else if(s && !(p[0] && p[6] && (p[2] || p[4]))) dstdat[i][j]=0;
					}
		}
    cvReleaseImage(&t_image);
}

