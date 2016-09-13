//Fahrenheit degree to Celsius degree
//By Weehowe.z 2014.3.2 Ver 1.0
#include <iostream>
using namespace std;
int main()
{
    int c,f;
    cout<<"Please input Fahrenheit degree.: ";
    cin>>f;
    c = double(5)/9*(f-32);
    cout<<"The Celsius degree is "<<c<<endl;
    cout<<"Thank you for using!"<<endl;
    return 0;
}

