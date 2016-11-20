#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED
#include <iostream>
#include "LinkedQueue.h"
using namespace std;
template <typename K,typename E>
class BSTNode
{
public:
    K key;
    E element;
    BSTNode<K,E>* left;
    BSTNode<K,E>* right;
    BSTNode(const K& k,const E& e,BSTNode<K,E>* lc=NULL,BSTNode<K,E>* rc=NULL)
    {
        key=k;
        element=e;
        left=lc;
        right=rc;
    }
    bool isLeaf()
    {
        if (left==NULL&&right==NULL) return true;
        return false;
    }
    void setLeft(BSTNode<K,E>* root)
    {
        left=root;
    }
    void setRight(BSTNode<K,E>* root)
    {
        right=root;
    }
};
template <typename K,typename E>
class BST
{
private:
    BSTNode<K,E>* root;
    //help method
    void clearhelp(BSTNode<K,E>* root)
    {
        if (root==NULL) return;
        clearhelp(root->left);
        clearhelp(root->right);
        delete root;
    }
    BSTNode<K,E>* inserthelp(BSTNode<K,E>* root,const K& key,const E& element)
    {
        if (root== NULL) return new BSTNode<K,E>(key,element);
        if (key<root->key) root->setLeft(inserthelp(root->left,key,element));
            else root->setRight(inserthelp(root->right,key,element));
        return root;
    }
    E findhelp(BSTNode<K,E>* root,const K& key)
    {
        if (root==NULL) return E(NULL);
        if (root->key<key) return findhelp(root->right,key);
            else if (root->key>key) return findhelp(root->left,key);
            else return  root->element;
    }
    BSTNode<K,E>* deleteLessThan(BSTNode<K,E>*root,const K&key)
    {
        if (root==NULL) return root;
        if(root->key<key){
            BSTNode<K,E>* tmp;
            tmp=root->right;
            root->right=NULL;
            clearhelp(root);
            root=tmp;
            return deleteLessThan(root,key);
        }
            else if (root->key>=key){
                root->setLeft(deleteLessThan(root->left,key));
            }
        return root;
    }
    BSTNode<K,E>* deleteLargerThan(BSTNode<K,E>*root,const K&key)
    {
        if (root==NULL) return root;
        if(root->key>key){
            BSTNode<K,E>* tmp;
            tmp=root->left;
            root->left=NULL;
            clearhelp(root);
            root=tmp;
            return deleteLargerThan(root,key);
        }
            else if (root->key<=key){
                root->setRight(deleteLargerThan(root->right,key));
            }
        return root;
    }
    void rangeSearch(BSTNode<K,E>* root,const K&key1,const K&key2,LQueue<K>& q)
    {
        if (root==NULL) return;
        rangeSearch(root->left,key1,key2,q);
        if (root->key<=key2&&root->key>=key1) q.enqueue(root->key);
        rangeSearch(root->right,key1,key2,q);
    }
    BSTNode<K,E>* deletemin(BSTNode<K,E>* root)
    {
        if (root->left==NULL) return root->right;
            else {
                root->setLeft(deletemin(root->left));
                return root;
            }
    }
    BSTNode<K,E>* getmin(BSTNode<K,E>* root)
    {
        if (root->left==NULL) return root;
            else return getmin(root->left);
    }
    BSTNode<K,E>* removehelp(BSTNode<K,E>* root,const K&key)
    {
        if (root==NULL) return E(NULL);
        if (root->key>key)  root->setLeft(removehelp(root->left,key));
            else if (root->key<key) root->setRight(removehelp(root->right,key));
            //if have found
            else {
                BSTNode<K,E>* tmp=root;
                if (root->left==NULL) {root=root->right;delete tmp;}
                    else if (root->right==NULL) {root=root->left;delete tmp;}
                    else{
                        tmp=getmin(root->right);
                        root->element=tmp->element;
                        root->key=tmp->key;
                        root->setRight(deletemin(root->right));
                        //delete tmp;
                    }
            }
            return root;
    }
    int getdepthhelp(BSTNode<K,E>* root,const K&key)
    {
        static int depth=1;
        if (root==NULL) return 0;
        if (root->key<key) depth= 1+getdepthhelp(root->right,key);
            else if (root->key>key) depth=1+ getdepthhelp(root->left,key);
        return depth;
    }
    int getNodeCounthelp(BSTNode<K,E>* root)
    {
        static int nodecount=0;
        if (root==NULL) return 0;
        nodecount=1+getNodeCounthelp(root->left)+getNodeCounthelp(root->right);
        return nodecount;
    }
    void printhelp(BSTNode<K,E>* root,int level)
    {
        if (root==NULL) return;
        printhelp(root->right,level+1);
        for (int i=0;i<level;++i) cout<<"  ";
        cout<<root->key<<endl;
        printhelp(root->left,level+1);
    }
    void preorderhelp(BSTNode<K,E>* root)
    {
        if (root==NULL) return;
        cout<<root->element<<" ";
        preorderhelp(root->left);
        preorderhelp(root->right);
    }
    void inorderhelp(BSTNode<K,E>* root)
    {
        if (root==NULL) return;
        inorderhelp(root->left);
        cout<<root->element<<" ";
        inorderhelp(root->right);
    }
public:
    BST()
    {
        root=NULL;
    }
    ~BST()
    {
        clearhelp(root);
    }
    void clear()
    {
        clearhelp(root);
    }
    void insert(const K& key,const E& element)
    {
        root=inserthelp(root,key,element);
    }
    E find(const K& key)
    {
        E tmp=findhelp(root,key);
        return tmp;
    }
    E remove(const K& key)
    {
        E tmp=findhelp(root,key);
        if (tmp!=E(NULL)){
            root=removehelp(root,key);
        }
        return tmp;
    }
    void removeLessThan(const K&key)
    {
        root=deleteLessThan(root,key);
    }
    void removeLargerThan(const K&key)
    {
        root=deleteLargerThan(root,key);
    }
    void removeBetween(const K&key1, const K&key2)
    {
        LQueue<K> removeList;
        rangeSearch(root,key1,key2,removeList);
        while (removeList.length()>0){
            remove(removeList.dequeue());
        }
    }
    int getdepth(const K&key)
    {
        E tmp=findhelp(root,key);
        if (tmp!=E(NULL)){
            return getdepthhelp(root,key);
        }
        return -1;
    }
    int getNodeCount()
    {
        return getNodeCounthelp(root);
    }
    void print()
    {
        printhelp(root,0);
        cout<<endl;
    }
    void printPreorder()
    {
        cout<<"postorder: ";
        preorderhelp(root);
        cout<<endl;
    }
    void printInorder()
    {
        cout<<"inorder: ";
        inorderhelp(root);
        cout<<endl;
    }
};

#endif // BST_H_INCLUDED
