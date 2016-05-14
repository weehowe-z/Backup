//factorial calculator
//by weehowe.z 2014.3.20
#include <iostream>
using namespace std;
int factorial(int n);
int main()
{
    int n;
    cout<<"please enter n(of n!): ";
    cin>>n;
    cout<<factorial(n);
    return 0;
}
int factorial(int n)
{
    if (n == 1) return 1;
    else return n*factorial(n-1);
}
