#include <iostream>
using   namespace std;
void snakeMatrix(int,int,int);
int **snake;
int main()
{
    int scale,i,j;
    cout<<"Please input scale: ";
    cin>>scale;
    snake=new int*[scale];
    for(i=0;i<scale;++i) snake[i]=new int[scale];
    snakeMatrix(scale,1,0);
    cout<<"\nSnake Matrix:\n";
    for(i=0;i<scale;++i){
        for (int j=0;j<scale;++j) cout<<snake[i][j]<<"\t";
        cout<<endl;
    }
    for(i=0;i<scale;++i) delete []snake[i];
    delete []snake;
}
void snakeMatrix(int n,int num,int edge )
{
    int row=0,col=0;
    if (n<=0) return;
    if (n==1) snake[edge][edge]=num*num;
    if (n>1){
        for (col=edge;col<edge+n-1;++col) {
                snake[edge][col]=num*num;
                ++num;
        }
        for (row=edge;row<edge+n-1;++row) {
                snake[row][edge+n-1]=num*num;
                ++num;
        }
         for (col=edge+n-1;col>edge;--col) {
                snake[edge+n-1][col]=num*num;
                ++num;
        }
         for (row=edge+n-1;row>edge;--row) {
                snake[row][edge]=num*num;
                ++num;
        }
    }
    snakeMatrix(n-2,num,edge+1);
}
