#ifndef BINNODE_H_INCLUDED
#define BINNODE_H_INCLUDED
//binary tree node ADT
template <typename E>
class BinNode
{
private:
    void operator=(const BinNode&) {}//protect assignment
    BinNode(const BinNode&) {}//protect copy constructor
public:
    BinNode();//default constructor
    virtual ~BinNode();//base class destructor

    virtual E& element() = 0;//return the element;
    virtual void setElement(const E&) = 0;
    virtual BinNode* left() const=0;  //return left sub tree;
    virtual BinNode* right() const=0; //return right sub tree;
    virtual void setLeft(BinNode*) =0;
    virtual void setRight(BinNode* )=0;
    virtual bool isLeaf() =0;
};


#endif // BINNODE_H_INCLUDED
