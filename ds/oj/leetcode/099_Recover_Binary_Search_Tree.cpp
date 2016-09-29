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

    void recoverTree(TreeNode* root) {
        vector<TreeNode*> vec;
        stack<TreeNode*> stk;
        TreeNode* p = root;

        while (!stk.empty() || p != nullptr){
            if (p != nullptr){
                stk.push(p);
                p = p -> left;
            } else{
                p = stk.top();
                stk.pop();
                vec.push_back(p);
                p = p -> right;
            }
        }
        
        TreeNode* p1 = nullptr;
        TreeNode* p21 = nullptr;
        TreeNode* p22 = nullptr;
        for (int i = 0 ; i<vec.size(); ++i){
            if (i == 0){
                if (vec[i]->val > vec[i+1]->val) p1 = vec[i];
                
            }else if (i == vec.size()-1){
                if (vec[i-1]->val > vec[i]->val) p21 = vec[i];
            }else {
                if (p1 == nullptr){
                    if ((vec[i-1]->val < vec[i]->val) && (vec[i+1]->val < vec[i]->val)) p1 = vec[i];
                }
                
                if (p21 == nullptr){
                    if ((vec[i-1]->val > vec[i]->val) && (vec[i+1]->val > vec[i]->val)) p21 = vec[i];
                }else {
                    if ((vec[i-1]->val > vec[i]->val) && (vec[i+1]->val > vec[i]->val)) p22 = vec[i];
                }
                
                
            }
            
            if ((p1 != nullptr)&&(p21 != nullptr)&&(p22 != nullptr)) break;
        }
        
        if (p22 == nullptr) swap(p1->val, p21->val);
        else swap(p1->val, p22->val);
//        for (TreeNode* p: vec){
//            cout<<p->val<<" ";
//        }
//        cout<<endl;
        return;
    }
};

int main()
{
    Solution s;
    vector<int> tree = {146,71,-13,55,-1,231,399,321,-1,-1,-1,-1,-1,-33};
    vector<TreeNode*> treeVec;

    int len = tree.size();

    for (int x: tree){
        cout<<x<<endl;
        if (x == -1) treeVec.push_back(nullptr);
        else{
            TreeNode* node = new TreeNode(x);
            treeVec.push_back(node);
        }
    }
    
    for (int i = 0; i<len; ++i){
        if (2*i+1 > len -1) break;
        if (treeVec[i] == nullptr) continue; 
        treeVec[i]->left = treeVec[2*i+1];
        treeVec[i]->right = treeVec[2*i+2];
    }
    
    cout<<"BEGIN"<<endl;
    s.recoverTree(treeVec[0]);
    return 0;
}
