#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
template <typename E>
class Stack
{
private:
    void operator=(const Stack&) {}//protect assignment
    Stack(const Stack& ){}//protect copy constructor
public:
    Stack(){}
    virtual ~Stack(){}

    virtual void clear() =0;
    virtual void push(const E& it) = 0;
    virtual E pop()=0;
    virtual const E& topValue()const=0;
    virtual int length() const=0 ;
};

#endif // STACK_H_INCLUDED
