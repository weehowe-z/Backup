#include <iostream>
#include <unordered_map>
using namespace std;

class Solution
{
public:
    int lengthOfLongestSubstring(string s)
    {
        int maxlen = 0;

        int len = s.size();

        const int ASCII_MAX = 255;

        int bitArray[255];

        int index = 0;

        for (int i = 0; i < ASCII_MAX; ++i) bitArray[i] = -1;

        for (int i = 0; i < len; ++i){
//            cout<<"now maxlen " << maxlen<<endl;
//            cout<<"now judging " << s[i] <<endl;
            if (bitArray[s[i]] >= index) {
//                cout <<s[i] <<" has seen\n";
                maxlen = max(maxlen, i - index);
//                cout<<"new max len" << maxlen << "\n";
                index = bitArray[s[i]] + 1;
            }
            bitArray[s[i]] = i;
        }

        return max(maxlen, len-index);
    }
};

int main()
{
    Solution s;
    cout<<s.lengthOfLongestSubstring("abcaaaaaaa")<<endl;
    return 0;
}
