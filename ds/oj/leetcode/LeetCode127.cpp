#include <iostream>
#include <string>
using namespace std;
int getDis(string a,string b);

int main()
{
        return 0;
}

int getDis(string a,string b)
{
        unsigned dif=0;
        unsigned int len=a.length();
        for (unsigned int i=0; i<len; ++i) {
                if (a[i]!=b[i]) ++dif;
        }
        return dif;
}
