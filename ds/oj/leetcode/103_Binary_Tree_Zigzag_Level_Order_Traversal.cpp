#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        queue<TreeNode*> q;
        vector<vector<int>> result;
        bool zigflag = false;
        if (root != nullptr) q.push(root);
        while (true){
            int size = q.size();
            vector<int> vec;
            for (int i = 0 ; i < size ; ++ i){
                TreeNode* p = q.front();
                q.pop();
                vec.push_back(p->val);
                if (p->left != nullptr) q.push(p->left);
                if (p->right != nullptr) q.push(p->right);
            }
            
            if (zigflag){
                reverse(vec.begin(),vec.end());
            }
            zigflag = !zigflag;
            if (!vec.empty()) result.push_back(vec);
            if (q.empty()) break;
        }
        return result;
    }
};

int main()
{
    Solution s;
    return 0;
}