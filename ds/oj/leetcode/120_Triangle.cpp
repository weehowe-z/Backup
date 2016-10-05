#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        int total_level = triangle.size();
        vector<vector<int>> f = triangle;
        for (int i = 1; i< total_level; ++i){
            for (int j = 0 ; j < i+1; ++j){
                if (j == 0) f[i][j] = f[i-1][j] + triangle[i][j];
                else if (j == triangle[i].size() -1) f[i][j] = f[i-1][j-1] + triangle[i][j];
                else f[i][j] = min(f[i-1][j], f[i-1][j-1]) + triangle[i][j];
            }
        }
        return *min_element(f[total_level-1].begin(),f[total_level-1].end());
    }
};

int main()
{
    Solution s;
    vector<vector<int>> vec= {
     {2},
    {3,4},
   {6,5,7},
  {4,1,8,3}
    };
//    vector<int> ss = {1};
//    vec.push_back(ss);
//    vector<int> ss2 = {2,3};
//    vec.push_back(ss2);
    cout<<s.minimumTotal(vec)<<endl;
}