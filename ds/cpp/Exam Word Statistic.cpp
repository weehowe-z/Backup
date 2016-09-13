//单词统计
//效率还可以改进
//输入检测
#include<iostream>
#include<cstring>
using namespace std;
void standardize(char *string);
void statistic(char*string);

int allWordNum=0;//单词总数
int differentWordNum=0;//不同单词数量
int wordNum[20]={0};//每一个不同单词的数量

char word[20][20];//所有不同单词的数组
char *nowWord;//当前单词

char sentence[100];

int main()
{
    cout<<"请输入句子（不超过80个字符）:\n";
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
        //如果找到一个单词
        if (prev==' '&&*p!=' ') {
            ++allWordNum;
            len=0;
            flag=true;
            stop=p;
            nowWord=new char[20];
            //计算长度
            while (*stop!='\0'&&*stop!=' '){
                ++len;
                ++stop;
            }
            //拷贝到当前单词
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
    cout<<"单词总数: "<<allWordNum<<endl;
    cout<<"不同的单词个数: "<<differentWordNum<<endl;
    for (int i=0;i<differentWordNum;++i){
        cout<<word[i]<<"\t个数: "<<wordNum[i]<<endl;
    }
}
