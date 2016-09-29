#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <cmath>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
public:
    void flatten(TreeNode* root) {
        stack<TreeNode*> stk;
        TreeNode* prev = nullptr;
        
        if (root != NULL){
            stk.push(root);
        }

        while(!stk.empty()){
            TreeNode* top = stk.top();
            stk.pop();
            
            if (prev != nullptr) {
                prev->left = nullptr;
                prev->right = top;
            }
            
            prev = top;
            
            if (top->right != nullptr) stk.push(top->right);
            if (top->left != nullptr) stk.push(top->left);
        }

    }
};

int main()
{
    Solution s;
    s.isBalanced(nullptr);
    return 0;
}
