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
    //Recursive solution
    /**
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> vec;
        if (root == NULL){
            return vec;
        }
        else {
            vec.push_back(root->val);
            vector<int> vecSub = preorderTraversal(root->left);
            if (vecSub.size() != 0){
               vec.insert(vec.end(),vecSub.begin(),vecSub.end());
            }
            vecSub = preorderTraversal(root->right);
             if (vecSub.size() != 0){
               vec.insert(vec.end(),vecSub.begin(),vecSub.end());
            }
            return vec;
        }
    }
    **/

    /**
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> vec;
        stack<TreeNode*> stk;

        if (root != NULL){
            stk.push(root);
        }

        while(!stk.empty()){
            TreeNode* top = stk.top();
            stk.pop();
            vec.push_back(top->val);
            if (top->right != nullptr) stk.push(top->right);
            if (top->left != nullptr) stk.push(top->left);
        }

        return vec;
    }
    **/




};

int main()
{

    return 0;
}
