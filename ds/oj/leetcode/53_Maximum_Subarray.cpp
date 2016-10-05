#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int maxSum = nums[0];
        vector<int> f = nums;
        for (unsigned int i = 1; i< nums.size(); ++i){
            f[i] = max(nums[i], f[i-1] + nums[i]);
            maxSum = max (maxSum, f[i]);
        }
        return maxSum;
    }
};

int main()
{
    Solution s;
    vector<int> haha = {-2,1,-3,4,-1,2,1,-5,4};
    s.maxSubArray(haha);
}