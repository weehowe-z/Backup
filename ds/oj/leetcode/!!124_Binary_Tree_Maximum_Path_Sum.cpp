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
    int maxPathSum(TreeNode* root) {
        return max(max(maxPathSum(root->left), maxPathSum(root->right)),0);
    }
};