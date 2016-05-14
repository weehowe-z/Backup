//Fib sequence
#include <iostream>
using namespace std;
int main()
{
    int n;
    int *num;
    cin>>n;
    if (n<=1) {cout<<1;return 0;}
    num=new int[n];
    num[0]=1;
    num[1]=1;
    for (int i=2;i<n;++i){
            num[i]=num[i-1]+num[i-2];
    }
    cout<<num[n-2]+num[n-1];
    delete []num;
    return 0;
}
