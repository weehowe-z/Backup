#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
            if (nums.size() == 0) return 0;
            if (nums.size() == 1) return 1;
            sort(nums.begin(), nums.end());
            int prev = nums[0];
            int len = 1;
            for (int i = 1; i < nums.size(); ++i) {
                    if (nums[i] != prev) {
                            prev = nums[i];
                            len += 1;
                    }
            }

            int index = 0;
            for (int i = 1; i< nums.size(); ++i) {
                    if (nums[index]!=nums[i]) {
                            nums[++index] = nums[i];
                    }
            }
            return len;
    }
};

int main()
{
        Solution s;
        vector<int> vec = {1,2,3,4,5,6,5,6,2,1,1};
        cout<<s.removeDuplicates(vec);
        for (int i =0; i <vec.size(); ++i) {
                cout<<vec[i]<<" ";
        }
        return 0;
}
