#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int q;
    cin >> q;
    for(int a0 = 0; a0 < q; a0++){
        long x;
        cin >> x;
        int num = 0;
        for (long i = 1 ; i < x; ++i){
            if ((i^x) > x) num++;
        }
        cout<<num<<endl;
    }
    return 0;
}
