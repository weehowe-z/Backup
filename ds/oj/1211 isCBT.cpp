#include <iostream>
using namespace std;
class Node
{
public:

    int element;
    Node* left;
    Node* right;
    Node(int e=0,Node*  l=NULL,Node* r=NULL)
    {
        element=e;
        left=l;
        right=r;
    }
};
class binaryTree
{
private:
    Node* root;
public:
    binaryTree()
    {
        root=new Node;
    }
    ~binaryTree()
    {
        clearhelp(root);
    }
    void clearhelp(Node* root)
    {
        if (root==NULL) return ;
        clearhelp(root->left);
        clearhelp(root->right);
        delete root;
    }
    Node* setLeft(Node* l)
    {
        root->left=l;
        return root;
    }
    Node* setRight(Node* r)
    {
        root->right=r;
        return root;
    }

};
int main()
{
    int root;
    int n,p,q;
    Node** tree;
    cin>>n;
    tree=new Node*[n+1];
    for (int i=0;i<=n;++i) tree[i]=new Node;
    for (int i=1;i<=n;++i){
        cin>>p>>q;
        if (root==p||root==q) root=i;
        if (p!=0) tree[i]->left=tree[p];
        if (q!=0) tree[i]->right=tree[q];
    }
    for (int i=0;i<=n;++i) delete tree[i];
    delete []tree;
    return 0;
}
