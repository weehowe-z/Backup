//This program deals 4 largest lakes' problem.
#include <iostream>
using namespace std;
int main()
{
    int a,b,c,d;
    bool flag=false;
    for (a=1;a<=4 && !flag;a++){
        for (b=1;b<=4 && !flag;b++){
            if (a==b) continue;
            for (c=1;c<=4 && !flag;c++){
                if (a==c || b==c) continue;
                d=10-a-b-c;
                if ((a==1)+(b==4)+(c==3)==1
                    &&(b==1)+(a==4)+(c==2)+(d==3)==1
                    &&(b==4)+(a==3)==1
                    &&(b==2)+(d==4)+(c==1)+(a==3)==1){
                        cout<<a<<b<<c<<d;
                        }
            }
        }
    }
    return 0;
}
