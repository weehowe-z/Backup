#ifndef ARRAYBASEDSTACK_H_INCLUDED
#define ARRAYBASEDSTACK_H_INCLUDED
#include <cassert>
#include "Stack.h"
using namespace std;
template <typename E>
class AStack:public Stack<E>
{
private:
    int maxSize;
    int top;
    E* listArray;
    void doubleSpace()
    {
        cout<<"Space Exhausted doubleSpacing......\n";
        E*  temp=listArray;
        maxSize*=2;
        listArray =new E[maxSize];
        for (int i=0;i<top;++i) listArray[i]=temp[i];
        delete temp;

    }
public:
    AStack(int size=10)
    {
            maxSize=size;
            top=0;
            listArray=new E[size];
    }
    ~AStack()
    {
        delete []listArray;
    }

    void clear()
    {
        top=0;
    }
    void push(const E&it)
    {
        if (top==maxSize) doubleSpace();
        listArray[top++]=it;
    }
    E pop()
    {
        if (top==0){cout<<"the stack is empty\n";assert(false);}
        return listArray[--top];
    }
    const E& topValue() const
    {
        if (top==0){cout<<"the stack is empty\n";assert(false);}
        return listArray[top-1];
    }
    int length() const { return top;}
};

#endif // ARRAYBASEDSTACK_H_INCLUDED
