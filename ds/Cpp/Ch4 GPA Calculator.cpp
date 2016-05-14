//value calculator Ver 1.0
//By Weehowe.z
//下一步将添加计算学积分，方差等功能
#include <iostream>
using namespace std;
int main()
{
    int value=0,total=0,max=0,min=100,people=0,i;
    float average;
    cout<<"How many students? ";
    cin>>people;
    for (i=1;i<=people;i++){
        while (true){
                cout<<"Input NO"<<i<<"'s value: ";
                cin>>value;
                if (value<=100 && value>=0) break;
                cout<<"Please input correct value!!"<<endl;
        }
        cout<<"Input NO"<<i<<"'s value: ";
        cin>>value;
        if (value<min) min=value;
        if (value>max) max=value;
        total+=value;
    }
    average=double(total)/(i-1);
    cout<<"the average is "<<average<<endl;
    cout<<"the highest value is "<<max<<endl;
    cout<<"the lowest value is "<<min<<endl;
    return 0;
}
