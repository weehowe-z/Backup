#include <iostream>
#include <string>
using namespace std;
bool isPalsquare(string num);
string decimalToBase(int num,int base);
string reverse(string num);
int main()
{
    int base;
    cin>>base;
    for (int i=1;i<=300;++i){
        if (isPalsquare(decimalToBase(i*i,base))) cout<<reverse(decimalToBase(i,base))<<" "<<decimalToBase(i*i,base)<<endl;
    }
    return 0;
}
bool isPalsquare(string num)
{
    int a=0;
    int b=num.length()-1;
    while(true){
        if (b-a<1) return true;
        if (num[a]!=num[b]) return false;
        ++a;
        --b;
    }
}
string decimalToBase(int num,int base)// in reverse version
{
    string numInBase;
    int a;
    while (num>0){
        a=num%base;
        if (a>=10) numInBase.append(1,char(a-10+'A'));
            else numInBase.append(1,char(a+'0'));
        num=num/base;
    }
    return numInBase;
}
string reverse(string num)
{
    string numInReverse;
    for ( int i=num.length()-1;i>=0;--i) numInReverse.append(1,num[i]);
    return numInReverse;
}

