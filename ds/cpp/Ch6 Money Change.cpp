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
    for (cents=1;cents<=moneyChange;cents++){//����������������������������
        minCoins=cents;//ȫ��ʹ��1��Ǯ�����
        for (i=1;i<5;i++){//size����������鳤�ȣ��������������Ǯ
            if (coins[i]>cents) continue;//��С��ֵҲ�޷�����������˳�
            if (coinUsed[cents-coins[i]]+1 < minCoins) minCoins=coinUsed[cents-coins[i]]+1;
        }
        coinUsed[cents]=minCoins;//�������������
    }
    cout<<"Total coins: "<<coinUsed[cents-1]<<endl;
    cout<<"Thanks for using!"<<endl;
}

