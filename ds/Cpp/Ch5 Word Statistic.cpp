//����ͳ�ƹ���
//V14.3.18 ����ѭ����ȡ ����I��m��ʶ��

#include <iostream>
#include <cstring>
using namespace std;
int statistics();
int main()
{
    cout<<"����ͳ�ƹ��� V0.3.18\n";
    int total=0,num=0;
    while (true){
        num=statistics();
        if (num==0) break;
        total+=num;
        cout<<"�����е��ʸ���Ϊ"<<num<<endl<<endl;
    }
    cout<<"\n���о��ӵ����ܸ���Ϊ"<<total<<endl<<endl;
    cout<<"��л����ʹ�ã�\n";
    return 0;
}
int statistics()
{
    char sentence[100],prev=' ';
    int num=0,i;
    cout<<"�������(�����뵥�����˳�):";
    cin.getline(sentence,100);
    strcat(sentence," ");//ĩβ����
    for (i=0;sentence[i]!='\0';i++){
        if ((prev!=' ' && sentence[i]==' ' ) ||
            ( prev=='\'' && sentence[i] != ' ')) num++;
        prev=sentence[i];
        }
    return num;
    }
