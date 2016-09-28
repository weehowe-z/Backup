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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> vec;
        if (root == NULL){
            return vec;
        }
        else {
            vector<int> vecSub = inorderTraversal(root->left);
            if (vecSub.size() != 0){
               vec.insert(vec.end(),vecSub.begin(),vecSub.end());
            }
            vec.push_back(root->val);
            vecSub = inorderTraversal(root->right);
             if (vecSub.size() != 0){
               vec.insert(vec.end(),vecSub.begin(),vecSub.end());
            }
            return vec;
        }
    }
    **/

//
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> vec;
        stack<TreeNode*> stk;
        TreeNode* p = root;


        while (!stk.empty() || p != nullptr){
            if (p != nullptr){
                stk.push(p);
                p = p -> left;
            } else{
                p = stk.top();
                stk.pop();
                vec.push_back(p->val);
                p = p -> right;
            }
        }
        return vec;
    }
//




};

int main()
{

    return 0;
}
