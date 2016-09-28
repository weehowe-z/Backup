#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        const int countsize = sizeof(int)*8;
        int bitcount[countsize] = {0};
        int num = 0;
        for (unsigned int i = 0 ; i < nums.size();++i){
            for (int j = 0 ; j<countsize; ++j){
                bitcount[j] += (nums[i] >> j)&1;
                bitcount[j] = bitcount[j]%3;
            }
        }

        for (int i = 0 ;i<countsize; ++i){
            num += bitcount[i] << i;
        }
        return num;
    }
};

int main()
{
    Solution s;
    vector<int> x = {1,1,1,2,3,3,3,2,2,5,5,4,5};
    //cout<<sizeof(int)<<endl;
    cout<<s.singleNumber(x)<<endl;
    return 0;
}
