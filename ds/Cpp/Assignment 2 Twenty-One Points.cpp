//21点游戏 By Weehowe.z
//V14.4.6 完成基本功能。
//V14.4.8 增加胜率统计
//下一版展望 1、电脑AI增加根据手牌计算概率从而决定自己是否要牌。2玩家电脑轮流先进行游戏。3增加筹码赌注。4可视化。
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

void printInfo();//显示游戏信息
void play();
void shuffle();//洗牌
void deal(int *num,float *point);//摸牌，并用指针传递牌数和点数的改变
void display(int num);//看手牌
void playerTurn();
void computerTurn();
void judge();//判断胜负

const string suits[4]={"黑桃","红桃","梅花","方块"};//用字符串数组保存花色点数的名称
const string ranks[13]={"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
const float points[13]={1,2,3,4,5,6,7,8,9,10,0.5,0.5,0.5};
bool cards[4][13];//用来判断某张牌是否已经被抽取
int hand[2][22];//用于保存手牌信息，理论上可以抽取22张才超过21点

int playerNum,computerNum;//定义全局变量玩家，电脑手牌数
float playerPoint,computerPoint;//定义全局变量玩家，电脑得分
int win=0,lose=0,tie=0;//定义全局胜负数量

int main()
{
    char answer='y';
    srand((unsigned)time(NULL));//初始化随机数种子
    printInfo();//显示游戏信息
    while (true){//不断进行游戏
        play();
        cout<<"\n是否继续(y/n): ";
        cin>>answer;
        while(answer!='y'&&answer!='n'){//检测输入错误
                cout<<"对不起您的输入有误，请输入y或n: ";
                cin>>answer;
        }
        if (answer=='n') break;//回答n则退出
        cout<<endl;
    }
    cout.precision(3);//设定浮点精度
    cout<<"\n您一共赢了"<<win<<"次/"<<win+lose+tie<<"局\t"<<"胜率是"<<100.0*win/(win+lose+tie)<<"%"<<endl;//输出胜率统计
    cout<<"感谢您的使用，再见!\n";
    return 0;
}
void printInfo()//显示游戏规则
{
    cout<<"欢迎来到21点游戏！\t\t\tby Weehowe.z\n\n";
    cout<<"游戏规则：\n";
    cout<<"一开始您会随机获得两张牌，由您决定是否继续要牌。\n";
    cout<<"目标是点数是21点，一旦超过21点就输！";
    cout<<"除了JQK都是0.5点，数字牌点数按照数字来算。\n";
    cout<<"您和电脑会先后进行一轮游戏，点数更大，牌数更少者获胜。\n";
    cout<<"祝您游戏愉快！\n\n";
    cout<<"----------------------------游戏开始了！---------------------------\n\n";
}
void play()
{
    playerNum=0;//游戏开始初始化双方得分和手牌
    playerPoint=0;
    computerNum=0;
    computerPoint=0;
    playerTurn();//进入玩家阶段
    if (playerPoint<=21) {//玩家未爆则进入电脑阶段
            computerTurn();
            if (computerPoint<=21) judge();//电脑未爆则进入比较阶段
    }
}
void playerTurn()//玩家阶段
{
    char answer='y';
    cout<<"玩家阶段\n";
    cout<<"玩家获得牌\t";
    shuffle();//洗牌
    deal(&playerNum,&playerPoint);//摸牌
    deal(&playerNum,&playerPoint);
    display(playerNum);//看牌
    while (true){//输入判断
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
         if (playerPoint>21){//超过21点就结束
                cout<<"\n玩家输了\n";
                ++lose;
                break;
         }
    }
}
void computerTurn()//电脑阶段
{
    cout<<"\n电脑阶段\n";
    cout<<"电脑获得牌\t";
    shuffle();
    deal(&computerNum,&computerPoint);
    deal(&computerNum,&computerPoint);
    display(computerNum);
    //AI设计原则：尽量获胜，是刚好赢人类玩家就收手。但也接受平局时收手。
    //题目里的意思可能是电脑只有赢和输，平局也要抽牌赌胜利，感觉不太合理，故做此修改。
    //1、点数比人小（进入电脑阶段的条件是人<=21分）则继续抽牌。
    //2、点数和人相同但是牌数比人少则继续抽牌。
    //3、点数恰好21点不抽牌。（优先）
    //4、点数比人大（获胜）不抽牌。
    //5、点数相同且牌数和人相同（平局）不抽牌。
    //6、点数相同且牌数比人大（获胜）不抽牌
    while ((computerPoint<playerPoint)||(computerPoint==playerPoint&&computerNum<playerNum&&computerPoint!=21)){
        cout<<"继续要一张牌:\t";
        deal(&computerNum,&computerPoint);
        display(computerNum);
         if (computerPoint>21){//超过21点就退出
                cout<<"\n玩家赢了\n";
                ++win;
                break;
         }
    }
}
void shuffle()//洗牌
{
    int i,j;
    for (i=0;i<=3;++i){//重置逻辑数组
        for (j=0;j<=12;++j) cards[i][j]=true;
    }
    for (i=0;i<=1;++i){//重置手牌数组
        for (j=0;j<=22;++j) hand[i][j]=0;
    }
}
void deal(int *num,float *point)//抽牌（用指针传递牌数和点数的改变）
{
    int suit,rank;
    while(true){
        suit=4*rand()/(RAND_MAX+1);//随机抽取花色
        rank=13*rand()/(RAND_MAX+1);//随机抽取点数
        if (cards[suit][rank]){//如果这张牌没有被抽过（逻辑数组对应元素为true)，则抽牌成功
            cards[suit][rank]=false;
            break;
        }
    }
    hand[0][*num]=suit;//在手牌数组第一行中记录卡牌花色
    hand[1][*num]=rank;//在手牌数组第二行中记录卡牌点数
    *point+=points[rank];//得分增加
    ++*num;//手牌数量增加
}
void display(int num)//展示手牌
{
    for (int i=0;i<num;i++)//从手牌数组中展示手牌
        cout<<suits[hand[0][i]]<<" "<<ranks[hand[1][i]]<<" ";
    cout<<endl;
}
void judge()//判断胜负
{
    //由AI的逻辑，不可能会出现得分比玩家小的情况
    if (playerPoint<computerPoint) {cout<<"\n玩家输了\n";++lose;}
    if (computerPoint==playerPoint &&computerNum>playerNum) {cout<<"\n玩家输了\n";++lose;}
    if (computerPoint==playerPoint &&computerNum<playerNum) {cout<<"\n玩家赢了\n";++win;}//仅可能出现在双方21点的情况
    if (computerPoint==playerPoint &&computerNum==playerNum) {cout<<"\n平局\n";++tie;}//仅可能出现在AI设定接受平局的情况
}
