#ifndef ARRAYBASEDLIST_H_INCLUDED
#define ARRAYBASEDLIST_H_INCLUDED
#include "List.h"
//by weeohowe.z
//no assert!  to be designed
//implementation
template <typename E>
class AList:public List<E>
{
private:
    int maxSize;//size max
    int listSize;//size now
    int curr;//store the position
    E* listArray;//the point to the specific room

    void doubleSpace()
    {
        E*  temp=listArray;
        maxSize*=2;
        listArray =new E[maxSize];
        for (int i=0;i<listSize;++i) listArray[i]=temp[i];
        delete temp;
    }
public:
    AList(int size=20)//constructor
    {
        maxSize=size;
        listSize=curr=0;
        listArray=new E[maxSize];
    }
    AList& operator=(const AList& x)
    {
        if (&x==this) return *this;
        maxSize=x.maxSize;
        curr=0;
        listSize=x.listSize;
        listArray=new E[maxSize];
        for (int i=0;i<maxSize;++i) listArray[i]=x.listArray[i];
        return *this;
    }

    ~AList()//destructor
    {
        delete []listArray;
    }
    void clear()//reinitialize the list
    {
        delete []listArray;
        listSize=curr=0;
        listArray=new E[maxSize];
    }
    void insert(const E& it)
    {
        if (listSize>=maxSize) doubleSpace();
        for (int i=listSize;i>curr;--i) listArray[i]=listArray[i-1];
        listArray[curr]=it;
        ++listSize;
    }
    void append(const E&it)
    {
        if (listSize>=maxSize) doubleSpace();
        listArray[listSize]=it;
        ++listSize;
    }
    E remove()
    {
        //assert((curr>=0)&&(curr<listSize));
        E it=listArray[curr];
        for (int i=curr;i<listSize;++i) listArray[i]=listArray[i+1];
        --listSize;
        return it;
    }
    void moveToStart()
    {curr=0;}
    void moveToEnd()
    {curr=listSize;}
    void prev()
    {
        if(curr!=0)  --curr;
    }
    void next()
    {
        if(curr<listSize) ++curr;
    }
    int length() const
    {
        return listSize;
    }
    int currtPos() const
    {
        return curr;
    }
    void moveToPos(int pos)
    {
       // Assert((pos>=0)&&(pos<=listSize),"Out of range");
        curr=pos;
    }
    const E& getValue() const
    {
        //assert((curr>=0)&&(curr<listSize));
        return listArray[curr];
    }
};


#endif // ARRAYBASEDLIST_H_INCLUDED
