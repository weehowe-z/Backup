//敏感词过滤 By Weehowe.z
//V14.4.14 完成基础功能。
//V14.4.16 根据拓展版功能重写代码
//V14.4.17 增加对大小写不敏感
//V14.4.17 增加递归调用过滤函数 完整过滤
//V14.4.17 增加自定义敏感词长度检测
//下一版展望 1、针对自定义标点输入内容增加输入检测.
#include <iostream>
#include <cstring>
using namespace std;

const int maxlen = 100;
int punctuationNum=3;//默认标点符号数
int uselessNum=3;//默认无用符号数
int sensitiveNum=3;//默认敏感词数
int stringlen=20;//默认字符串最大长度

char *punctuation;//指向标点符号动态数组的指针
char *useless;//指向无用符号动态数组的指针
char **sensitiveWord;//指向过滤字符二维动态数组的指针
char *pstring;//指向字符串数组的指针

void initialize();//初始化话合法字符和过滤字符
void release();//释放动态数组空间
void getInput();//获取输入字符串
void filter(char*);//过滤
bool validityCheck(const char *);//判断字符串合法性
bool InAcpChar(const char *);//判断字符是否在可接受字符内
bool compare(char,char);//大小写不敏感的比较
int main()
{
    initialize();
    while (true){
        getInput();
        filter(pstring);//过滤
        cout<<"过滤后: "<<pstring<<endl<<endl;
        delete []pstring;//释放在getInput中申请的空间
    }
    release();//释放空间
    return 0;
}
void initialize()//初始化合法字符和过滤字符
{
    char answer;
    int i;
    cout<<"欢迎使用和谐工具β   \t\t by Weehowe.z\n\n";
    //自定义标点符号
    cout<<"是否需要自定义标点？ 请输入y或n： ";
    while(true){
        cin>>answer;
        if (answer=='y'||answer=='Y'){
            cout<<"您要定义几个标点？ ";
            while (true){
                cin>>punctuationNum;
                if (punctuationNum>0) break;
                cout<<"您的输入有误，请输入正确的个数:  ";
            }
            punctuation=new char[punctuationNum];
            for (i=0;i<punctuationNum;++i){
                cout<<"请输入第"<<i+1<<"个标点: ";
                cin>>punctuation[i];
            }
            break;
        }
        if (answer=='n'||answer=='N'){
            punctuation=new char[4];
            punctuation[0]=',';
            punctuation[1]='.';
            punctuation[2]='"';
            break;
        }
        cout<<"您的输入有误，请输入y或n: ";
    }
    cout<<"您定义的标点符号是: ";
    for (i=0;i<punctuationNum;++i) cout<<punctuation[i]<<" ";
    cout<<endl<<endl;
    //自定义无用字符
    cout<<"是否需要自定义无用字符？ 请输入y或n： ";
    while(true){
        cin>>answer;
        if (answer=='y'||answer=='Y'){
            cout<<"您要定义几个无用字符？ ";
           while (true){
                cin>>uselessNum;
                if (uselessNum>0) break;
                cout<<"您的输入有误，请输入正确的个数:  ";
            }
            useless=new char[uselessNum];
            for (i=0;i<uselessNum;++i){
                cout<<"请输入第"<<i+1<<"个无用字符: ";
                cin>>useless[i];
            }
            break;
        }
        if (answer=='n'||answer=='N'){//保存默认信息
            useless=new char[4];
            useless[0]='@';
            useless[1]='#';
            useless[2]='$';
            break;
        }
        cout<<"您的输入有误，请输入y或n: ";
    }
    cout<<"您定义的无用字符是: ";
    for (i=0;i<uselessNum;++i) cout<<useless[i]<<" ";
    cout<<endl<<endl;
    //自定义敏感词
    cout<<"是否需要自定义敏感词汇？ 请输入y或n： ";
    while(true){
        cin>>answer;
        if (answer=='y'||answer=='Y'){
            cout<<"您要定义几个敏感词汇？ ";//需要增加输入检测
            while (true){
                cin>>sensitiveNum;
                if (sensitiveNum>0) break;
                cout<<"您的输入有误，请输入正确的个数:  ";
            }
            cin.ignore();//消除输入流中的残余
            sensitiveWord=new char*[sensitiveNum];//设置指针指向每一行的首地址
            for (i=0;i<sensitiveNum;++i){
                sensitiveWord[i]=new char[maxlen];
                cout<<"请输入第"<<i+1<<"个敏感词汇: ";
                while (true){
                    cin.getline(sensitiveWord[i],maxlen);
                    if (strlen(sensitiveWord[i])>1) break;
                    cout<<"您的输入有误，请输入至少2个字符: ";
                }
            }
            break;
        }
        if (answer=='n'||answer=='N'){//保存默认值
            sensitiveWord=new char*[3];
            for (i=0;i<sensitiveNum;++i) sensitiveWord[i]=new char[4];
            sensitiveWord[0]=(char*)"L4";
            sensitiveWord[1]=(char*)"Fd";
            sensitiveWord[2]=(char*)"D26";
            break;
        }
        cout<<"您的输入有误，请输入y或n: ";
    }
    cout<<"您定义的敏感词汇是: ";
    for (i=0;i<sensitiveNum;++i) cout<<sensitiveWord[i]<<" ";
    cout<<endl<<endl;
    //自定义最大长度
    cout<<"是否需要自定义字符串最大长度？ 请输入y或n： ";
    while(true){
        cin>>answer;
        if (answer=='y'||answer=='Y'){
            cout<<"请输入最大长度： ";
            while (true){
                cin>>stringlen;
                if (stringlen>0) break;
                cout<<"您的输入有误，请输入正确的长度:  ";
            }
            cin.ignore();
            break;
        }
        if (answer=='n'||answer=='N') {cin.ignore();break;}
        cout<<"您的输入有误，请输入y或n: ";
    }
    cout<<endl<<endl;
}
void release()//释放动态数组空间
{
    delete []punctuation;
    delete []useless;
    for (int i=0;i<sensitiveNum;++i) delete []sensitiveWord[i];
    delete []sensitiveWord;
    //delete []pstring;//在main函数中已使用
}
void getInput()//获取用户字符串输入
{
    pstring=new char[maxlen];
    while (true){
        cout<<"请输入字符串(不多于"<<stringlen<<"个字符) :\n";
        cin.getline(pstring,maxlen,'\n');
        if (validityCheck(pstring)) break;//如果通过合法性检查则跳出
        else cout<<"输入不符合要求\n\n";
    }
}
bool InAcpChar(const char *s)//判断字符是否为可接受字符（除了数字和字母）
{
    int i;
    if (*s==' ') return true;
    for (i=0;i<punctuationNum;++i) {
        if (*s==punctuation[i]) return true;
    }
    for (i=0;i<uselessNum;++i) {
        if (*s==useless[i]) return true;
    }
    return false;
}
bool validityCheck(const char *s)//判断字符串合法性
{
    if (strlen(s)>stringlen) {//判断长度
            cout<<"长度超出限制\n";
            return false;
    }
    while (*s!='\0'){//判断字符是否有效
        if (!(*s>='0' && *s<='9'|| *s>='a'&&* s<='z'||*s>='A' && *s<='Z'|| InAcpChar(s))) {
                cout<<*s<<"不是可接受字符\n";
                return false;
        }
        ++s;
    }
    return true;
}
bool compare(char a,char b)
{
    if ((a>='a'&&a<='z')&&(b>='A'&&b<='Z')) {if ((a-'a'+'A')==b) return true;}
    if ((a>='A'&&a<='Z')&&(b>='a'&&b<='z')) {if ((a-'A'+'a')==b) return true;}
    if (a==b) return true;
    return false;
}
void filter(char *s)
{
    bool sensitiveflag;//敏感词旗帜
    bool prevflag;//前一符号旗帜
    bool usefulflag;//有用符号旗帜
    bool filterflag=false;//过滤需要旗帜
    int i,j;
    char *p,*origin,*startPos,*stopPos;//敏感词位置的指针
    origin=s;//保存初始位置
    //寻找敏感词首字母
    while (*s!='\0'){
        sensitiveflag=false;//敏感词旗帜
        prevflag=false;//前一个符号被找到
        usefulflag=false;
        for (i=0;i<sensitiveNum;++i){//尝试每一个敏感词
            if (compare(*s,sensitiveWord[i][0])){//如果侦测该敏感词首字符
                sensitiveflag=true;
                prevflag=true;
                startPos=s;//保存位置
                break;
            }
        }
    if (!sensitiveflag) {
            ++s;
            continue;
            }//没有敏感词则不再过滤
    //寻找完整敏感词
    p=startPos+1;
    j=1;
    while(sensitiveWord[i][j]!='\0'&&prevflag){
        prevflag=false;
        while(*p!='\0'){
                if (compare(*p,sensitiveWord[i][j])){//找到敏感词的下一位
                    prevflag=true;
                    stopPos=p;
                    ++p;
                    break;
                }
                else {//不是敏感字符，判断是否有用
                    if (*p>='0' && *p<='9'|| *p>='a'&&* p<='z'||*p>='A' && *p<='Z') usefulflag=true;
                    for (int k=0;k<punctuationNum;++k)  if (*p==punctuation[k]) usefulflag=true;
                }
        ++p;
        }
        ++j;
    }
    if (!prevflag ){//没有找到完整敏感词，判断下一字符
            ++s;
            continue;
    }
     if (usefulflag) {//过滤词中包含有用词汇，判断下一字符
            ++s;
            continue;
    }
    if (!usefulflag) {
        strcpy(startPos,stopPos+1);//过滤
        filterflag=true;
        break;
        }
    ++s;
    }
    if (filterflag) filter(origin);//如果还需过滤则递归调用过滤函数
}
