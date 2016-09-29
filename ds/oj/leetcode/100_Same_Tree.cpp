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
    bool isSameTree(TreeNode* p, TreeNode* q) {
        //both empty
        if (!p&&!q) return true;
        else if ( !p&&q || !q&&p ) return false;
        else{
            if (p->val != q->val) return false;
            return (isSameTree(p->left, q->left)&&isSameTree(p->right,q->right));
        }
    }
};

int main()
{
    Solution s;
    return 0;
}