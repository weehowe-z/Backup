#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_map<int,bool> umap;
        //init

        for (int num: nums){
            umap.insert(pair<int,bool>(num,false));
            cout<<num<<endl;
        }
        int maxlen = 1;
        for (int num: nums){
            if (umap[num]) continue;

            umap[num] = true;
            int len = 1;
            int index = num;
            while(true){
                index++;
                if (umap.find(index) == umap.end()) break;
                else{
                    umap[index] = true;
                    ++len;
                }
            }

            index = num;
            while(true){
                index--;
                if (umap.find(index) == umap.end()) break;
                else{
                    umap[index] = true;
                    ++len;
                }
            }

            maxlen = max(maxlen,len);
        }
        return maxlen;
    }
};

int main()
{
    Solution s;
    vector<int> nums = {100, 4, 200, 1, 3, 2,5};
    cout<<s.longestConsecutive(nums)<<endl;
    return 0;
}
