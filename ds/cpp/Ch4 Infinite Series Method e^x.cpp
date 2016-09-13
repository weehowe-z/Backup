//Infinite series by Weehowe.z VER 1.0
#include <iostream>
using namespace std;
int main()
{
    double ex,p,x;
    int n;
    ex=0;
    p=n=1;

    cout<<"This program calculate e^x by infinite series\n\n";
    cout<<"Please input the x: ";
    cin>>x;

    while(p>=1e-6){
       ex+=p;
       p*=x/n;
       n++;
    }

    cout<<"e^"<<x<<" = "<<ex<<endl;
    cout<<"Thank you for using!\n";
    return 0;
}
