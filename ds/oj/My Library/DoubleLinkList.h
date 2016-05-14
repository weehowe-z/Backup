//by weehowe.z
//implement 10/18
//using free list
#ifndef DOUBLELINKLIST_H_INCLUDED
#define DOUBLELINKLIST_H_INCLUDED
#include <iostream>
#include <cassert>
#include "List.h"
using namespace std;
template <typename E>
class Node
{
private:
    static Node<E>* freelist;
public:
    E element;//Value
    Node* next;
    Node* prev;
    //constructor
    Node(const E& it,Node* prevp=NULL,Node* nextp=NULL)
    {
        element=it;
        prev=prevp;
        next=nextp;
    }
    Node(Node* prevp=NULL,Node* nextp=NULL)
    {
        prev=prevp;
        next=nextp;
    }
    //free list
    void* operator new(size_t)
    {
        if (freelist==NULL) return::new Node;
        Node<E>* temp=freelist;
        freelist=freelist->next;
        return temp;
    }
    void operator delete(void* ptr)
    {
        ((Node<E>*)ptr)->next=freelist;
        freelist=(Node<E>*)ptr;
    }
};
template <typename E>
Node<E>* Node<E>::freelist=NULL;

//detail implement
template <typename E>
class DList:public List<E>
{
private:
    Node<E>* curr;
    Node<E>* head;
    Node<E>* tail;
    int cnt;

    void init()//initializer
    {
        head=curr=new Node<E>;
        tail=new Node<E>(0,head,NULL);
        head->next=tail;
        cnt=0;
    }
    void removeall()
    {
        while (head->next!=tail){
            curr=head;
            head=head->next;
            delete curr;
        }
        delete head;
        delete tail;
    }
public:
    DList(int size=10){init();}
    ~DList(){removeall();}
    void print() const;
    void clear(){removeall();init();}//clear up the list

    void insert(const E& it)
    {
        curr->next=curr->next->prev=new Node<E>(it,curr,curr->next);
        ++cnt;
    }
    void append(const E& it)
    {
        tail->prev=tail->prev->next=new Node<E>(it,tail->prev,tail);
        ++cnt;
    }
    E remove()
    {
        assert(curr->next!=tail);
        E it = curr->next->element;
        Node<E>* temp=curr->next;
        curr->next=curr->next->next;
        curr->next->prev=curr;
        delete temp;
        --cnt;
        return it;
    }
    void moveToStart()
    {curr=head;}
    void moveToEnd()
    {curr=tail->prev;}
    void prev()
    {
        if(curr==head) return;
        curr=curr->prev;
    }
    void next()
    {
        if(curr->next==tail) return;
        curr=curr->next;
    }
    int length() const
    {
        return cnt;
    }
    int currtPos() const
    {
        Node<E>*temp=head;
        int cnt=0;
        while(temp!=curr){
            temp=temp->next;
            ++cnt;
        }
        return cnt;
    }
    void moveToPos(int pos)
    {
        assert((pos>=0)&&(pos<=cnt));
        curr=head;
        for (int i=0;i<pos;++i) curr=curr->next;
    }
    const E& getValue() const
    {
        assert(curr->next!=NULL);
        return curr->next->element;
    }
};

#endif // DOUBLELINKLIST_H_INCLUDED
