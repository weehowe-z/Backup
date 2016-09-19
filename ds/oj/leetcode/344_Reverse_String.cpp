#include <iostream>
using namespace std;

class Solution {
public:
    string reverseString(string s) {
            char temp;
            int len;
            len = s.length();
            for (int i = 0; i<len/2; ++i) {
                    temp = s[i];
                    s[i] = s[len-i-1];
                    s[len-i-1] = temp;
            }
            return s;
    }
};

int main()
{
        Solution s;
        cout<<"Hello world!"<<endl;
        cout<<s.reverseString("ab")<<endl;

}
