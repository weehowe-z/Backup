#include <iostream>
using namespace std;
int main()
{
    int a;
    double total=0;
    cin>>a;
    a-=3500;
    while (a>80000) {total+=(a-80000)*0.45;a=80000;}
    while (a>55000) {total+=(a-55000)*0.35;a=55000;}
    while (a>35000) {total+=(a-35000)*0.3;a=35000;}
    while (a>9000) {total+=(a-9000)*0.25;a=9000;}
    while (a>4500) {total+=(a-4500)*0.2;a=4500;}
    while (a>1500) {total+=(a-1500)*0.1;a=1500;}
    if (a>0) total+=(a*0.03);
    cout<<int(total);
    return 0;
}
