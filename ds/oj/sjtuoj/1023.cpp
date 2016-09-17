#include <iostream>
using namespace std;
void calculate();
int main()
{
    int n;
    cin>>n;
    for (int k=0;k<n;++k) calculate();
    return 0;
}
void calculate()
{
    int **mat;
    int dex,type;
    cin>>dex>>type;
    mat=new int*[dex];
    for (int i=0;i<dex;++i) mat[i]=new int[dex];
    for (int i=0;i<dex;++i){
        for (int j=0;j<dex;++j) cin>>mat[i][j];
    }
    switch(type)
    {
    case 0:
        for (int i=0;i<dex;++i){
            for (int j=dex-1;j>=0;--j) cout<<mat[i][j]<<" ";
            cout<<endl;
        }
        break;
    case 1:
        for (int i=dex-1;i>=0;--i){
            for (int j=0;j<dex;++j) cout<<mat[i][j]<<" ";
            cout<<endl;
        }
        break;
    case 2:
        for (int j=0;j<dex;++j){
            for (int i=0;i<dex;++i) cout<<mat[i][j]<<" ";
            cout<<endl;
        }
    }
    for (int i=0;i<dex;++i) delete[]mat[i];
    delete []mat;
}
