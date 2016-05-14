//单词统计工具
//V14.3.18 增加循环获取 增加I’m的识别

#include <iostream>
#include <cstring>
using namespace std;
int statistics();
int main()
{
    cout<<"单词统计工具 V0.3.18\n";
    int total=0,num=0;
    while (true){
        num=statistics();
        if (num==0) break;
        total+=num;
        cout<<"本句中单词个数为"<<num<<endl<<endl;
    }
    cout<<"\n所有句子单词总个数为"<<total<<endl<<endl;
    cout<<"感谢您的使用！\n";
    return 0;
}
int statistics()
{
    char sentence[100],prev=' ';
    int num=0,i;
    cout<<"输入句子(不输入单词则退出):";
    cin.getline(sentence,100);
    strcat(sentence," ");//末尾增加
    for (i=0;sentence[i]!='\0';i++){
        if ((prev!=' ' && sentence[i]==' ' ) ||
            ( prev=='\'' && sentence[i] != ' ')) num++;
        prev=sentence[i];
        }
    return num;
    }
