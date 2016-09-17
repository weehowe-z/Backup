#include <iostream>
using namespace std;
int main()
{
    int n;
    int **soduku;
    bool flag;
    bool boolsodu[9];
    cin>>n;
    for (int k=0;k<n;++k){
        flag=true;
        while (flag){
            soduku=new int*[9];
            for (int i=0;i<9;++i) soduku[i]=new int[9];
            flag=true;
            for (int i=0;i<9;++i) {
                for (int j=0;j<9;++j) cin>>soduku[i][j];
            }
            //按行
            for (int i=0;i<9;++i){
                for (int j=0;j<9;++j) boolsodu[j]=false;
                for (int j=0;j<9;++j) boolsodu[soduku[i][j]-1]=true;
                for (int j=0;j<9;++j) if (boolsodu[j]==false) {flag=false;break;}
            }
            if (!flag) break;
            //按列
            for (int j=0;j<9;++j){
                for (int i=0;i<9;++i) boolsodu[i]=false;
                for (int i=0;i<9;++i) boolsodu[soduku[i][j]-1]=true;
                for (int i=0;i<9;++i) if (boolsodu[i]==false) {flag=false;break;}
            }
            if (!flag) break;

            for (int i=0;i<9;i+=3){
                for (int j=0;j<9;j+=3){
                    for (int w=0;w<9;++w) boolsodu[w]=false;
                    for (int p=i;p<i+3;++p){
                        for (int q=j;q<j+3;++q)
                            boolsodu[soduku[p][q]-1]=true;
                    }
                    for (int w=0;w<9;++w) if (boolsodu[w]==false) {flag=false;break;}
                }
                if (!flag) break;
            }
            break;
        }
        if (flag) cout<<"Right"<<endl;
            else cout<<"Wrong"<<endl;
        for (int i=0;i<9;++i) delete[]soduku[i];
        delete []soduku;
    }
    return 0;
}
