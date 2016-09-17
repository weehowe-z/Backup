#include <iostream>
#define Nill -1
using namespace std;
int main()
{
    int n,m,a,b;
    cin>>n>>m;
    int* course;
    course=new int[n];
    for (int i=0;i<n;++i) course[i]=Nill;
    for (int i=0;i<m;++i){
        cin>>a>>b;
        course[a-1]=b-1;
    }
    int mintime=0;
    for (int i=0;i<n;++i){
        int minstep=1;
        int k=i;
        while (course[k]!=Nill){
            k=course[k];
            ++minstep;
        }
        if (minstep>mintime) mintime=minstep;
    }
    cout<<mintime<<endl;
    delete []course;
}
