//21����Ϸ By Weehowe.z
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

void printInfo();//��ʾ��Ϸ��Ϣ
void play();
void shuffle();//ϴ��
void deal(int *num,float *point);//��ָ�봫�������͵����ĸı�
void display(int num);//����,���ܵ���
void playerTurn();
void computerTurn();
void judge();

const string suits[4]={"����","����","÷��","����"};
const string ranks[13]={"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
const float points[13]={1,2,3,4,5,6,7,8,9,10,0.5,0.5,0.5};
bool cards[4][13];//�����ж�ĳ�����Ƿ��Ѿ�����ȡ

int playerNum,computerNum;//������ң�����������
float playerPoint,computerPoint;//��ң����Ե÷�
int **hand;//�����������еĶ�̬���飬���Ա���������Ϣ

int main()
{
    int x;
    char answer='y';
    srand((unsigned)time(NULL));//��ʼ�����������
    //x=rand()/(RAND_MAX+1);
    printInfo();
    while (true){
        cout<<endl;
        play();
        cout<<"\n�Ƿ����(y/n): ";
        cin>>answer;
        while(answer!='y'&&answer!='n'){
                cout<<"�Բ���������������������y��n: ";
                cin>>answer;
        }
        if (answer=='n') break;
    }
    return 0;
}
void printInfo()
{
    cout<<"��ӭ����21����Ϸ!\n";
    cout<<"һ��ʼ���������������ƣ����������Ƿ����Ҫ��.\n";
    cout<<"Ŀ���ǵ�����ǡ��21�㣬�����Ƶ��������������㣬JQK����0.5��.\n";
    cout<<"���͵��Ի�ֱ����һ����Ϸ����������������ʤ.\n";
    cout<<"ף����Ϸ���!\n\n";
}
void  play()
{
    playerNum=0;//��Ϸ��ʼ��ʼ��˫���÷ֺ�����
    playerPoint=0;
    computerNum=0;
    computerPoint=0;
    hand=new int *[2];//����ָ��ÿһ���׵�ַ��ָ��
    hand[0]=new int[15];
    hand[1]=new int[15];
    playerTurn();
    if (playerPoint<=21) {
            computerTurn();
            if (computerPoint<=21) judge();
    }
    delete [] hand[0];//�ͷſռ�
    delete [] hand[1];
    delete [] hand;
}
void playerTurn()
{
    char answer='y';
    cout<<"��ҽ׶�\n";
    cout<<"��һ����\t";
    shuffle();
    deal(&playerNum,&playerPoint);
    deal(&playerNum,&playerPoint);
    display(playerNum);
    while (true){
        cout<<"�Ƿ����Ҫ��(y/n): ";
        cin>>answer;
        while(answer!='y'&&answer!='n'){
                cout<<"�Բ���������������������y��n: ";
                cin>>answer;
        }
        if (answer=='n') break;
        cout<<"����Ҫһ����:\t";
        deal(&playerNum,&playerPoint);
        display(playerNum);
         if (playerPoint>21){
                cout<<"\n�������\n";
                break;
         }
    }
}
void computerTurn()
{
    cout<<"\n���Խ׶�\n";
    cout<<"���Ի����\t";
    shuffle();
    deal(&computerNum,&computerPoint);
    deal(&computerNum,&computerPoint);
    display(computerNum);
    while ((computerPoint<playerPoint)||(computerPoint==playerPoint&&computerNum<playerNum&&computerPoint!=21)){//�����������ߵ�����ͬ����������������������ơ�
        cout<<"����Ҫһ����:\t";
        deal(&computerNum,&computerPoint);
        display(computerNum);
         if (computerPoint>21){
                cout<<"\n���Ӯ��\n";
                break;
         }
    }
}
void shuffle()//ϴ��
{
    for (int i=0;i<=3;i++){
        for (int j=0;j<=12;j++) cards[i][j]=true;
    }
    delete [] hand[0];
    delete [] hand[1];
    delete [] hand;
    hand=new int *[2];//����ָ��ÿһ���׵�ַ��ָ��
    hand[0]=new int[15];
    hand[1]=new int[15];
}
void deal(int *num,float *point)//����
{
    int suit,rank;
    while(true){
        suit=4*rand()/(RAND_MAX+1);//�����ȡ��ɫ
        rank=13*rand()/(RAND_MAX+1);//�����ȡ����
        if (cards[suit][rank]){//���������û�б����������ĳɹ�
            cards[suit][rank]=false;
            break;
        }
    }
    hand[0][*num]=suit;//�����������һ���м�¼���ƻ�ɫ
    hand[1][*num]=rank;//����������ڶ����м�¼���Ƶ���
    *point+=points[rank];//�÷�����
    ++*num;//��������+1
}
void display(int num)//չʾ����
{
    for (int i=0;i<num;i++)
        cout<<suits[hand[0][i]]<<" "<<ranks[hand[1][i]]<<" ";
    cout<<endl;
}
void judge()
{
    //��AI���߼��������ܻ���ֵ÷ֱ����С�����
    if (playerPoint<computerPoint) cout<<"\n�������\n";
    if (computerPoint==playerPoint &&computerNum>playerNum) cout<<"\n�������\n";
    if (computerPoint==playerPoint &&computerNum<playerNum) cout<<"\n���Ӯ��\n";
    if (computerPoint==playerPoint &&computerNum==playerNum) cout<<"\nƽ��\n";
}
