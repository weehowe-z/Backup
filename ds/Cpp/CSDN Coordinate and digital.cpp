//Coordinate and digital By Weehowe.z
//V14.3.13 ��ɻ�������
//���Ǵ�0��ʼ������д������ֱ��y=x y=x-1��.
//0, 1, 2,  3�ֱ�д��(0,0), (1,1), (2,0)��(3, 1)��4���ϡ���ͼ���ɼ���д
//���ڸ�������(x,y)����(x,y)λ�õ������Ƕ��٣�
//������λ�ò���������������-1�����У�0<=x,y<=1100��
#include <iostream>
using namespace std;
int coordinate(int x,int y)
{
   if ((y==x || y== x-2)&&(x>=0 && x<=1100 && y>=0 && y<=1100)){
        if (y==x) {
            if (x%2==0) return 2*x;
            else return 2*x-1;
            }
        else {if (x%2==0) return 2*x-2;
                else return 2*x-3;
                }
        }
    else return -1;
}
int main()
{
    int x,y;
    cout<<"�������������꣨x,y�� (0��1100���ڣ�: ";
    cin>>x>>y;
    cout    <<coordinate(x,y)<<endl;
    return 0;
}
