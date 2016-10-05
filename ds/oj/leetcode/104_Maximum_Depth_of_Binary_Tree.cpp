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
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        else if (root->right == nullptr) return maxDepth(root->left) +1;
        else if (root->left == nullptr) return maxDepth(root->right) +1;
        else return max(maxDepth(root->left),maxDepth(root->right))+1;
    }
};

int main()
{
    return 0;
}