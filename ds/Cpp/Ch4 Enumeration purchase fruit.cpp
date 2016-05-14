//enumeration buy fruits
#include <iostream>
using namespace std;
int main()
{
    int apple,melon,orange;
    for (melon=1;melon<=9;melon++){
        for (apple=1;apple<(50-5*melon);apple++){
            orange = 3*(50-5*melon-apple);
            if (melon+apple+orange==100){
                cout<<"melon: "<<melon;
                cout<<"\tapple: "<<apple;
                cout<<"\torange: "<<orange<<endl;
            }
        }
    }
    return 0;
}

