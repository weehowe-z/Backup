//easy select Sort
//O(N^2)
#include <iostream>
using namespace std;
int main()
{
    int lh,k,temp;
    int array[10]={2,5,1,9,10,0,4,8,7,6};
    for (lh=0;lh<=8;lh++){//n-1 turn
        for (k=lh;k<=9;k++){
            if (array[lh]<array[k]) {
                temp=array[lh];
                array[lh]=array[k];
                array[k]=temp;
            }
        }
        cout<<array[lh]<<" ";
    }
    return 0;
}
