#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

//bool mod8(vector<int> nums) {
//    int remain=0;
//    for (unsigned int i = 0 ; i < nums.size(); ++i) {
//        remain = (remain*10 + nums[i])%8;
//    }
//    return (remain==0)?true:false;
//}

bool mod8WithMap(string nums, unordered_map<string,bool> &mod8Map) {

    if (mod8Map.find(nums)!= mod8Map.end()) {
        return mod8Map[nums];
    }

    string fullpath = "";
    string currentpath = "";
    int remain=0;
    for (unsigned int i =0; i < nums.size(); ++i) {
        fullpath.push_back(nums[i]);
        currentpath.push_back(nums[i]);

        int num = nums[i]-'0';
        remain = (remain*10 + num)%8;

        if (remain == 0){
            mod8Map.insert(pair<string, bool>(fullpath,true));
            mod8Map.insert(pair<string, bool>(currentpath,true));
            currentpath = "";
        }
    }
    bool result = (remain==0)?true:false;
    mod8Map.insert(pair<string, bool>(nums,result));
    return result;
}



//void dfs(string& number, int startPos, vector<int> path, int  &totalNum, int len) {
//    if (startPos >= len) {
//        if (path.empty()) return;
//        if ((path[path.size()-1]-'0')%2!=0) return;
//        if (mod8(path)) totalNum+=1;
//        return;
//    } else {
//        path.push_back(number[startPos]-'0');
//        dfs(number,startPos+1,path,totalNum, len);
//        path.pop_back();
//        dfs(number,startPos+1,path,totalNum, len);
//    }
//}

void dfs(string& number, int startPos, string path, int  &totalNum, int len, unordered_map<string, bool> &mod8Map) {
    if (startPos >= len) {
        if (path.empty()) return;
        if ((path[path.size()-1]-'0')%2!=0) return;
        if (mod8WithMap(path,mod8Map)) {
                totalNum+=1;
                cout<<path<<endl;
        }
    } else {
        path.push_back(number[startPos]);
        dfs(number,startPos+1,path,totalNum, len, mod8Map);
        path.pop_back();
        dfs(number,startPos+1,path,totalNum, len, mod8Map);
    }
    return;
}


int main() {
    int n;
    cin >> n;
    string number;
    cin >> number;
    // your code goes here
    int totalNum = 0;
//    vector<int> path;
    string path="";
    unordered_map<string, bool> mod8Map;
    dfs(number,0,path,totalNum,n, mod8Map);
    cout<<totalNum%(1000000007)<<endl;
    return 0;
}
