#include <iostream>
using namespace std;


class Solution {
public:
    bool canWinNim(int n) {
            if ( n%4 == 0) return false;
            else return true;
    }
};

int main()
{
        Solution s;
        cout<<s.canWinNim(5)<<endl;
}
