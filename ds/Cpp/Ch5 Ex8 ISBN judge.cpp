#include <iostream>
using namespace std;
int main()
{
    char ISBN[14];
    int num=0,i=0,md5=0;
    cout<<"Please input ISBN: ";
    cin.getline(ISBN,14);
    while (ISBN[i]!='\0'){
            if (ISBN[i]<'0'||ISBN[i]>'9') break;
            ++num;
            ++i;
    }
    switch(num)
    {
        case 10:
            for (i=0;i<10;++i) md5+=ISBN[i]*(10-i);
            if (md5%11==0) cout<<"Correct ISBN"<<endl;
            else cout<<"Wrong ISBN"<<endl;
            break;
        case 13:
            for (i=0;i<13;i+=2) md5+=ISBN[i];
            for (i=1;i<13;i+=2) md5+=3*ISBN[i];
            if (md5%10==0) cout<<"Correct ISBN"<<endl;
            else cout<<"Wrong ISBN"<<endl;
            break;
        default:
            cout<<"Wrong ISBN!"<<endl;
    }
    return 0;
}
