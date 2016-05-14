#include <iostream>
using namespace std;
int main()
{
    int m,t,u,f,d;
    char *type;
    int distance=0,time=0;
    cin>>m>>t>>u>>f>>d;
    type=new char[t];
    for (int i=0;i<t;++i) cin>>type[i];
    int i=0;
    while (true){
        if (type[i]=='f'||type[i]=='F') {
                time+=2*f;
                if (time>=m) break;
                ++distance;
        }
        else {
            time+= (u+d);
            if (time>=m) break;
            ++distance;
        }
        ++i;
    }
    cout<<distance<<endl;
    return 0;
}
