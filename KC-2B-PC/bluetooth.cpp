#include <windows.h>
#include <iostream>
#include <string>
using namespace std;

class Car
{
public:
    //don't change this function!or there may be some mistakes
    bool initialPort(char *port)//initial example initialPort("COM0")
    {
        m_hCom = CreateFile( port, GENERIC_READ | GENERIC_WRITE, 0, NULL,OPEN_EXISTING, 0, NULL );
        if(m_hCom==INVALID_HANDLE_VALUE)
        {
            return false;
        }
        else
        {
            DCB dcb;
            GetCommState(m_hCom,&dcb);

            dcb.BaudRate = 9600;//port rate
            dcb.ByteSize = 8;
            dcb.Parity = NOPARITY;
            dcb.StopBits = ONESTOPBIT;
            dcb.fOutxCtsFlow=0;
            dcb.fRtsControl=RTS_CONTROL_ENABLE;
            SetCommState(m_hCom,&dcb);
            PurgeComm(m_hCom,PURGE_TXCLEAR);
        }
        SetupComm(m_hCom,1024,1024);
        SetCommMask(m_hCom,EV_RXCHAR|EV_TXEMPTY);
        return true;
    }
    void up()
    {
        DWORD length;
        buffer[0]='A';
        WriteFile(m_hCom, buffer, 1, &length, NULL );
    }
    void down()
    {
        DWORD length;
        buffer[0]='B';
        WriteFile(m_hCom, buffer, 1, &length, NULL );
    }
    void left()
    {
        DWORD length;
        buffer[0]='L';
        WriteFile(m_hCom, buffer,1, &length, NULL );
    }
    void right()
    {
        DWORD length;
        buffer[0]='R';
        WriteFile(m_hCom, buffer, 1, &length, NULL );
    }
    void stop()
    {
        DWORD length;
        buffer[0]='P';
        WriteFile(m_hCom, buffer, 1, &length, NULL );
    }
    void changeDuty(string duty)
    {
        DWORD length;
        buffer[0]='D';
        numbuffer=new char[duty.length()];
        for (unsigned int i=0;i<duty.length();++i) numbuffer[i]=duty[i];
        WriteFile(m_hCom, buffer, 1, &length, NULL );
        WriteFile(m_hCom,numbuffer,duty.length(),&length,NULL);
        WriteFile(m_hCom, buffer, 1, &length, NULL );
        delete []numbuffer;
    }
        void changeSpeed(string speed)
    {
        DWORD length;
        buffer[0]='S';
        numbuffer=new char[speed.length()];
        for (unsigned int i=0;i<speed.length();++i) numbuffer[i]=speed[i];
        WriteFile(m_hCom, buffer, 1, &length, NULL );
        WriteFile(m_hCom,numbuffer,speed.length(),&length,NULL);
        WriteFile(m_hCom, buffer, 1, &length, NULL );
        delete []numbuffer;
    }
      void changeTurn(string Turn)
    {
        DWORD length;
        buffer[0]='K';
        numbuffer=new char[Turn.length()];
        for (unsigned int i=0;i<Turn.length();++i) numbuffer[i]=Turn[i];
        WriteFile(m_hCom, buffer, 1, &length, NULL );
        WriteFile(m_hCom,numbuffer,Turn.length(),&length,NULL);
        WriteFile(m_hCom, buffer, 1, &length, NULL );
        delete []numbuffer;
    }
        void changeCYC(string CYC)
    {
        DWORD length;
        buffer[0]='K';
        numbuffer=new char[CYC.length()];
        for (unsigned int i=0;i<CYC.length();++i) numbuffer[i]=CYC[i];
        WriteFile(m_hCom, buffer, 1, &length, NULL );
        WriteFile(m_hCom,numbuffer,CYC.length(),&length,NULL);
        WriteFile(m_hCom, buffer, 1, &length, NULL );
        delete []numbuffer;
    }
private:
    HANDLE m_hCom;
    char buffer[1];//input signal
    char* numbuffer;//use to input number
};

int main()
{
    Car mycar;
    if(mycar.initialPort("COM9")) cout<<"build connection completed\n";
        else {cout<<"build connection failed\n";return 0;}
        char signal;
    string number;
    while (true)
    {
        std::cin>>signal;
        switch (signal)
        {
            case 'A':mycar.up();break;
            case 'B':mycar.down();break;
            case 'L':mycar.left();break;
            case 'R':mycar.right();break;
            case 'P':mycar.stop();break;
            case 'D'://change duty
                {
                    cin>>number;
                    mycar.changeDuty(number);
                    break;
                }
            case 'S':
                {
                    cin>>number;
                    mycar.changeSpeed(number);
                    break;
                }
            case 'C':
                {
                     cin>>number;
                    mycar.changeTurn(number);
                }
            case 'K':
                {
                    cin>>number;
                    mycar.changeCYC(number);
                }
        }
    }
    return 0;
}
