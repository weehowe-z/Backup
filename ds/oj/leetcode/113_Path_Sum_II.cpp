#include <iostream>
#include <vector>
#include <stack>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
 
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) { 
        vector<int> vec;
        vector<vector<int>> rst;
        hasPathSum(root,sum,vec,rst);
        return rst;
    }
    
    void hasPathSum(TreeNode* root, int sum, vector<int> vec, vector<vector<int>> &rst) {
        if (root == nullptr) return;
        
        vec.push_back(root->val);
        
        if (!root->left && !root->right && root->val == sum) {
            rst.push_back(vec);
            return;
        }
        
        hasPathSum(root->left, sum-root->val, vec, rst);
        hasPathSum(root->right, sum-root->val, vec, rst);
    }
};