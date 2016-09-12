#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> countBits(int num) {
        vector<int> vec;
        if (num == 0) {vec.push_back(0);return vec;}
        if (num == 1) {vec.push_back(1);return vec;}

        for(int i=0; i<num ;++i){

        }


    }
};

int main()
{
    Solution s;
    cout<<"Hello world!"<<endl;
    vector<int> vec = s.countBits(5);
}
