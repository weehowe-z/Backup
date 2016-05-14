//21����Ϸ By Weehowe.z
//V14.4.6 ��ɻ������ܡ�
//V14.4.8 ����ʤ��ͳ��
//��һ��չ�� 1������AI���Ӹ������Ƽ�����ʴӶ������Լ��Ƿ�Ҫ�ơ�2��ҵ��������Ƚ�����Ϸ��3���ӳ����ע��4���ӻ���
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

void printInfo();//��ʾ��Ϸ��Ϣ
void play();
void shuffle();//ϴ��
void deal(int *num,float *point);//���ƣ�����ָ�봫�������͵����ĸı�
void display(int num);//������
void playerTurn();
void computerTurn();
void judge();//�ж�ʤ��

const string suits[4]={"����","����","÷��","����"};//���ַ������鱣�滨ɫ����������
const string ranks[13]={"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
const float points[13]={1,2,3,4,5,6,7,8,9,10,0.5,0.5,0.5};
bool cards[4][13];//�����ж�ĳ�����Ƿ��Ѿ�����ȡ
int hand[2][22];//���ڱ���������Ϣ�������Ͽ��Գ�ȡ22�Ųų���21��

int playerNum,computerNum;//����ȫ�ֱ�����ң�����������
float playerPoint,computerPoint;//����ȫ�ֱ�����ң����Ե÷�
int win=0,lose=0,tie=0;//����ȫ��ʤ������

int main()
{
    char answer='y';
    srand((unsigned)time(NULL));//��ʼ�����������
    printInfo();//��ʾ��Ϸ��Ϣ
    while (true){//���Ͻ�����Ϸ
        play();
        cout<<"\n�Ƿ����(y/n): ";
        cin>>answer;
        while(answer!='y'&&answer!='n'){//����������
                cout<<"�Բ���������������������y��n: ";
                cin>>answer;
        }
        if (answer=='n') break;//�ش�n���˳�
        cout<<endl;
    }
    cout.precision(3);//�趨���㾫��
    cout<<"\n��һ��Ӯ��"<<win<<"��/"<<win+lose+tie<<"��\t"<<"ʤ����"<<100.0*win/(win+lose+tie)<<"%"<<endl;//���ʤ��ͳ��
    cout<<"��л����ʹ�ã��ټ�!\n";
    return 0;
}
void printInfo()//��ʾ��Ϸ����
{
    cout<<"��ӭ����21����Ϸ��\t\t\tby Weehowe.z\n\n";
    cout<<"��Ϸ����\n";
    cout<<"һ��ʼ���������������ƣ����������Ƿ����Ҫ�ơ�\n";
    cout<<"Ŀ���ǵ�����21�㣬һ������21����䣡";
    cout<<"����JQK����0.5�㣬�����Ƶ��������������㡣\n";
    cout<<"���͵��Ի��Ⱥ����һ����Ϸ�������������������߻�ʤ��\n";
    cout<<"ף����Ϸ��죡\n\n";
    cout<<"----------------------------��Ϸ��ʼ�ˣ�---------------------------\n\n";
}
void play()
{
    playerNum=0;//��Ϸ��ʼ��ʼ��˫���÷ֺ�����
    playerPoint=0;
    computerNum=0;
    computerPoint=0;
    playerTurn();//������ҽ׶�
    if (playerPoint<=21) {//���δ���������Խ׶�
            computerTurn();
            if (computerPoint<=21) judge();//����δ�������ȽϽ׶�
    }
}
void playerTurn()//��ҽ׶�
{
    char answer='y';
    cout<<"��ҽ׶�\n";
    cout<<"��һ����\t";
    shuffle();//ϴ��
    deal(&playerNum,&playerPoint);//����
    deal(&playerNum,&playerPoint);
    display(playerNum);//����
    while (true){//�����ж�
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
         if (playerPoint>21){//����21��ͽ���
                cout<<"\n�������\n";
                ++lose;
                break;
         }
    }
}
void computerTurn()//���Խ׶�
{
    cout<<"\n���Խ׶�\n";
    cout<<"���Ի����\t";
    shuffle();
    deal(&computerNum,&computerPoint);
    deal(&computerNum,&computerPoint);
    display(computerNum);
    //AI���ԭ�򣺾�����ʤ���Ǹպ�Ӯ������Ҿ����֡���Ҳ����ƽ��ʱ���֡�
    //��Ŀ�����˼�����ǵ���ֻ��Ӯ���䣬ƽ��ҲҪ���ƶ�ʤ�����о���̫�����������޸ġ�
    //1����������С��������Խ׶ε���������<=21�֣���������ơ�
    //2������������ͬ����������������������ơ�
    //3������ǡ��21�㲻���ơ������ȣ�
    //4���������˴󣨻�ʤ�������ơ�
    //5��������ͬ������������ͬ��ƽ�֣������ơ�
    //6��������ͬ���������˴󣨻�ʤ��������
    while ((computerPoint<playerPoint)||(computerPoint==playerPoint&&computerNum<playerNum&&computerPoint!=21)){
        cout<<"����Ҫһ����:\t";
        deal(&computerNum,&computerPoint);
        display(computerNum);
         if (computerPoint>21){//����21����˳�
                cout<<"\n���Ӯ��\n";
                ++win;
                break;
         }
    }
}
void shuffle()//ϴ��
{
    int i,j;
    for (i=0;i<=3;++i){//�����߼�����
        for (j=0;j<=12;++j) cards[i][j]=true;
    }
    for (i=0;i<=1;++i){//������������
        for (j=0;j<=22;++j) hand[i][j]=0;
    }
}
void deal(int *num,float *point)//���ƣ���ָ�봫�������͵����ĸı䣩
{
    int suit,rank;
    while(true){
        suit=4*rand()/(RAND_MAX+1);//�����ȡ��ɫ
        rank=13*rand()/(RAND_MAX+1);//�����ȡ����
        if (cards[suit][rank]){//���������û�б�������߼������ӦԪ��Ϊtrue)������Ƴɹ�
            cards[suit][rank]=false;
            break;
        }
    }
    hand[0][*num]=suit;//�����������һ���м�¼���ƻ�ɫ
    hand[1][*num]=rank;//����������ڶ����м�¼���Ƶ���
    *point+=points[rank];//�÷�����
    ++*num;//������������
}
void display(int num)//չʾ����
{
    for (int i=0;i<num;i++)//������������չʾ����
        cout<<suits[hand[0][i]]<<" "<<ranks[hand[1][i]]<<" ";
    cout<<endl;
}
void judge()//�ж�ʤ��
{
    //��AI���߼��������ܻ���ֵ÷ֱ����С�����
    if (playerPoint<computerPoint) {cout<<"\n�������\n";++lose;}
    if (computerPoint==playerPoint &&computerNum>playerNum) {cout<<"\n�������\n";++lose;}
    if (computerPoint==playerPoint &&computerNum<playerNum) {cout<<"\n���Ӯ��\n";++win;}//�����ܳ�����˫��21������
    if (computerPoint==playerPoint &&computerNum==playerNum) {cout<<"\nƽ��\n";++tie;}//�����ܳ�����AI�趨����ƽ�ֵ����
}
