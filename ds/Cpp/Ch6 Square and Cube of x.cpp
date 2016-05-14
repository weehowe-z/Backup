//二次方，三次方表格
#include <iostream>
using namespace std;
inline int square(int x) {return x*x;}
inline int cube(int x){return x*x*x;}
int main()
{
    int x;
    cout<<"Input x: ";
    cin>>x;
    cout<<"X^2 = "<<square(x)<<endl;
    cout<<"X^3 = "<<cube(x)<<endl;
    return 0;
}
