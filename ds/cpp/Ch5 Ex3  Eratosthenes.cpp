//The Sieve of Eratosthenes ������ɫ������ɸѡ��
#include <iostream>
using namespace std;
int main()
{
    bool *array;
    int i,j,n;
    cout<<"����ɸѡ���������� ";
    cin>>n;
    array=new bool[n];
    for (i=1;i<=n-1;++i) array[i]=true;
    for (i=1;i<=n-1;++i){
        if (array[i]) {
                for (j=i+1;j<=n-1;++j){
                    if ((j+1)%(i+1)==0) array[j]=false;
                }
        }
    }
    for (i=1;i<=n-1;++i) {
        if (array[i]) cout<<i+1<<"\t";
    }
    delete []array;
    return 0;
}
