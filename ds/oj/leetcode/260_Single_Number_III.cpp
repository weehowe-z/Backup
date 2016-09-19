#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    /*
    int getDifIndex(int a, int b){
        int intsize = sizeof(int)*8;

        for (int i = 0 ; i < intsize;++i){
            int bita = (a >> i) &1;
            int bitb = (b >> i) &1;
            if (bita!= bitb) return i;
        }
    }
    */


    vector<int> singleNumber(vector<int>& nums) {
        vector<int> result;

        int num = 0;
        int num_a = 0;
        int num_b = 0;

         for (unsigned int i = 0 ; i < nums.size();++i){
            num = num^nums[i];
        }

        int difIndex;
        int intsize = sizeof(int)*8;
        for (int i = 0 ; i< intsize; ++i){
            if ((num>>i)&1){
                difIndex = i;
                break;
            }
        }

        for (unsigned int i = 0 ; i < nums.size();++i){
            //devide into two parts
            if ((nums[i]>>difIndex) & 1){
                num_a = num_a^nums[i];
            }else{
                num_b = num_b^nums[i];
            }
        }
        result.push_back(num_a);
        result.push_back(num_b);
        return result;
    }
};

int main()
{
    Solution s;
    vector<int> x = {1,1,2,2,3,3,4,5,6,6,7,7};
    //cout<<sizeof(int)<<endl;
    cout<<s.singleNumber(x)[1];
    return 0;
}
