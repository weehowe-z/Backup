#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Solution
{
public:
    int search(vector<int>& nums, int target)
    {
        sort(nums.begin(),nums.end());
        if (!binary_search(nums.begin(),nums.end(),target)) return -1;
        else return (lower_bound(nums.begin(),nums.end(),target)-nums.begin());
    }

};

int main()
{
    Solution s;
    vector<int> nums = {4,5,6,7,0,1,2};
    cout<<s.search(nums,11);
    for (unsigned int i = 0; i< nums.size(); ++i)
    {
        cout<< nums[i] <<" ";
    }
    return 0;
}
