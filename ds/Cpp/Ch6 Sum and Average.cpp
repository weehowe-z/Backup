//统计平均分
#include <iostream>
using namespace std;
int average(int array[10]);
int main()
{
    int grade[10],i;
    cout<<"Please enter 10 students' grade.\n";
    for (i=0;i<=9;i++) cin>>grade[i];
    cout<<"Average is "<<average(grade)<<endl;
    return 0;
}
int average(int array[10])
{
    int i,sum=0;
    for (i=0;i<=9;i++) sum+=array[i];
    return sum/10;
}
