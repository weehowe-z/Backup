#include <iostream>
#include <cstdlib>
#include<ctime>
using namespace std;
int array[100];
bool signal[101];
void createArray();
void bubbleSort();
int main()
{
    createArray();
    bubbleSort();
    return 0;
}
void createArray()
{
    srand(time(NULL));
    int i,j,num;
    for (i=0;i<101;++i) signal[i]=true;
    for (i=0;i<100;++i){
        while(true){
            num=101*rand()/(RAND_MAX+1);
            if (signal[num]){
                signal[num]=false;
                array[i]=num;
                break;
            }
        }
    }
    cout<<"随机生成的数组是:\n";
    for (i=0;i<10;++i){
        for (j=0;j<10;++j){
            cout<<array[i*10+j]<<"\t";
        }
        cout<<endl;
    }
}
void bubbleSort()
{
    bool flag=true;
    int i=99,j,temp;
    while(i>=0 && flag){
            flag=false;
            for (j=0;j<=i-1;++j){
                if (array[j]>array[j+1]){
                        temp=array[j+1];
                        array[j+1]=array[j];
                        array[j]=temp;
                        flag=true;
                }
            }
            --i;
        }
        cout<<"冒泡排序的数组是:\n";
        for (i=0;i<10;++i){
        for (j=0;j<10;++j){
            cout<<array[i*10+j]<<"\t";
        }
        cout<<endl;
    }
}
