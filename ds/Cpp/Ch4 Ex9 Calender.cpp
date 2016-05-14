//Calender

//V2014.4.8 finish basic function
#include <iostream>
using namespace std;

int getYear();
bool jugdeLunarYear(int year);
int getFirstdayInYear(int year);
int getDaysInMonth(int month,int year);
void printCalender(int year);
int main()
{
    printCalender(getYear());
    return 0;
}
int getYear()//获得年份
{
    int year;
    cout<<"Please input a year later than 2010 :";
    cin>>year;
    return year;
}
int getFirstdayInYear(int year)
{
    int i,firstday=5;
    int day=0;
    for (i=2010;i<year;++i){
        day+=365;
        if ((i%4 == 0 && i%100 != 0) || i%400 == 0) ++day;
    }
    firstday=(firstday+day)%7;
    return firstday;
}
bool jugdeLunarYear(int year)
{
    if ( year%4 == 0 && year%100 != 0 || year%400 == 0) return true;
    return false;
}
int getDaysInMonth(int month,int year)
{
    int day;
    switch(month)
    {
        case 4:case 6: case 9: case 11:day=30;break;
        case 2:if (year%4 == 0 && year%100 != 0 || year%400 == 0) day=29;
                    else  day=28;
                    break;
        default: day=31;
    }
    return day;
}
void printCalender(int year)
{

    int month,weekday,day,i;
    weekday=getFirstdayInYear(year);
    for (month=1;month<=12;month++){
        day=getDaysInMonth(month,year);
        cout<<"Sun\tMon\tThu\tWed\tThu\tFri\tSat\n";
        for (i=0;i<weekday;i++) cout<<"\t";
        for (i=1;i<=day;i++){
            cout<<i<<"\t";
            weekday=(weekday+1)%7;
            if (weekday==0) cout<<endl;
        }
        cout<<endl;
    }
}
