/**
 *	Declaration of Global Function & #DEFINE
 *	函数声明与宏定义声明
 */


#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED


////////	Global Definition		////////
#define KEY_ENTER	13
#define KEY_ESC		27
#define Length      50
////////			End				////////


////////	Function Declaration	////////

void InitCamera(CvCapture* cam, IplImage*& img);
void InitPerspectivePoints(const IplImage* img);

void on_mouse(int mouseevent, int x, int y, int flags, void* param);
void VOID_mouse(int mouseevent, int x, int y, int flags, void* param);

void DrawPerspectivePoints(IplImage*& img);
void GetCameraImage(const char* winName, IplImage*& img, CvCapture* cam);
void GetPerspectivePoints(const char* winName, IplImage*& img);

void RouteBinaryzationThin(IplImage*& img);
void cvThin(IplImage* src, IplImage* dst, int iterations=1);

void route(CvPoint start, RgbImage dat);	//	函数接口
void route(int x,int y,RgbImage dat,int len,int wid,int last=1);
void avoid_back(int x,int y,int len,int wid,int l);
void set_a_dot(RgbImage dat);
void revive_a_dot(RgbImage dat,int len,int wid);
void set_a_big_dot(RgbImage dat,int len,int wid);
void display(const char * xx,IplImage* testImage,RgbImage d1);

////////			End				////////


#endif // FUNCTION_H_INCLUDED
