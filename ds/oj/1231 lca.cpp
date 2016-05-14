#include <iostream>
using namespace std;
int main()
{
    int n,x,y,a,b;
    cin>>n>>x>>y;
    int tree[n+1];
    tree[1]=0;
    for (int i=1;i<n+1;++i)
    {
        cin>>a>>b;
        tree[a]=tree[b]=i;
    }
    a=x;
    b=y;
    int counta=0,countb=0;
    while (tree[a]!=0){
        a=tree[a];
        ++counta;
    }
    while (tree[b]!=0){
        b=tree[b];
        ++countb;
    }
    a=x;
    b=y;
    if (counta>=countb){
        for (int i=0;i<counta-countb;++i)  a=tree[a];
    }
        else {
            for (int i=0;i<countb;++i)  b=tree[b];
        }
    while (a!=b) {a=tree[a];b=tree[b];}
    cout<<a<<endl;
    return 0;
}
