//���������� sizeof()����ȡռ�õ��ڴ���
//Weehowe.z 2014.2.27 Ver1.0
//�޸�Ԥ�ڣ���ȡĳ�ļ���ȡռ���ڴ�

#include <iostream>
using namespace std;
int main()
{
    cout<<"int: "<<sizeof(int)<<"Byte"<<endl;
    cout<<"short: "<<sizeof(short)<<"Byte"<<endl;
    cout<<"long: "<<sizeof(long)<<"Byte"<<endl;
    cout<<"unsigned int: "<<sizeof(unsigned int)<<"Byte"<<endl;
    cout<<"unsigned short: "<<sizeof(unsigned short)<<"Byte"<<endl;
    cout<<"unsigned long: "<<sizeof(unsigned long)<<"Byte"<<endl;
    cout<< "float: "<<sizeof(float)<<"Byte"<<endl;
	cout<<"double: "<<sizeof(double)<<"Byte"<<endl;
	cout<<"char: "<<sizeof(char)<<"Byte"<<endl;
	cout<<"bool: "<<sizeof(bool)<<"Byte"<<endl;
    return 0;
}
