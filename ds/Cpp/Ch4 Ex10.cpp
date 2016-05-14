#include <iostream>
using namespace std;
int main()
{
    char ch[100];
    int i=0;
    int yuan=0,fu=0,space=0,num=0,other=0;
    cin.getline(ch,100,'.');
    while (ch[i]!='\0'){//大写转小写??！！！
            if (ch[i]=='a'||ch[i]=='i'||ch[i]=='u'||ch[i]=='e'||ch[i]=='o') {++yuan;i++;continue;}
            if (ch[i]>='a' && ch[i]<='z' &&ch[i]!='a'&&ch[i]!='i'&&ch[i]!='u'&&ch[i]!='e'&&ch[i]!='o') {++fu;i++;continue;}
            if (ch[i]==' ') {++space;i++;continue;}
            if (ch[i]>='0'&& ch[i]<='9') {++num;i++;continue;}
            ++other;
            i++;
    }
    cout<<"元音"<<yuan<<"个"<<endl;
    cout<<"辅音"<<fu<<"个"<<endl;
    cout<<"空格"<<space<<"个"<<endl;
    cout<<"数字"<<num<<"个"<<endl;
    cout<<"其他"<<other<<"个"<<endl;
    return 0;
}
