#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    int n,cnt=1;
    cin>>n;
    int **mon;
    mon=new int*[n];
    for(int i=0;i<n;++i) mon[i]=new int[n];
    for(int p=0;p<(n+1)/2;++p){
        for(int j=p;j<=n-p-1;++j) mon[p][j]=cnt++;
        for(int i=p+1;i<n-p-1;++i) mon[i][n-p-1]=cnt++;
        for(int j=n-p-1;j>p;--j) mon[n-p-1][j]=cnt++;
        for(int i=n-p-1;i>p;--i) mon[i][p]=cnt++;
    }
    for (int i=0;i<n;++i){
        for (int j=0;j<n;++j) cout<<setw(6) <<mon[i][j];
        cout<<endl;
    }
    for (int i=0;i<n;++i) delete []mon[i];
    delete []mon;
    return 0;
}
