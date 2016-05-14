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
    initializeCard();//洗牌
    head=rear=p=new Node;//创建链表存储玩家所得到的牌
    cout<<"*************************************\n";
    cout<<"    ^_^ 欢迎来到益智游戏21点! ^_^    \n";
    cout<<"*************************************\n";
    cout<<"若要开始游戏，请输入y，若要查看游戏规则请输入help :";
    cin>>help;
    if (strlen(help)==4) cout<<"\n游戏规则:不分花色，A为1点，J,Q,K为0.5点，其余按牌面数值算点数\n在没有超过21点的情况下，分数越高越好，同分数时，牌越多越好\n若超过21点则算失败!\n\n";
    cout<<"玩家阶段"<<endl;
    cout<<"玩家获得牌: ";
    hump+=givecard(rear);
    rear=rear->next;       //维护链表
    hump+=givecard(rear);
    rear=rear->next;
    humc+=2;
    cout<<"\n是否继续要牌(y/n):";
    cin>>answer;
    while (answer=='y') {      //不断循环询问玩家是否要牌
        cout<<"继续要一张牌: ";
        printcard(head,rear);
        hump+=givecard(rear);
        rear=rear->next;
        ++humc;
        if (humdead()) {cout<<"\n玩家输了"; break;}
        cout<<"\n是否继续要牌(y/n):";
        cin>>answer;
    }
    if (!humdead()){         //如果玩家没有死则开始电脑阶段，如果死了则直接结束游戏
    initializeCard();
    head1=rear1=p1=new Node;
    cout<<"\n电脑阶段";
    cout<<"\n电脑获得牌: ";
    comp+=givecard(rear1);
    rear1=rear1->next;
    comp+=givecard(rear1);
    rear1=rear1->next;
    comc+=2;
    while(comp<hump || (comp==hump && comc<=humc)){   //只要电脑没死并且没有赢过玩家，则继续要牌
        cout<<"\n继续要一张牌: ";
        printcard(head1,rear1);
        comp+=givecard(rear1);
        rear1=rear1->next;
        ++comc;
        if (comdead()) {cout<<"\n玩家赢了";win=1; break;}

    }
    if (win!=1) cout<<"\n玩家输了";
    }
    return 0;

}

double givecard(Node *rear)    //发牌函数
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
        case 0: cout<<"黑桃";break;
        case 1: cout<<"红桃";break;
        case 2: cout<<"梅花";break;
        case 3: cout<<"方片";break;
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

void initializeCard()    //洗牌函数
{
    int i,j;
    for (i=0;i<4;++i){
        for (j=0;j<13;++j)  card[i][j]=1;
    }
    }

void printcard(Node *head,Node *rear)  //打印玩家或者电脑已经有的牌
{
    Node *p;
    p=head->next;
    while(p!=NULL){
                switch(p->type){
                    case 0: cout<<"黑桃";break;
                    case 1: cout<<"红桃";break;
                    case 2: cout<<"梅花";break;
                    case 3: cout<<"方片";break;
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

int humdead()    //判断玩家是否死亡
{
    if (hump>21) return 1;
    else return 0;
}

int comdead()    //判断电脑是否死亡
{
    if (comp>21) return 1;
    else return 0;
}

