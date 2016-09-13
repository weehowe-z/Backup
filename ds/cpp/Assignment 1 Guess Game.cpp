//数字猜谜游戏 by Weehowe.z
//游戏规则：
//1、游戏开始，电脑随机生成三个不重复的十以内的数字。
//2、玩家输入他所猜测的三个数字。
//3、将玩家提交的数与电脑生成的数进行比较，结果显示成"*A*B"。A代表位置正确数，字也正确，B代表数字正确但位置不正确。
//4、玩家共有7次机会，在7次内，如果结果为“3A0B”，游戏成功，退出游戏。如果7次里玩家都没有猜对游戏失败。
//V14.3.9  完成基本功能。
//V14.3.11 1增加输入数字是否在0到9内的判断。2增加输入数字是否相同的判断。
//v14.3.13 增加防闪退
//下一版展望 增加输入字母报错的异常捕获。可视化

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()
{
    int i,j,A,B,num1[3],num2[3],life=7;
    srand(time(NULL));//初始化随机种子
    while (true){
        for (i=0;i<=2;i++) {
            num1[i]=rand()*10/(RAND_MAX+1);//生成三个随机数字
            }
        if (num1[0]!=num1[1] && num1[1]!=num1[2] && num1[2]!=num1[0]) break;//判断3个数字不重复则跳出循环重新生成
        }
    while (life>0){
            A=B=0;
            while (true){
                    cout<<"请输入你猜测的数字: ";
                    cin>>num2[0]>>num2[1]>>num2[2];
                    if ((num2[0]<0 || num2[0]>9)||(num2[1]<0 || num2[1]>9)||(num2[1]<0 || num2[1]>9)) {//判断是否在0到9之间
                            cout<<"请输入0到9之间的数字！\n\n";
                            continue;
                            }
                    if (num2[0]==num2[1] || num2[1]==num2[2] || num2[2]==num2[0]){//判断三个数字是否相同
                            cout<<"请输入三个不同的数字！\n\n";
                            continue;
                            }
                    break;//输入的数字没有问题则跳出循环
            }

            for (i=0;i<=2;i++){            //两个循环嵌套从而比较每个数字
                for (j=0;j<=2;j++){
                    if (num1[i]==num2[j] && i==j) {A++;break;}//相同位置数字相等 A+1，一旦得到结果就跳出，减少一层循环
                    if (num1[i]==num2[j] && i!=j) {B++;break;}//不同位置数字相等 B+1，一旦得到结果就跳出，减少一层循环
                    }
                }
            if (A==3) {cout<<"恭喜，你猜对了！！\n";break;}
            else {
                cout<<A<<"A"<<B<<"B\n";
                life--;
                if (life==0) cout<<"很遗憾，你没有在规定次数内猜对。答案是 "<<num1[0]<<num1[1]<<num1[2]<<endl;
                }
            }
            cin>>life;//防闪退。
            return 0;
}
