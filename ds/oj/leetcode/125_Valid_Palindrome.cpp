#include <iostream>
using namespace std;


class Solution {
public:
    bool isPalindrome(string s) {
        string newstr;
        for (int i = 0 ; i < s.size(); ++i){
            if ((s[i]>='a')&&(s[i]<='z')) newstr.push_back(s[i]);
            else if ((s[i]>='0')&&(s[i]<='9')) newstr.push_back(s[i]);
            else if ((s[i]>='A')&&(s[i]<='Z')) newstr.push_back((char)(s[i]-'A'+'a'));
        }
        if (newstr.size()==0) return true;
        int size = newstr.size();
        for (int i = 0 ; i < newstr.size()/2; ++i){
            if (newstr[i]!=newstr[size-i-1]) return false;
        }
        return true;
    }
};


int main()
{
    Solution s;
    cout<<s.isPalindrome("race a car");
    return 0;
}
