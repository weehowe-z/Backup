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
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) return true;
        else return isSymmetric(root->left, root->right);
    }
    
    bool isSymmetric(TreeNode* p, TreeNode* q){
        if (!p&&!q) return true;
        else if (!p&&q || !q&&p) return false;
        else if (p->val!=q->val) return false;
        else return (isSymmetric(p->left,q->right)&&isSymmetric(p->right,q->left));
    }
};

int main()
{
    Solution s;
    return 0;
}