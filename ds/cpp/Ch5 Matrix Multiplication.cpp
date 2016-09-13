//matrix multiplication
//V2014.3.17 Weehowe.z
#include <iostream>
#define maxsize 10
using namespace std;
int main()
{
    int a[maxsize][maxsize]={0};
    int b[maxsize][maxsize]={0};
    int c[maxsize][maxsize]={0};
    int i,j,k;
    int row_a,row_b,col_a,col_b;
    cout<<"This cpp can deal with Matrix A * Matrix B lower than 10 scale.\n";
    while(true){
            cout<<"Please enter the row and column of matrix A: ";
            cin>>row_a>>col_a;
            cout<<"Please enter the row and column of matrix B: ";
            cin>>row_b>>col_b;
            if (col_a==row_b) break;
            cout<<"Can't multiply A and B\n";
    }

    for (i=0;i<=row_a-1;i++){
        for (j=0;j<=col_a-1;j++){
            cout<<"Input a["<<i+1<<"]["<<j+1<<"]: ";
            cin>>a[i][j];
            }
    }
    for (i=0;i<=row_b-1;i++){
        for (j=0;j<=col_b-1;j++){
            cout<<"Input b["<<i+1<<"]["<<j+1<<"]: ";
            cin>>b[i][j];
            }
    }
    for (i=0;i<=row_a-1;i++){
        for(j=0;j<=col_b-1;j++){
            for(k=0;k<=row_b-1;k++){
                c[i][j]+=a[i][k]*b[k][j];
            }
        }

    }
    //Output Matrix C
    cout<<"Matrix C is:\n";
    for (i=0;i<=row_a-1;i++){
            for(j=0;j<=col_b-1;j++){
                cout<<c[i][j]<<"\t";
            }
            cout<<"\n";
    }
    return 0;
}
