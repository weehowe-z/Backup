//����ͳ��
//Ч�ʻ����ԸĽ�
//������
#include<iostream>
#include<cstring>
using namespace std;
void standardize(char *string);
void statistic(char*string);

int allWordNum=0;//��������
int differentWordNum=0;//��ͬ��������
int wordNum[20]={0};//ÿһ����ͬ���ʵ�����

char word[20][20];//���в�ͬ���ʵ�����
char *nowWord;//��ǰ����

char sentence[100];

int main()
{
    cout<<"��������ӣ�������80���ַ���:\n";
    cin.getline(sentence,80);
    standardize(sentence);
    statistic(sentence);
    return 0;

}
void standardize(char *p)
{
    while (*p!='\0'){
        if (!(*p>='a'&&*p<='z'||*p>='A'&&*p<='Z')) *p=' ';
        if (*p>='A'&&*p<='Z') *p=char(*p-'A'+'a');
        ++p;
    }
//    cout<<"Std: "<<sentence<<endl;
}
void statistic(char *p)
{
    char *stop=NULL;
    char prev=' ';
    bool flag;
    int len;
    while (*p!='\0'){
        //����ҵ�һ������
        if (prev==' '&&*p!=' ') {
            ++allWordNum;
            len=0;
            flag=true;
            stop=p;
            nowWord=new char[20];
            //���㳤��
            while (*stop!='\0'&&*stop!=' '){
                ++len;
                ++stop;
            }
            //��������ǰ����
            strncpy(nowWord,p,len);
            nowWord[len]='\0';
//          cout<<"String len:"<<len<<"  Now: "<<nowWord<<endl;
            for(int i=0;i<differentWordNum;++i){
                    if (strcmp(nowWord,word[i])==0){
                        ++wordNum[i];
//                        cout<<"Find same word : "<<word[i]<<endl;
                        flag=false;
                        break;
                    }
            }
            if (flag){
                strcpy(word[differentWordNum],nowWord);
//                cout<<"Find dif word : "<<word[differentWordNum]<<endl;
                ++wordNum[differentWordNum];
                ++differentWordNum;
            }
            delete []nowWord;
        }
        prev=*p;
        ++p;
    }
    cout<<"��������: "<<allWordNum<<endl;
    cout<<"��ͬ�ĵ��ʸ���: "<<differentWordNum<<endl;
    for (int i=0;i<differentWordNum;++i){
        cout<<word[i]<<"\t����: "<<wordNum[i]<<endl;
    }
}
