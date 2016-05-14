//Mark CHANGE
//By Weehowe.z 2014.3.2 Ver 1.0
#include <iostream>
using namespace std;
int main()
{
    int score;
    char grade;
    cout<<"Your score: ";
    cin>>score;
    switch(score/10)
    {
        case 10:;
        case 9: grade='A';break;
        case 8: grade='B';break;
        case 7: grade='C';break;
        case 6: grade='D';break;
        default: grade='E';
    }
    cout<<"Your Grade is "<<grade<<endl;
    if (grade == 'E') cout<<"What a pity!"<<endl;
    return 0;
}

