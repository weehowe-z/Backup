#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> countBits(int num) {
            vector<int> vec;
            if (num == 0) {vec.push_back(0); return vec; }
            if (num == 1) {vec.push_back(0); vec.push_back(1); return vec; }

            int len = 2;

            vec.push_back(0);
            vec.push_back(1);

            int level = ceil(sqrt(num)) + 1;
            cout<<level<<endl;
            for(int i=1; i<level; ++i) {
                    for (int j=0; j<pow(2,i); ++j) {
                            vec.push_back(vec[j]+1);
                            len++;
                            if (len==num+1) return vec;
                    }
            }

            return vec;
    }
};

int main()
{
        Solution s;
        cout<<"Hello world!"<<endl;
        vector<int> vec = s.countBits(6);
        for (int i = 0; i < vec.size(); ++i) {
                cout<<vec[i]<<" ";
        }
        return 0;
}
