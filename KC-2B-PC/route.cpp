#include <core/core.hpp>
#include <cv.h>
#include <highgui/highgui.hpp>
#include "image.h"
#include "function.h"

using namespace cv;

int dots[121][3];
int counts=0;
bool has[641*481];
//bool* has;

extern CvPoint RouteDot[1000];
extern int total_dots;


void save_a_dot(RgbImage dat, CvPoint a, int len, int wid)
{
    for (int i=-5; i<=5; ++i)
        for (int j=-5; j<=5; ++j)
            if (a.x+i<wid && a.x+i>0 && a.y+j<len && a.y+j>0) {
                dots[(i+5)*11+j+5][2] = dat[a.y+j][a.x+i].b;
                dots[(i+5)*11+j+5][0] = dat[a.y+j][a.x+i].r;
                dots[(i+5)*11+j+5][1] = dat[a.y+j][a.x+i].g;
			}
}


void revive_a_dot(RgbImage dat, CvPoint a, int len, int wid)
{
    for (int i=-5; i<=5 ; ++i)
        for (int j=-5; j<=5; ++j)
            if (a.x+i<wid && a.x+i>0 && a.y+j<len && a.y+j>0) {
                dat[a.y+j][a.x+i].b = dots[(i+5)*11+j+5][2];
                dat[a.y+j][a.x+i].r = dots[(i+5)*11+j+5][0];
                dat[a.y+j][a.x+i].g = dots[(i+5)*11+j+5][1];
			}

}


void set_a_big_dot(RgbImage dat, CvPoint a, int len, int wid)
{
    save_a_dot(dat, a, len,wid);
    for (int i=-5;i<=5;i++)
        for (int j=-5;j<=5;j++)
            if (a.x+i<wid && a.x+i>0 && a.y+j<len && a.y+j>0) {
                dat[a.y+j][a.x+i].b = 255;
                dat[a.y+j][a.x+i].r = dat[a.y+j][a.x+i].g=0;
			}
}


void avoid_back(int x, int y, int len, int wid, int l)
{
    ++l;
    for (int i=-l; i<=l; ++i)
        for (int j=-l; j<=l; ++j)
            if(y+j<len && j+y>0 && x+i<wid && x+i>0) has[(y+j)*wid+x+i]=true;
}


void set_a_dot(RgbImage dat)
{
    int x,y;
    for (int i=0;i<total_dots;i++) {
        x=RouteDot[i].x;
        y=RouteDot[i].y;
        dat[y][x+1].r=255;dat[y][x+1].b=dat[y][x+1].g=0;
        if (x-1)dat[y][x-1].r=255;dat[y][x-1].b=dat[y][x-1].g=0;
        dat[y][x].r=255;dat[y][x].b=dat[y][x].g=0;
        dat[y+1][x+1].r=255;dat[y+1][x+1].b=dat[y+1][x+1].g=0;
        if (y-1)dat[y-1][x+1].r=255;dat[y-1][x+1].b=dat[y-1][x+1].g=0;
        dat[y+1][x].r=255;dat[y+1][x].b=dat[y+1][x].g=0;
        if (x-1)dat[y+1][x-1].r=255;dat[y+1][x-1].b=dat[y+1][x-1].g=0;
        if(y-1)dat[y-1][x].r=255;dat[y-1][x].b=dat[y-1][x].g=0;
        if(x-1 && y-1) dat[y-1][x-1].r=255; dat[y-1][x-1].b=dat[y-1][x-1].g=0;
    }
}


void route(CvPoint start, RgbImage dat)
{
	//int size = 1000*1000*10;
	//has = new bool[size];
	//for(int i=0; i<641*481; ++i) has[i]=false;
	route(start.x, start.y, dat, dat.height(), dat.width());
	//delete[] has;
	//has = NULL;
}

void route(int x,int y,RgbImage dat,int len,int wid,int last)
{
    int i=1;
    while (1)
    {
        if (last==1)
        {

        for (int j=-i;j<i;j++)
        {
            if ((y-i>0) && (x+j<wid) && (y-i<len) && (x+j>0))
            if(dat[y-i][x+j].r==255 && !has[x+j+y*wid-i*wid] )
            {
                if(++counts==Length)
                {
                    set_a_dot(dat);
                    counts=0;
                    RouteDot[total_dots].x=x;
                    RouteDot[total_dots++].y=y;
                    return;
                }
                has[x+j+y*wid-i*wid]=true;
                avoid_back(x,y,len,wid,i);
                route(x+j,y-i,dat,len,wid,1);
                return;
            }
        }
        for (int j=i;j>-i;j--)
        {
            if ((y+j>0) && (x+i<wid) && (y+j<len) && (x+i>0))
            if(dat[y+j][x+i].r==255 && !has[x+i+wid*(j+y)] )
            {
                if(++counts==Length)
                {
                    set_a_dot(dat);
                    counts=0;
                    RouteDot[total_dots].x=x;
                    RouteDot[total_dots++].y=y;
                    return;
                }
                has[x+i+(j+y)*wid]=true;
                avoid_back(x,y,len,wid,i);
                route(x+i,y+j,dat,len,wid,2);
                return;
            }
        }
        for (int j=i;j>-i;j--)
        {
            if ((y+i>0) && (x+j<wid) && (y+i<len) && (x+j>0))
            if(dat[y+i][x+j].r==255 && !has[x+j+wid*(i+y)])
            {
                if(++counts==Length)
                {
                    set_a_dot(dat);
                    counts=0;
                    RouteDot[total_dots].x=x;
                    RouteDot[total_dots++].y=y;
                    return;
                }
                has[x+j+wid*(i+y)]=true;
                avoid_back(x,y,len,wid,i);
                route(x+j,y+i,dat,len,wid,3);
                return;
            }
        }
        for (int j=-i;j<i;j++)
        {
            if ((y+j>0) && (x-i<wid) && (y+j<len) && (x-i>0))
            if(dat[y+j][x-i].r==255 && !has[x-i+wid*(y+j)])
            {
                if(++counts==Length)
                {
                    set_a_dot(dat);
                    counts=0;
                    RouteDot[total_dots].x=x;
                    RouteDot[total_dots++].y=y;
                    return;
                }
                has[x-i+wid*(y+j)]=true;
                avoid_back(x,y,len,wid,i);
                route(x-i,y+j,dat,len,wid,4);
                return;
            }
        }
        i++;
        }
        if (last==2)

        {
        for (int j=i;j>-i;j--)
        {
            if ((y+j>0) && (x+i<wid) && (y+j<len) && (x+i>0))
            if(dat[y+j][x+i].r==255 && !has[x+i+wid*(j+y)] )
            {
                if(++counts==Length)
                {
                    set_a_dot(dat);
                    counts=0;
                    RouteDot[total_dots].x=x;
                    RouteDot[total_dots++].y=y;
                    return;
                }
                has[x+i+(j+y)*wid]=true;
                avoid_back(x,y,len,wid,i);
                route(x+i,y+j,dat,len,wid,2);
                return;
            }
        }
        for (int j=i;j>-i;j--)
        {
            if ((y+i>0) && (x+j<wid) && (y+i<len) && (x+j>0))
            if(dat[y+i][x+j].r==255 && !has[x+j+wid*(i+y)])
            {
                if(++counts==Length)
                {
                    set_a_dot(dat);
                    counts=0;
                    RouteDot[total_dots].x=x;
                    RouteDot[total_dots++].y=y;
                    return;
                }
                has[x+j+wid*(i+y)]=true;
                avoid_back(x,y,len,wid,i);
                route(x+j,y+i,dat,len,wid,3);
                return;
            }
        }
        for (int j=-i;j<i;j++)
        {
            if ((y+j>0) && (x-i<wid) && (y+j<len) && (x-i>0))
            if(dat[y+j][x-i].r==255 && !has[x-i+wid*(y+j)])
            {
                if(++counts==Length)
                {
                    set_a_dot(dat);
                    counts=0;
                    RouteDot[total_dots].x=x;
                    RouteDot[total_dots++].y=y;
                    return;
                }
                has[x-i+wid*(y+j)]=true;
                avoid_back(x,y,len,wid,i);
                route(x-i,y+j,dat,len,wid,4);
                return;
            }
        }

        for (int j=-i;j<i;j++)
        {
            if ((y-i>0) && (x+j<wid) && (y-i<len) && (x+j>0))
            if(dat[y-i][x+j].r==255 && !has[x+j+y*wid-i*wid] )
            {
                if(++counts==Length)
                {
                    set_a_dot(dat);
                    counts=0;
                    RouteDot[total_dots].x=x;
                    RouteDot[total_dots++].y=y;
                    return;
                }
                has[x+j+y*wid-i*wid]=true;
                avoid_back(x,y,len,wid,i);
                route(x+j,y-i,dat,len,wid,1);
                return;
            }
        }
        i++;
        }
        if (last==3)

        {
        for (int j=i;j>-i;j--)
        {
            if ((y+i>0) && (x+j<wid) && (y+i<len) && (x+j>0))
            if(dat[y+i][x+j].r==255 && !has[x+j+wid*(i+y)])
            {
                if(++counts==Length)
                {
                    set_a_dot(dat);
                    counts=0;
                    RouteDot[total_dots].x=x;
                    RouteDot[total_dots++].y=y;
                    return;
                }
                has[x+j+wid*(i+y)]=true;
                avoid_back(x,y,len,wid,i);
                route(x+j,y+i,dat,len,wid,3);
                return;
            }
        }
        for (int j=-i;j<i;j++)
        {
            if ((y+j>0) && (x-i<wid) && (y+j<len) && (x-i>0))
            if(dat[y+j][x-i].r==255 && !has[x-i+wid*(y+j)])
            {
                if(++counts==Length)
                {
                    set_a_dot(dat);
                    counts=0;
                    RouteDot[total_dots].x=x;
                    RouteDot[total_dots++].y=y;
                    return;
                }
                has[x-i+wid*(y+j)]=true;
                avoid_back(x,y,len,wid,i);
                route(x-i,y+j,dat,len,wid,4);
                return;
            }
        }

        for (int j=-i;j<i;j++)
        {
            if ((y-i>0) && (x+j<wid) && (y-i<len) && (x+j>0))
            if(dat[y-i][x+j].r==255 && !has[x+j+y*wid-i*wid] )
            {
                if(++counts==Length)
                {
                    set_a_dot(dat);
                    counts=0;
                    RouteDot[total_dots].x=x;
                    RouteDot[total_dots++].y=y;
                    return;
                }
                has[x+j+y*wid-i*wid]=true;
                avoid_back(x,y,len,wid,i);
                route(x+j,y-i,dat,len,wid,1);
                return;
            }
        }
        for (int j=i;j>-i;j--)
        {
            if ((y+j>0) && (x+i<wid) && (y+j<len) && (x+i>0))
            if(dat[y+j][x+i].r==255 && !has[x+i+wid*(j+y)] )
            {
                if(++counts==Length)
                {
                    set_a_dot(dat);
                    counts=0;
                    RouteDot[total_dots].x=x;
                    RouteDot[total_dots++].y=y;
                    return;
                }
                has[x+i+(j+y)*wid]=true;
                avoid_back(x,y,len,wid,i);
                route(x+i,y+j,dat,len,wid,2);
                return;
            }
        }
        i++;
        }
        if (last==4)

        {
        for (int j=-i;j<i;j++)
        {
            if ((y+j>0) && (x-i<wid) && (y+j<len) && (x-i>0))
            if(dat[y+j][x-i].r==255 && !has[x-i+wid*(y+j)])
            {
                if(++counts==Length)
                {
                    set_a_dot(dat);
                    counts=0;
                    RouteDot[total_dots].x=x;
                    RouteDot[total_dots++].y=y;
                    return;
                }
                has[x-i+wid*(y+j)]=true;
                avoid_back(x,y,len,wid,i);
                route(x-i,y+j,dat,len,wid,4);
                return;
            }
        }

        for (int j=-i;j<i;j++)
        {
            if ((y-i>0) && (x+j<wid) && (y-i<len) && (x+j>0))
            if(dat[y-i][x+j].r==255 && !has[x+j+y*wid-i*wid] )
            {
                if(++counts==Length)
                {
                    set_a_dot(dat);
                    counts=0;
                    RouteDot[total_dots].x=x;
                    RouteDot[total_dots++].y=y;
                    return;
                }
                has[x+j+y*wid-i*wid]=true;
                avoid_back(x,y,len,wid,i);
                route(x+j,y-i,dat,len,wid,1);
                return;
            }
        }
        for (int j=i;j>-i;j--)
        {
            if ((y+j>0) && (x+i<wid) && (y+j<len) && (x+i>0))
            if(dat[y+j][x+i].r==255 && !has[x+i+wid*(j+y)] )
            {
                if(++counts==Length)
                {
                    set_a_dot(dat);
                    counts=0;
                    RouteDot[total_dots].x=x;
                    RouteDot[total_dots++].y=y;
                    return;
                }
                has[x+i+(j+y)*wid]=true;
                avoid_back(x,y,len,wid,i);
                route(x+i,y+j,dat,len,wid,2);
                return;
            }
        }
        for (int j=i;j>-i;j--)
        {
            if ((y+i>0) && (x+j<wid) && (y+i<len) && (x+j>0))
            if(dat[y+i][x+j].r==255 && !has[x+j+wid*(i+y)])
            {
                if(++counts==Length)
                {
                    set_a_dot(dat);
                    counts=0;
                    RouteDot[total_dots].x=x;
                    RouteDot[total_dots++].y=y;
                    return;
                }
                has[x+j+wid*(i+y)]=true;
                avoid_back(x,y,len,wid,i);
                route(x+j,y+i,dat,len,wid,3);
                return;
            }
        }
        i++;
        }
        if (i>=50)
        {
            RouteDot[total_dots].x=RouteDot[total_dots-1].x;
            RouteDot[total_dots].y=RouteDot[total_dots-1].y;
            return;
        }
    }
}


void display(const char * xx,IplImage* testImage,RgbImage RgbRoute)
{
    for (int i=0;i<total_dots;i++)
    {
        if(i) revive_a_dot(RgbRoute, RouteDot[i-1], testImage->height, testImage->width);
        set_a_big_dot(RgbRoute, RouteDot[i], testImage->height, testImage->width);
        cvShowImage(xx,testImage);
        cvWaitKey(200);
    }
}
