//Calculate the area and the circumference of a circle
//Weehowe.z 2014.2.28 Ver1.0
#include <iostream>
#include <cmath>
using namespace std;
const double pi=3.1415926;
int main()
{
    double radius,area,circumference,radian,arcLength,sectorialArea;
    cout<<"You can calculate some attributes of a circle."<<endl;
    cout<<"Please input the radius of the circle: ";
    cin>>radius;
    area =pi*pow(radius,2);
    circumference = 2 * pi * radius;
    cout<<"The area is " <<area<<endl;
    cout<<"The circumference is "<<circumference<<endl;
    cout<<"Please input the radian of the arc: ";
    cin>>radian;
    cout<<"sin = "<<sin(radian)<<endl;
    arcLength =radian*radius;
    sectorialArea=0.5*radian*pow(radius,2);
    cout<<"The arc length is " <<arcLength<<endl;
    cout<<"The sectorial area is "<<sectorialArea<<endl;
    return 0;
}
