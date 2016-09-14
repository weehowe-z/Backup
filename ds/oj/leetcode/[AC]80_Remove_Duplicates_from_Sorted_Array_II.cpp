#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
            if (nums.size() == 0) return 0;
            if (nums.size() == 1) return 1;
            sort(nums.begin(), nums.end());

            map<int, int> mp;
            map<int,int>::iterator it;
            mp.insert(pair<int,int>(nums[0],1));

            int index = 0;

            for (int i = 1; i< nums.size(); ++i) {
                    if (nums[index]!=nums[i]) {
                            nums[++index] = nums[i];
                            mp.insert(pair<int,int>(nums[i],1));
                    } else{
                            it = mp.find(nums[i]);
                            if (it->second == 1) {
                                    it->second = 2;
                                    nums[++index] = nums[i];
                            }
                    }
            }
            return index+1;
    }
};

int main()
{
        Solution s;
        //vector<int> vec = {1,2,3,4,5,6,5,5,6,2,1,1};
        vector<int> vec = {1,1,1,2,2,3};
        cout<<s.removeDuplicates(vec)<<endl;
        for (int i =0; i <vec.size(); ++i) {
                cout<<vec[i]<<" ";
        }
        return 0;
}
