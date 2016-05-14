#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int getInput();
void printInfo();
void play();
int main()
{
    printInfo();
    play();
    return 0;
}
int getInput()
{
    int answer;
    while (true){
        cout<<"Head Side(0) or Tail Side(1)? £º";
        cin>>answer;
        if ((answer==0)||(answer==1)||(answer==-1)) break;
        cout<<"Please input 0 or 1(or -1 to quit)!\n\n";
    }
    return answer;
}

void printInfo()
{
    cout<<"Happy Coins Game!\n";
    cout<<"By Weehowe.z 2014.4.2\n\n";
    cout<<"I'will throw a coin and you have to guess wheather it is the head or tail.\n";
    cout<<"If you're right, you win, otherwise I win!\n";
    cout<<"Also You can input -1 to quit.\n";
    cout<<"So let's begin!\n\n";
}
void play()
{
    int coin,answer;
    int lose=0,win=0;
    srand(time(NULL));
    while (true){
        coin=rand()*2/(RAND_MAX+1);
        answer =getInput();
        if (answer==-1) {
                cout<<"Your winning rate is "<<float(win)/(win+lose)<<endl;
                cout<<"\nThank you for using!\n";
                break;
                }
        if (answer==coin){
                cout<<"You Win!\n\n";
                win++;
        }
            else{
                cout<<"I win!\n\n";
                lose++;
        }
    }
}
