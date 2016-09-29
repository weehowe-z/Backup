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
    bool isBalanced(TreeNode* root) {
        return (getHeightWithBalance(root)>=0);
    }
    
    int getHeightWithBalance(TreeNode* root){
        if (root == nullptr) return 0;
        
        int heightLeft = getHeightWithBalance(root->left);
        if (heightLeft == -1) return -1;
        
        int heightRight = getHeightWithBalance(root->right);
        if (heightRight == -1) return -1;
        
        if (abs(heightLeft - heightRight) > 1) return -1;
        else{
            return (max(heightLeft,heightRight)+1);
        }
    }
};

int main()
{
    Solution s;
    s.isBalanced(nullptr);
    return 0;
}
