#include <iostream>
using namespace std;
int main()
{
    char *str1,*p;
    char *str2,*q;
    str1=new char[1002];
    str2=new char[1002];
    int similarity=0;
    cin.getline(str1,1000);
    cin.getline(str2,1000);
    p=str1;
    q=str2;
    while (*str1!='\0'&&*str2!='\0'){
        if (*str1==*str2) ++similarity;
        ++str1;
        ++str2;
    }
    cout<<similarity;
    str1=p;
    str2=q;
    delete []str1;
    delete []str2;
    return 0;
}
