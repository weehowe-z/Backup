#include <iostream>
using namespace std;
bool isBisquare(int num,int upbound);
void getAriProg(int terms,int upbound);
int main()
{
    int n,m;
    cin>>n>>m;
    getAriProg(n,m);
    return 0;
}
bool isBisquare(int num,int upbound)
{
    int p,q;
    for (int p=0;p<=upbound;++p){
        for (int q=0;q<=upbound;++q){
            if (p*p+q*q==num) return true;
        }
    }
    return false;
}
void getAriProg(int terms,int upbound)
{
    int max=2*upbound*upbound;
    int difference=1,leader;
    while (true)
    {
        if (difference*(terms-1)>max) break;
        for (int leader=0;leader<=max-(terms-1)*difference;++leader){
                //if (difference==24) cout<<"leader:"<<leader<<endl;
                bool flag=true;
                int test=leader;
                for (int i=0;i<terms;++i){
                    //cout<<"no."<<i<<endl;
                    if (!isBisquare(test,upbound)) {flag=false;break;}
                    test+=difference;
                }
                if (flag) cout<<leader<<" "<<difference<<endl;
        }
        ++difference;
    }
}
//2 26 50 74 98
