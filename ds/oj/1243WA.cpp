//1243. �����ر��΢������
//Description
//�ֵ�����ĩ���ֵ�ʱ���ˡ�X��ʦ����Ϊ�������¸е����������Ϊ���ͬѧ�Ƿ�����ƫ�߻���ƫ�ͣ��쵼�ͻ����Լ��Ȳ衣
//
//���Ϊ��ȷ������������̬�ֲ���X��ʦ�����Է�������΢����������ϵķ�������ѧ���ų�һ�����У�X��ʦӵ���ر��΢�����ɡ���Ϊ����ʵ���̵��㣬��Ҫ��дһ��΢��ϵͳ�� ��Ҫʵ�ֵĲ������£�

//0 l r -- ��ѧ��l��r֮�䣨�������ˣ���ͬ������ͬѧ�ĳɼ�������ƽ�������

//1 l r -- ��l��r֮������ͬѧ����߷������

//2 l r -- ��l��r֮������ͬѧ�ĳɼ���ת����lͬѧ�ɼ���Ϊrͬѧ�ɼ���l+1ͬѧ�ı�Ϊr-1�ģ��Դ����ƣ�

//3 l r -- �������l��r֮������ͬѧ�ĳɼ����ÿո�ֿ���

//4 l r -- ��l��r֮������ͬѧ�ĳɼ��µ�1�����Ѿ���0���򲻱䡣


#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    int n,m,l,r,opt,high;
    double total;
    int *grade;
    cin>>n>>m;
    grade=new int[n];
    for (int i=0;i<n;++i) cin>>grade[i];
    for (int i=0;i<m;++i){
        cin>>opt>>l>>r;
        switch(opt)
        {
            case 0:
                {
                    total=0;
                    for (int j=l;j<=r;++j) total+=grade[j];
                    cout<<fixed<<setprecision(2)<<total/n<<endl;
                    break;
                }
            case 1:
                {
                    high=grade[0];
                    for (int j=l;j<=r;++j){
                        if (high<grade[j]) high=grade[j];
                    }
                    cout<<high<<endl;
                    break;
                }
            case 2:
                {
                    for (int j=l;j<=(r+l)/2;++j){
                        high=grade[j];
                        grade[j]=grade[l+r-j];
                        grade[l+r-j]=high;
                    }
                    break;
                }
            case 3:
                {
                    for (int j=l;j<=r;++j) cout<<grade[j]<<" ";
                    cout<<endl;
                    break;
                }
            case 4:
                {
                    for (int j=l;j<=r;++j){
                        if (grade[j]>0) --grade[j];
                    }
                }
        }
    }
    delete []grade;
    return 0;
}
