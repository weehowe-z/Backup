#include <iostream>
using namespace std;


class Solution {
public:
    int strStr(string haystack, string needle) {
        //KMP or Boyer-Mooer or Rabin-Karp
        if (needle.size() == 0) return 0;
        int size1 = haystack.size();
        int size2 = needle.size();

        int i = 0;
        for (; i<= size1-size2;++i){
            //judge this
            int x = i;
            int y = 0;
            while((x<size1)&&(y<size2)&&(haystack[x]==needle[y])){
                ++x;
                ++y;
            }
            if (y == size2) return i;
        }
        return -1;
    }
};


int main()
{
    Solution s;
    cout<<s.strStr("","a");
    return 0;
}
