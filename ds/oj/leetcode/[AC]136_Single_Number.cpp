#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int num = 0;
        for (unsigned int i = 0 ; i < nums.size();++i){
            num = num^nums[i];
        }
        return num;
    }
};

int main()
{
    Solution s;
    vector<int> x = {1,2,3,2,3,1,5,4,5};
    cout<<s.singleNumber(x);
    return 0;
}
