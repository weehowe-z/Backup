//Money Change
//V2014.3.20
#include <iostream>
using namespace std;
void makechange(int coins[],int coinUsed[],int moneyChange);
int main()
{
    int coins[5]={1,5,10,21,25},moneyChange;
    cout<<"Please enter the money: ";
    cin>>moneyChange;
    int coinUsed[100]={0};
    makechange(coins,coinUsed,moneyChange);
    return  0;
}
void makechange(int coins[],int coinUsed[],int moneyChange)
{
    int cents,minCoins,i;;
    for (cents=1;cents<=moneyChange;cents++){//遍历不超过找零的所有情况并保存
        minCoins=cents;//全部使用1分钱的情况
        for (i=1;i<5;i++){//size函数获得数组长度，遍历所有种类的钱
            if (coins[i]>cents) continue;//最小面值也无法完成找零则退出
            if (coinUsed[cents-coins[i]]+1 < minCoins) minCoins=coinUsed[cents-coins[i]]+1;
        }
        coinUsed[cents]=minCoins;//保存其找零情况
    }
    cout<<"Total coins: "<<coinUsed[cents-1]<<endl;
    cout<<"Thanks for using!"<<endl;
}

