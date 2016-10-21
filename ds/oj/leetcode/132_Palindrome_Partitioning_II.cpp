#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minCut(string s){
        const int size = s.length();
        vector<bool> = vec(false, size);
        vector<vector<bool>> p;
        for (int i = 0 ;i <size; ++i) p.push_back(vec);
        
        vector<int> f(0,size);

        //get init stat
        
        for (int i = 0 ; i < size ;++i){
            f[i] = 
        }
        
    }

    vector<vector<string>> partition(string s) {
        vector<vector<string>> result;
        vector<string> path;
        dfs(s,path,result,0);
        return result;
    }
    
    void dfs(string &s, vector<string> &path, vector<vector<string>> &result, int startPos){
        if (startPos == s.length()){
            result.push_back(path);
            return;
        }
        
        for (int i = startPos; i<s.length();++i){
            //do as partition
            if (isPalindrome(s,startPos,i)){
                path.push_back(s.substr(startPos,i-startPos+1));
                dfs(s,path,result,i+1);
                path.pop_back();
            }
        }
    }
    
    bool isPalindrome(string &s, int begin, int end){
        int length = end - begin + 1;
        for (int i = begin ; i < (begin + end)/2 + 1; ++i){
            if (s[i] != s[begin+end-i]) return false;
        }
        return true;
    }
};

int main()
{
    Solution s;
    string haha = "aab";
    cout<<(s.isPalindrome(haha,1,2))<<endl;
    return 0;
    
}