#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> vec;
        
        if (root == nullptr){
            return vec;
        }
        vector<int> vec2;
        
        vec2 = postorderTraversal(root->left);
        if (!vec2.empty()) vec.insert(vec.end(),vec2.begin(),vec2.end());
        vec2 = postorderTraversal(root -> right);
        if (!vec2.empty()) vec.insert(vec.end(),vec2.begin(),vec2.end());
        vec.push_back(root->val);
        return vec;
    }
};

int main()
{
    Solution s;
    return 0;

}
