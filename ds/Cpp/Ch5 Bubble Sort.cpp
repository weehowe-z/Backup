//
#include <iostream>
using namespace std;
int main()
{
    int i,j,temp;
    bool flag;
    int array[10]={2,5,1,9,10,0,4,8,7,6};
    for (i=1;i<=9;i++){
        flag= false;
        for (j=0;j<=10-i;j++){
            if (array[j]>array[j+1]) {
                temp=array[j];
                array[j]=array[j+1];
                array[j+1]=temp;
                flag = true;
            }
        }
        if (!flag) break;
    }
    for (i=0;i<=9;i++) cout<<array[i]<<" ";
    return 0;
}
