#include <iostream>
using namespace std;
int main()
{
    char a,b,c;
    for (a='A';a<='C';a++){
        for (b='A';b<='C';b++){
            if (a==b) continue;
            for (c='A';c<='C';c++){
                if (b==c || a==c) continue;
                cout<<a<<b<<c<<"\t";
            }
        }
    }
    return 0;
}
