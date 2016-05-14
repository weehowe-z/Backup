//Auto-Four Arithmetic Operations
//By Weehowe.z
//V14.3.2.1 完成基础功能
//V14.3.8.1 修改除法运算,增加循环
//V14.3.8.2 加入计数器,生命值
//V14.4.3.1 模块化重构，随机用户回答
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
void winMessage();
void loseMessage();
void play();
int main()
{
    play();
    return 0;
}
void play()
{
    int type,num1,num2,result,point=0,life=3;
    srand(time(NULL));// initialize random
    while (true){
            type = rand()*4/(RAND_MAX+1);
            num1 = rand()*9/(RAND_MAX+1)+1;
            num2 = rand()*9/(RAND_MAX+1)+1;
            switch (type)
            {

                case 0:
                    cout<<num1<<" + "<<num2<<" = ";cin>>result;
                    if (num1+num2 == result) {
                            winMessage();
                            point++;
                            }
                        else {
                            loseMessage();
                            cout<<num1+num2<<endl<<endl;
                            life--;
                            break;
                            }
                case 1:
                    if ((num1-num2) <0) break;//abandon if minis 0
                    cout<<num1<<" - "<<num2<<" = ";cin>>result;
                    if (num1-num2 == result) {
                            winMessage();
                            point++;
                            }
                        else {
                            loseMessage();
                            cout<<num1-num2<<endl<<endl;
                            life--;
                            break;
                            }
                case 2:
                    cout<<num1<<" * "<<num2<<" = ";cin>>result;
                    if (num1*num2 == result) {
                            winMessage();
                            point++;
                            }
                        else {
                            loseMessage();
                            cout<<num1*num2<<endl<<endl;
                            life--;
                            break;
                            }
                case 3:
                    if (num1%num2 !=0) break;//abandon if not exact division
                    cout<<num1<<" / "<<num2<<" = ";cin>>result;
                    if (num1/num2 == result) {
                            winMessage();
                            point++;
                            }
                        else {
                            loseMessage();
                            cout<<num1/num2<<endl<<endl;
                            life--;
                            break;
                            }
            }
            if (life==0) {
                cout<<"Game over.\nYou have won "<<point<<"p\n";
                break;
            }
    }
}
void winMessage()
{
    int way;
    way=rand()*3/(RAND_MAX+1);
    switch (way)
    {
        case 0:cout<<"Congratulation! You're right!\n\n";break;
        case 1:cout<<"Ok! You got it!\n\n";break;
        case 2:cout<<"Excellent!You win!\n\n";break;
        case 3:cout<<"You did it!\n\n";break;
    }
}
void loseMessage()
{
    int way;
    way=rand()*3/(RAND_MAX+1);
    switch (way)
    {
        case 0:cout<<"What a pity! You're wrong!\nThe right answer is ";break;
        case 1:cout<<"Sorry you are wrong!\nThe right answer is ";break;
        case 2:cout<<"You fail to get it!\nThe right answer is ";break;
        case 3:cout<<"You are not right!\nThe right answer is ";break;
    }
}
