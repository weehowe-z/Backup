#include <iostream>
using namespace std;
class Node
{
public:
    int element;
    Node* left;
    Node* right;
    Node(int n=0,Node* l=NULL,Node* r=NULL)
    {
        element=0;
        left=l;
        right=r;
    }
};
class binaryTree
{
private:
    Node* root;
    void clearhelp(Node* root)
    {
        if (root==NULL) return;
        clearhelp(root->left);
        clearhelp(root->right);
        delete root;
    }
    int findDegreeOnehelp(Node* root)
    {
        if (root==NULL) return 0;
        if (root->left!=NULL&&root->right!=NULL) return findDegreeOnehelp(root->left)+findDegreeOnehelp(root->right);
        if (root->left==NULL&&root->right!=NULL) return findDegreeOnehelp(root->right)+1;
        if (root->left==NULL&&root->left!=NULL) return findDegreeOnehelp(root->left)+1;
        return 0;
    }
public:
    binaryTree()
    {
        root=new Node;
    }
    ~binaryTree()
    {
        clearhelp(root);
    }
    int findDegreeOne()
    {
        return findDegreeOnehelp(root);
    }

};
int main()
{
    binaryTree a;
    cout<<a.findDegreeOne();
    return 0;
}
