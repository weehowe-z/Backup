#include <iostream>
using namespace std;
int main()
{
    int sum=0,student,n,p=0;
    float average;
    cout<<"how many students? ";
    cin>>student;
    int value[student];
    for (n=1;n<=student;n++){
        cout<<"Value? ";
        cin>>value[n];
        sum+=value[n];
    }
    average=double(sum)/student;
    cout<<"oval "<<average<<endl;
    for (n=1;n<=student;n++){
        if (value[n]>=average){
            cout<<"student "<<n<<endl;
            p++;
        }
    }
    cout<<p<<endl;
    return 0;
}
