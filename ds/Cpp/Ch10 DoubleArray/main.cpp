#include <iostream>
#include "DoubleArray.h"
using namespace std;

int main()
{
    DoubleArray array(20,30);
    int i;
    double value;
    for (i=20;i<=30;++i){
        cout<<"Please input No."<<i<<" element: ";
        cin>>value;
        array.insert(i,value);
    }
    while (true){
        cout<<"Please enter the No. you want to find( 0 to quit ): ";
        cin>>i;
        if (i==0) break;
        if (array.fatch(i,value)) cout<<"No."<<i<<" element = "<<value<<endl;
            else cout<<"Out of range!\n";
    }
    return 0;
}
