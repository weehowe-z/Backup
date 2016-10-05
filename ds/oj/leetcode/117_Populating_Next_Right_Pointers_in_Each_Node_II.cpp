#include <iostream>
#include <queue>
using namespace std;


struct TreeLinkNode {
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

class Solution {
public:
    void connect(TreeLinkNode *root) {
        queue<TreeLinkNode*> q;
        
        if (root !=  nullptr) q.push(root);
        
        while(true){
            const int num = q.size();
            for (int i = 0; i < num; ++i){
                TreeLinkNode* p = q.front();
                
                q.pop();
                if (i != num -1) p->next = q.front();
                else p->next = nullptr;
                
                if (p->left) q.push(p->left);
                if (p->right) q.push(p->right);
                
            }
            
            if (q.empty()) break;
        }
    }   
};

int main()
{
    Solution s;
    return 0;
}