#include <iostream>
using namespace std;
int ackerman(int m,int n);
int main()
{
    int m,n;
    cin>>m>>n;
    cout<<ackerman(m,n)<<endl;
}
int ackerman(int m,int n)
{
    if (m==0) return n+1;
    if (n==0) return ackerman(m-1,1);
    return ackerman(m-1,ackerman(m,n-1));
}
