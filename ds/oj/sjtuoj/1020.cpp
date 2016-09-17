#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    long int n,org;
    int sqr,*sat;
    bool flag=true;
    cin>>n;
    org=n;
    sqr=pow(n,0.5);
    sat=new int[sqr+1];
    for(int i=0;i<=sqr;++i) sat[i]=0;
    while (flag)
    {
        flag=false;
        for (int k=2;k<=pow(n,0.5);++k){
            if (n%k==0) {
                ++sat[k];
                flag=true;
                n=n/k;
                break;
            }
        }
    }
    if (n<=sqr) ++sat[n];
    cout<<org<<"=";
    for (int i=2;i<=sqr;++i) {
            if (sat[i]!=0) cout<<i<<"("<<sat[i]<<")";
    }
    if (n>sqr) cout<<n<<"("<<1<<")";
    cout<<endl;
    delete []sat;
    return 0;
}
