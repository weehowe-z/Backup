//Magic Matrix
//V2014.3.17
#define Max 15
#include <iostream>
using namespace std;
int main()
{
    int row,col,i,scale;
    int magic[Max][Max]={0};
    cout<<"Please input scale: ";
    cin>>scale;
    row=0;
    col=(scale-1)/2;
    magic[row][col]=1;
    for (i=2;i<=scale*scale;i++){//create
            if (magic[(row-1+scale)%scale][(col+1+scale)%scale]==0){
                row=(row-1+scale)%scale;
                col=(col+1)%scale;
                }
            else row=(row+1)%scale;
            magic[row][col]=i;
            }
    //print
    cout<<"The Magic Matrix["<<scale<<"] is: \n";
    for (row=0;row<=scale-1;row++){
        for (col=0;col<=scale-1;col++){
            cout<<magic[row][col]<<"\t";
        }
        cout<<endl;
    }
    return 0;
}
