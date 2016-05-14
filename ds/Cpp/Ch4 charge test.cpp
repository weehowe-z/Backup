#include <iostream>
using namespace std;
int main()
{
    const double onefen=0.01,twofen=0.02;
    int one=0,two=0;
    double charge;
    cout<<"Input charge: ";
    cin>>charge;
    while (charge>=twofen){
        two++;
        charge-=twofen;
    }
    while (charge>=onefen){
        one++;
        charge-=onefen;
    }
    cout<<"one fen "<<one<<endl;
    cout<<"two fen "<<two<<endl;
    return 0;

}
