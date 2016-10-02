#include <iostream>
#include <vector>
#include <stack>
#include <climits>

using namespace std;

 struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
 
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        return isValidBST(root, LONG_MIN, LONG_MAX);
    }
    
    bool isValidBST(TreeNode* root, long min, long max){
        if (root == nullptr) return true;
        if (root->val<=min || root->val>=max) return false;
        //    if (!(((max == INT_MAX)&&(root->val == INT_MAX)&&(min<INT_MAX))||((min == INT_MIN)&&(root->val == INT_MIN)&&(max>INT_MIN)))) return false;
        return isValidBST(root->left, min, root->val)&&isValidBST(root->right, root->val, max);
    }
};

int main()
{
    return 0;
}