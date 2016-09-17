#include <iostream>
using namespace std;
int main()
{
    int m,n;
    int* mm, *nm;
    bool flag=true;
    cin>>n;
    nm=new int[n];
    mm=new int[m];
    for (int i=0;i<n;++i) cin>>nm[i];
    cin>>m;
    for (int i=0;i<m;++i) cin>>mm[i];
    for (int i=0;i<m;++i) {
        flag=true;
        for (int j=0;j<n;++j){
            if (nm[j]==mm[i]) {cout<<'Y'<<endl;flag=false;break;}
        }
        if (flag) cout<<'N'<<endl;
    }
    //delete []mm;
    //delete []nm;
    return 0;
}
