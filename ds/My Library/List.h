#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
//ADT
template <typename E>
class List
{
private:
    void operator=(const List&) {}//protect assignment
    List(const List&) {}//protect copy constructor
public:
    List() {}//default constructor
    virtual ~List() {}// base class destructor

    virtual void clear() = 0;
    virtual void insert(const E& element)= 0;//insert at current position
    virtual void append(const E& element)=0;//insert at the end;
    virtual E remove()=0; //remove at the end;
    virtual void moveToStart()=0;
    virtual void moveToEnd()=0;
    virtual void prev()=0;//one step left
    virtual void next()=0;//ons step right
    virtual int length() const=0;
    virtual int currtPos() const=0;//return current position
    virtual void moveToPos(int pos)=0;
    virtual const E& getValue() const=0;
};
#endif // LIST_H_INCLUDED
