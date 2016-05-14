#include <iostream>
using namespace std;
int main()
{
    int **hand;
    int i,j,k=0;
    hand=new int *[2];
    for (i=0;i<=1;i++) hand[i]=new int[3];
    for (i=0;i<=1;i++){
        for (j=0;j<=5;j++) hand[i][j]=k++;
    }
    for (i=0;i<=1;i++){
        for (j=0;j<=3;j++) cout<<hand[i][j];
    }
    for (i=0;i<=1;i++) delete [] hand[i];
    delete [] hand;

    return 0;
}
