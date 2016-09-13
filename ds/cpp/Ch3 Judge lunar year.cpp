//Judging Lunar Year
//Weehowe.z 2014.3.2 Ver1.0

#include <iostream>
using namespace std;
int main()
{
    int year;
    bool result;
    cout<<"Please input a year: ";
    cin>>year;
    result = (year%4 == 0 && year%100 != 0) || (year%400 == 0);
    if (result) cout<<year<<" is a lunar year."<<endl;
        else cout<<year<<" is not a lunar year."<<endl;
    cout<<"Thank you for using!"<<endl;
    return 0;
}
