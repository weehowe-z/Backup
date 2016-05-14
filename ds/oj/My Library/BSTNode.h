#ifndef BSTNODE_H_INCLUDED
#define BSTNODE_H_INCLUDED
#include "BinNode.h"
template <typename Key,typename E>
class BSTNode: public BinNode<E>
{
private:
    E e;
    Key k;
    BSTNode* lc;
    BSTNode* rc;
public:
    //two constructor
    BSTNode()
    {
        lc=rc=NULL;
    }
    BSTNode(Key K,E it,lc=l,rc=r)
    {
        k=K;
        e=it;
        lc=l;
        rc=r;
    }
    ~BSTNode(){}

    //Functions
    E& element()
    {
        return e;
    }
    void setElement(const E& it)
    {
        e=it;
    }
    Key& key()
    {
        return k;
    }
    void setKey(const Key&K)
    {
        k=K;
    }

    inline BSTNode* left()const
    {
        return lc;
    }
    inline BSTNode* right()const
    {
        return rc;
    }
    void setLeft(const BinNode<E>* b)
    {
        lc=(BSTNode* )b;
    }
    void setRight(const BinNode<E>* b)
    {
        rc=(BSTNode*)b;
    }

    bool isLeft(){return (lc==NULL)&&(rc==NULL);}
};


#endif // BSTNODE_H_INCLUDED
