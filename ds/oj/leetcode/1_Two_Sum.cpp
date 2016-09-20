#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, vector<int>> umap;
        vector<int> vec;

        for (int i = 0 ; i < nums.size(); ++i){
            if (umap.find(nums[i]) == umap.end()){
                //new
                vector<int> vec;
                vec.push_back(i);
                umap.insert(pair<int,vector<int>>(nums[i],vec));
                //cout<<"new insert "<< nums[i]<<endl;
            }else{
                //update
                vector<int> vec = umap[nums[i]];
                vec.push_back(i);
                umap[nums[i]] = vec;
                //cout<<"insert "<< nums[i]<<endl;
            }


        }

        for (int i = 0 ; i < nums.size(); ++i){
            int gap = target - nums[i];
            //cout<<"gap is "<<gap<<endl;
            if (gap == nums[i]){
                if (umap[nums[i]].size() == 1) continue;
                //cout<<"size is "<<umap[nums[i]].size()<<endl;
                return umap[nums[i]];
            }
            else if (umap.find(gap) != umap.end()){
                //cout<<"find " << nums[i]<<endl;
                vec.push_back(i);
                vec.push_back(umap[target-nums[i]][0]);
                return vec;
            }
        }
        return vec;
    }
};

int main()
{
    Solution s;
    vector<int> nums = {3,2,4};
    cout<<s.twoSum(nums,6)[0];

    return 0;

}
