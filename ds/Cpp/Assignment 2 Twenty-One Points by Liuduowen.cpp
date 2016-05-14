#include <iostream>
#include<cstring>
#include<ctime>
#include<cstdlib>
using namespace std;
struct Node{
    int type;
    int num;
    Node *next;
};
int card[4][13];double hump=0,comp=0;int humc=0,comc=0;
double givecard(Node *rear);void initializeCard();void printcard(Node *head,Node *rear);int humdead();int comdead();
int main()
{
    char answer,help[5];int win=0;Node *head,*head1,*rear,*rear1,*p,*p1;
    srand(time(NULL));
    initializeCard();//ϴ��
    head=rear=p=new Node;//��������洢������õ�����
    cout<<"*************************************\n";
    cout<<"    ^_^ ��ӭ����������Ϸ21��! ^_^    \n";
    cout<<"*************************************\n";
    cout<<"��Ҫ��ʼ��Ϸ��������y����Ҫ�鿴��Ϸ����������help :";
    cin>>help;
    if (strlen(help)==4) cout<<"\n��Ϸ����:���ֻ�ɫ��AΪ1�㣬J,Q,KΪ0.5�㣬���ఴ������ֵ�����\n��û�г���21�������£�����Խ��Խ�ã�ͬ����ʱ����Խ��Խ��\n������21������ʧ��!\n\n";
    cout<<"��ҽ׶�"<<endl;
    cout<<"��һ����: ";
    hump+=givecard(rear);
    rear=rear->next;       //ά������
    hump+=givecard(rear);
    rear=rear->next;
    humc+=2;
    cout<<"\n�Ƿ����Ҫ��(y/n):";
    cin>>answer;
    while (answer=='y') {      //����ѭ��ѯ������Ƿ�Ҫ��
        cout<<"����Ҫһ����: ";
        printcard(head,rear);
        hump+=givecard(rear);
        rear=rear->next;
        ++humc;
        if (humdead()) {cout<<"\n�������"; break;}
        cout<<"\n�Ƿ����Ҫ��(y/n):";
        cin>>answer;
    }
    if (!humdead()){         //������û������ʼ���Խ׶Σ����������ֱ�ӽ�����Ϸ
    initializeCard();
    head1=rear1=p1=new Node;
    cout<<"\n���Խ׶�";
    cout<<"\n���Ի����: ";
    comp+=givecard(rear1);
    rear1=rear1->next;
    comp+=givecard(rear1);
    rear1=rear1->next;
    comc+=2;
    while(comp<hump || (comp==hump && comc<=humc)){   //ֻҪ����û������û��Ӯ����ң������Ҫ��
        cout<<"\n����Ҫһ����: ";
        printcard(head1,rear1);
        comp+=givecard(rear1);
        rear1=rear1->next;
        ++comc;
        if (comdead()) {cout<<"\n���Ӯ��";win=1; break;}

    }
    if (win!=1) cout<<"\n�������";
    }
    return 0;

}

double givecard(Node *rear)    //���ƺ���
{
    int i,j;double point;Node *p;
    i=rand()%4;j=rand()%13;
    while (card[i][j]==0){
    i=rand()%4;j=rand()%13;
    }
    card[i][j]=0;
    p=new Node;
    p->type=i;
    p->num=j;
    rear->next=p;
    rear=p;
    rear->next=NULL;
    switch(i){
        case 0: cout<<"����";break;
        case 1: cout<<"����";break;
        case 2: cout<<"÷��";break;
        case 3: cout<<"��Ƭ";break;
    }
    switch(j){
        case 0:cout<<'A'<<' ';point=1;break;
        case 10:cout<<'J'<<' ';point=0.5;break;
        case 11:cout<<'Q'<<' ';point=0.5;break;
        case 12:cout<<'K'<<' ';point=0.5;break;
        default:cout<<++j<<' ';point=j;break;
    }
    return point;
}

void initializeCard()    //ϴ�ƺ���
{
    int i,j;
    for (i=0;i<4;++i){
        for (j=0;j<13;++j)  card[i][j]=1;
    }
    }

void printcard(Node *head,Node *rear)  //��ӡ��һ��ߵ����Ѿ��е���
{
    Node *p;
    p=head->next;
    while(p!=NULL){
                switch(p->type){
                    case 0: cout<<"����";break;
                    case 1: cout<<"����";break;
                    case 2: cout<<"÷��";break;
                    case 3: cout<<"��Ƭ";break;
                }
                switch(p->num){
                    case 0:cout<<'A'<<' ';break;
                    case 10:cout<<'J'<<' ';break;
                    case 11:cout<<'Q'<<' ';break;
                    case 12:cout<<'K'<<' ';break;
                    default:cout<<p->num+1<<' ';break;
                }
                p=p->next;
            }



}

int humdead()    //�ж�����Ƿ�����
{
    if (hump>21) return 1;
    else return 0;
}

int comdead()    //�жϵ����Ƿ�����
{
    if (comp>21) return 1;
    else return 0;
}

