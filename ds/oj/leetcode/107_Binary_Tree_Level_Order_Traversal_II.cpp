#include <iostream>
#include <stack>
#include <vector>
#include <queue>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        queue<TreeNode*> q;
        stack<vector<int>> stk;
        vector<vector<int>> result;
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
            if (!vec.empty()) stk.push(vec);
            if (q.empty()) break;
        }
        
        while(!stk.empty()){
            result.push_back(stk.top());
            stk.pop();
        }
        return result;
    }
};