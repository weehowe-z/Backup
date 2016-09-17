//���дʹ��� By Weehowe.z
//V14.4.14 ��ɻ������ܡ�
//V14.4.16 ������չ�湦����д����
//V14.4.17 ���ӶԴ�Сд������
//V14.4.17 ���ӵݹ���ù��˺��� ��������
//V14.4.17 �����Զ������дʳ��ȼ��
//��һ��չ�� 1������Զ�����������������������.
#include <iostream>
#include <cstring>
using namespace std;

const int maxlen = 100;
int punctuationNum=3;//Ĭ�ϱ�������
int uselessNum=3;//Ĭ�����÷�����
int sensitiveNum=3;//Ĭ�����д���
int stringlen=20;//Ĭ���ַ�����󳤶�

char *punctuation;//ָ������Ŷ�̬�����ָ��
char *useless;//ָ�����÷��Ŷ�̬�����ָ��
char **sensitiveWord;//ָ������ַ���ά��̬�����ָ��
char *pstring;//ָ���ַ��������ָ��

void initialize();//��ʼ�����Ϸ��ַ��͹����ַ�
void release();//�ͷŶ�̬����ռ�
void getInput();//��ȡ�����ַ���
void filter(char*);//����
bool validityCheck(const char *);//�ж��ַ����Ϸ���
bool InAcpChar(const char *);//�ж��ַ��Ƿ��ڿɽ����ַ���
bool compare(char,char);//��Сд�����еıȽ�
int main()
{
    initialize();
    while (true){
        getInput();
        filter(pstring);//����
        cout<<"���˺�: "<<pstring<<endl<<endl;
        delete []pstring;//�ͷ���getInput������Ŀռ�
    }
    release();//�ͷſռ�
    return 0;
}
void initialize()//��ʼ���Ϸ��ַ��͹����ַ�
{
    char answer;
    int i;
    cout<<"��ӭʹ�ú�г���ߦ�   \t\t by Weehowe.z\n\n";
    //�Զ��������
    cout<<"�Ƿ���Ҫ�Զ����㣿 ������y��n�� ";
    while(true){
        cin>>answer;
        if (answer=='y'||answer=='Y'){
            cout<<"��Ҫ���弸����㣿 ";
            while (true){
                cin>>punctuationNum;
                if (punctuationNum>0) break;
                cout<<"��������������������ȷ�ĸ���:  ";
            }
            punctuation=new char[punctuationNum];
            for (i=0;i<punctuationNum;++i){
                cout<<"�������"<<i+1<<"�����: ";
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
        cout<<"������������������y��n: ";
    }
    cout<<"������ı�������: ";
    for (i=0;i<punctuationNum;++i) cout<<punctuation[i]<<" ";
    cout<<endl<<endl;
    //�Զ��������ַ�
    cout<<"�Ƿ���Ҫ�Զ��������ַ��� ������y��n�� ";
    while(true){
        cin>>answer;
        if (answer=='y'||answer=='Y'){
            cout<<"��Ҫ���弸�������ַ��� ";
           while (true){
                cin>>uselessNum;
                if (uselessNum>0) break;
                cout<<"��������������������ȷ�ĸ���:  ";
            }
            useless=new char[uselessNum];
            for (i=0;i<uselessNum;++i){
                cout<<"�������"<<i+1<<"�������ַ�: ";
                cin>>useless[i];
            }
            break;
        }
        if (answer=='n'||answer=='N'){//����Ĭ����Ϣ
            useless=new char[4];
            useless[0]='@';
            useless[1]='#';
            useless[2]='$';
            break;
        }
        cout<<"������������������y��n: ";
    }
    cout<<"������������ַ���: ";
    for (i=0;i<uselessNum;++i) cout<<useless[i]<<" ";
    cout<<endl<<endl;
    //�Զ������д�
    cout<<"�Ƿ���Ҫ�Զ������дʻ㣿 ������y��n�� ";
    while(true){
        cin>>answer;
        if (answer=='y'||answer=='Y'){
            cout<<"��Ҫ���弸�����дʻ㣿 ";//��Ҫ����������
            while (true){
                cin>>sensitiveNum;
                if (sensitiveNum>0) break;
                cout<<"��������������������ȷ�ĸ���:  ";
            }
            cin.ignore();//�����������еĲ���
            sensitiveWord=new char*[sensitiveNum];//����ָ��ָ��ÿһ�е��׵�ַ
            for (i=0;i<sensitiveNum;++i){
                sensitiveWord[i]=new char[maxlen];
                cout<<"�������"<<i+1<<"�����дʻ�: ";
                while (true){
                    cin.getline(sensitiveWord[i],maxlen);
                    if (strlen(sensitiveWord[i])>1) break;
                    cout<<"����������������������2���ַ�: ";
                }
            }
            break;
        }
        if (answer=='n'||answer=='N'){//����Ĭ��ֵ
            sensitiveWord=new char*[3];
            for (i=0;i<sensitiveNum;++i) sensitiveWord[i]=new char[4];
            sensitiveWord[0]=(char*)"L4";
            sensitiveWord[1]=(char*)"Fd";
            sensitiveWord[2]=(char*)"D26";
            break;
        }
        cout<<"������������������y��n: ";
    }
    cout<<"����������дʻ���: ";
    for (i=0;i<sensitiveNum;++i) cout<<sensitiveWord[i]<<" ";
    cout<<endl<<endl;
    //�Զ�����󳤶�
    cout<<"�Ƿ���Ҫ�Զ����ַ�����󳤶ȣ� ������y��n�� ";
    while(true){
        cin>>answer;
        if (answer=='y'||answer=='Y'){
            cout<<"��������󳤶ȣ� ";
            while (true){
                cin>>stringlen;
                if (stringlen>0) break;
                cout<<"��������������������ȷ�ĳ���:  ";
            }
            cin.ignore();
            break;
        }
        if (answer=='n'||answer=='N') {cin.ignore();break;}
        cout<<"������������������y��n: ";
    }
    cout<<endl<<endl;
}
void release()//�ͷŶ�̬����ռ�
{
    delete []punctuation;
    delete []useless;
    for (int i=0;i<sensitiveNum;++i) delete []sensitiveWord[i];
    delete []sensitiveWord;
    //delete []pstring;//��main��������ʹ��
}
void getInput()//��ȡ�û��ַ�������
{
    pstring=new char[maxlen];
    while (true){
        cout<<"�������ַ���(������"<<stringlen<<"���ַ�) :\n";
        cin.getline(pstring,maxlen,'\n');
        if (validityCheck(pstring)) break;//���ͨ���Ϸ��Լ��������
        else cout<<"���벻����Ҫ��\n\n";
    }
}
bool InAcpChar(const char *s)//�ж��ַ��Ƿ�Ϊ�ɽ����ַ����������ֺ���ĸ��
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
bool validityCheck(const char *s)//�ж��ַ����Ϸ���
{
    if (strlen(s)>stringlen) {//�жϳ���
            cout<<"���ȳ�������\n";
            return false;
    }
    while (*s!='\0'){//�ж��ַ��Ƿ���Ч
        if (!(*s>='0' && *s<='9'|| *s>='a'&&* s<='z'||*s>='A' && *s<='Z'|| InAcpChar(s))) {
                cout<<*s<<"���ǿɽ����ַ�\n";
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
    bool sensitiveflag;//���д�����
    bool prevflag;//ǰһ��������
    bool usefulflag;//���÷�������
    bool filterflag=false;//������Ҫ����
    int i,j;
    char *p,*origin,*startPos,*stopPos;//���д�λ�õ�ָ��
    origin=s;//�����ʼλ��
    //Ѱ�����д�����ĸ
    while (*s!='\0'){
        sensitiveflag=false;//���д�����
        prevflag=false;//ǰһ�����ű��ҵ�
        usefulflag=false;
        for (i=0;i<sensitiveNum;++i){//����ÿһ�����д�
            if (compare(*s,sensitiveWord[i][0])){//����������д����ַ�
                sensitiveflag=true;
                prevflag=true;
                startPos=s;//����λ��
                break;
            }
        }
    if (!sensitiveflag) {
            ++s;
            continue;
            }//û�����д����ٹ���
    //Ѱ���������д�
    p=startPos+1;
    j=1;
    while(sensitiveWord[i][j]!='\0'&&prevflag){
        prevflag=false;
        while(*p!='\0'){
                if (compare(*p,sensitiveWord[i][j])){//�ҵ����дʵ���һλ
                    prevflag=true;
                    stopPos=p;
                    ++p;
                    break;
                }
                else {//���������ַ����ж��Ƿ�����
                    if (*p>='0' && *p<='9'|| *p>='a'&&* p<='z'||*p>='A' && *p<='Z') usefulflag=true;
                    for (int k=0;k<punctuationNum;++k)  if (*p==punctuation[k]) usefulflag=true;
                }
        ++p;
        }
        ++j;
    }
    if (!prevflag ){//û���ҵ��������дʣ��ж���һ�ַ�
            ++s;
            continue;
    }
     if (usefulflag) {//���˴��а������ôʻ㣬�ж���һ�ַ�
            ++s;
            continue;
    }
    if (!usefulflag) {
        strcpy(startPos,stopPos+1);//����
        filterflag=true;
        break;
        }
    ++s;
    }
    if (filterflag) filter(origin);//������������ݹ���ù��˺���
}
