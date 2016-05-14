#include <iostream>
using namespace std;
int main()
{
    int l,m;
    int **bowl;
    bool flag=true;

    cin>>l;
    bowl=new int*[l];
    for (int i=0;i<l;++i) bowl[i]=new int[l];

    for (int i=0;i<l;++i){
        for (int j=0;j<l;++j) {
            cin>>bowl[i][j];
            if (bowl[i][j]==2) bowl[i][j]=-1;
        }
    }

    m=0;
    while(true){
        flag=false;
        for (int i=0;i<l;++i){
            for (int j=0;j<l;++j) {
                if (bowl[i][j]==m+1){
                    //1
                    if (i>0 && bowl[i-1][j]==0) {bowl[i-1][j]=m+2;flag=true;}
                    if (j>0 && bowl[i][j-1]==0) {bowl[i][j-1]=m+2;flag=true;}
                    if (i<l-1 && bowl[i+1][j]==0) {bowl[i+1][j]=m+2;flag=true;}
                    if (j<l-1 && bowl[i][j+1]==0) {bowl[i][j+1]=m+2;flag=true;}
                }
            }
        }
        if (!flag) break;
        ++m;
    }
    cout<<m<<endl;

    for (int i=0;i<l;++i) delete []bowl[i];
    delete []bowl;
    return 0;

}
