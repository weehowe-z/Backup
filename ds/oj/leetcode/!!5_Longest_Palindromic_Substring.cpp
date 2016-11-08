#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;


class Solution {
public:
    string longestPalindrome(string s) {
        int size = s.size();

//        if (size <= 1) return s;


        vector<vector<bool>> isPal;
        for (int i = 0; i < size; ++i){
            vector<bool> vec(size,false);
            isPal.push_back(vec);
        }

        for (int i = 0 ; i< size; ++i){
            isPal[i][i] = true;
        }
        for (int i = 0; i < size-1;++i){
            if (s[i] == s[i+1]) isPal[i][i+1] = true;
        }
        for (int k = 2; k < size; ++k){
            int num = size - k;
            for (int p = 0; p <num; ++p){
                int i = p;
                int j = k + p;
                if ((s[i] == s[p])&&(isPal[i+1][j-1])) isPal[i][j] = true;
            }
        }

        int maxium = 0;
        int x;
        int y;
        for (int i = 0; i < size; ++i){
            for (int j = i; j < size; ++j){
                int length = j-i +1;
                if ((isPal[i][j])&&(length>maxium)){
                    x = i;
                    y = j;
                }
            }
        }
        return s.substr(x,y-x+1);
    }
};


int main()
{
    Solution s;
    return 0;
}
