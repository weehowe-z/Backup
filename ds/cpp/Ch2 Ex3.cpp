#include <iostream>
using namespace std;
int main()
{
    int array[9]={0};
    int i,j;
    for (i=0;i<=8;i++){
        cin>>array[i];
    }
    for (i=0;i<=2;i++){
        for (j=0;j<=2;j++){
            cout<<array[i*3+j]<<"\t";
        }
        cout<<endl;
    }
    return 0;
}
