//Coordinate and digital By Weehowe.z
//V14.3.13 完成基本功能
//我们从0开始把整数写在两条直线y=x y=x-1上.
//0, 1, 2,  3分别写在(0,0), (1,1), (2,0)和(3, 1)这4点上。如图规律继续写
//现在给定坐标(x,y)，问(x,y)位置的整数是多少？
//如果这个位置不存在整数，输入-1。其中，0<=x,y<=1100。
#include <iostream>
using namespace std;
int coordinate(int x,int y)
{
   if ((y==x || y== x-2)&&(x>=0 && x<=1100 && y>=0 && y<=1100)){
        if (y==x) {
            if (x%2==0) return 2*x;
            else return 2*x-1;
            }
        else {if (x%2==0) return 2*x-2;
                else return 2*x-3;
                }
        }
    else return -1;
}
int main()
{
    int x,y;
    cout<<"请输入整数坐标（x,y） (0到1100以内）: ";
    cin>>x>>y;
    cout    <<coordinate(x,y)<<endl;
    return 0;
}
