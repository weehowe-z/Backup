#include <iostream>
using namespace std;
int main()
{
    int budget[12];
    int pocket=0;
    int saving=0;
    for (int i=0;i<12;++i) cin>>budget[i];
    for (int i=0;i<12;++i) {
        pocket+=300;
        pocket-=budget[i];
        if (pocket<0) {cout<<"-"<<i+1;return 0;}
        while (pocket>=100){
            pocket-=100;
            saving+=100;
        }
    }
    cout<<saving*1.2+pocket;
    return 0;
}
