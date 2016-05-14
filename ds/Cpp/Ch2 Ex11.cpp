#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    double plot1[2],plot2[2];
    int i;
    for (i=0;i<=1;i++) {cin>>plot1[i];}
    for (i=0;i<=1;i++) {cin>>plot2[i];}
    cout<<sqrt(pow((plot1[0]-plot2[0]),2)+pow((plot1[1]-plot2[1]),2));
    return 0;
}
