//21点游戏 By Weehowe.z
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

void printInfo();//显示游戏信息
void play();
void shuffle();//洗牌
void deal(int *num,float *point);//用指针传递牌数和点数的改变
void display(int num);//看牌,看总点数
void playerTurn();
void computerTurn();
void judge();

const string suits[4]={"黑桃","红桃","梅花","方块"};
const string ranks[13]={"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
const float points[13]={1,2,3,4,5,6,7,8,9,10,0.5,0.5,0.5};
bool cards[4][13];//用来判断某张牌是否已经被抽取

int playerNum,computerNum;//定义玩家，电脑手牌数
float playerPoint,computerPoint;//玩家，电脑得分
int **hand;//申请两行两列的动态数组，用以保存手牌信息

int main()
{
    int x;
    char answer='y';
    srand((unsigned)time(NULL));//初始化随机数种子
    //x=rand()/(RAND_MAX+1);
    printInfo();
    while (true){
        cout<<endl;
        play();
        cout<<"\n是否继续(y/n): ";
        cin>>answer;
        while(answer!='y'&&answer!='n'){
                cout<<"对不起您的输入有误，请输入y或n: ";
                cin>>answer;
        }
        if (answer=='n') break;
    }
    return 0;
}
void printInfo()
{
    cout<<"欢迎来到21点游戏!\n";
    cout<<"一开始您会随机获得两张牌，由您决定是否继续要牌.\n";
    cout<<"目标是点数是恰好21点，数字牌点数按照数字来算，JQK都是0.5点.\n";
    cout<<"您和电脑会分别进行一轮游戏，点数大，牌数少者胜.\n";
    cout<<"祝您游戏愉快!\n\n";
}
void  play()
{
    playerNum=0;//游戏开始初始化双方得分和手牌
    playerPoint=0;
    computerNum=0;
    computerPoint=0;
    hand=new int *[2];//申请指向每一行首地址的指针
    hand[0]=new int[15];
    hand[1]=new int[15];
    playerTurn();
    if (playerPoint<=21) {
            computerTurn();
            if (computerPoint<=21) judge();
    }
    delete [] hand[0];//释放空间
    delete [] hand[1];
    delete [] hand;
}
void playerTurn()
{
    char answer='y';
    cout<<"玩家阶段\n";
    cout<<"玩家获得牌\t";
    shuffle();
    deal(&playerNum,&playerPoint);
    deal(&playerNum,&playerPoint);
    display(playerNum);
    while (true){
        cout<<"是否继续要牌(y/n): ";
        cin>>answer;
        while(answer!='y'&&answer!='n'){
                cout<<"对不起您的输入有误，请输入y或n: ";
                cin>>answer;
        }
        if (answer=='n') break;
        cout<<"继续要一张牌:\t";
        deal(&playerNum,&playerPoint);
        display(playerNum);
         if (playerPoint>21){
                cout<<"\n玩家输了\n";
                break;
         }
    }
}
void computerTurn()
{
    cout<<"\n电脑阶段\n";
    cout<<"电脑获得牌\t";
    shuffle();
    deal(&computerNum,&computerPoint);
    deal(&computerNum,&computerPoint);
    display(computerNum);
    while ((computerPoint<playerPoint)||(computerPoint==playerPoint&&computerNum<playerNum&&computerPoint!=21)){//点数不够或者点数相同牌数不大于人类均继续抽牌。
        cout<<"继续要一张牌:\t";
        deal(&computerNum,&computerPoint);
        display(computerNum);
         if (computerPoint>21){
                cout<<"\n玩家赢了\n";
                break;
         }
    }
}
void shuffle()//洗牌
{
    for (int i=0;i<=3;i++){
        for (int j=0;j<=12;j++) cards[i][j]=true;
    }
    delete [] hand[0];
    delete [] hand[1];
    delete [] hand;
    hand=new int *[2];//申请指向每一行首地址的指针
    hand[0]=new int[15];
    hand[1]=new int[15];
}
void deal(int *num,float *point)//抽牌
{
    int suit,rank;
    while(true){
        suit=4*rand()/(RAND_MAX+1);//随机抽取花色
        rank=13*rand()/(RAND_MAX+1);//随机抽取点数
        if (cards[suit][rank]){//如果这张牌没有被抽过，则抽拍成功
            cards[suit][rank]=false;
            break;
        }
    }
    hand[0][*num]=suit;//在手牌数组第一行中记录卡牌花色
    hand[1][*num]=rank;//在手牌数组第二行中记录卡牌点数
    *point+=points[rank];//得分增加
    ++*num;//手牌数量+1
}
void display(int num)//展示手牌
{
    for (int i=0;i<num;i++)
        cout<<suits[hand[0][i]]<<" "<<ranks[hand[1][i]]<<" ";
    cout<<endl;
}
void judge()
{
    //由AI的逻辑，不可能会出现得分比玩家小的情况
    if (playerPoint<computerPoint) cout<<"\n玩家输了\n";
    if (computerPoint==playerPoint &&computerNum>playerNum) cout<<"\n玩家输了\n";
    if (computerPoint==playerPoint &&computerNum<playerNum) cout<<"\n玩家赢了\n";
    if (computerPoint==playerPoint &&computerNum==playerNum) cout<<"\n平局\n";
}
