//Enumeration take step
#include <iostream>
using namespace std;
int main()
{
    int floor;
    for(floor=7;true;floor+=7){
        if (floor%2==1 && floor%3==2 && floor%5==4 && floor%6==5 && floor%7==0) break;
    }
    cout<<floor<<endl;
    return 0;
}
