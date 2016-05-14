#include "List.h"
#include <cassert>
#include <iostream>
#ifndef LINKLIST_H_INCLUDED
#define LINKLIST_H_INCLUDED
using namespace std;
//by weeohowe.z
//10/18 freelist support
//no assert!  to be designed
//10/30 add reverse
template <typename E>
class Node//with freelist support
{
private:
    static Node<E>* freelist;//reference to freelist head
public:
    E element;//Value
    Node* next;
    //Constructor
    Node(const E& elemval,Node* nextval=NULL) {element=elemval;next=nextval;}
    Node(Node* nextval=NULL){next=nextval;}

    //Overload of new & delete
    void* operator new(size_t)
    {
        if (freelist==NULL) return ::new Node;
        Node<E>* temp=freelist;
        freelist=freelist->next;
        return temp;
    }
    void operator delete (void* ptr)
    {
        ((Node<E>*)ptr)->next=freelist;//put on free list
        freelist=(Node<E>*)ptr;
    }
};
template <typename E>
Node<E>* Node<E>::freelist=NULL;

//LinkList Implementation
template <typename E>
class LList:public List<E>
{
private:
    Node<E>* curr;
    Node<E>* head;
    Node<E>* tail;
    int cnt;

    void init()//initializer
    {
        curr=tail=head=new Node<E>;
        cnt=0;
    }
    void removeall()//return node places
    {
        while (head!=NULL){
            curr=head;
            head=head->next;
            delete curr;
        }
    }
public:
    LList(int size =10) {init();}
    ~LList(){removeall();}
    void print() const;//print List content
    void clear(){removeall();init();} //clear lists

    //insert
    void insert(const E& it)
    {
        curr->next=new Node<E>(it,curr->next);
        if (tail==curr) tail=curr->next;//the special situation
        ++cnt;
    }
    void append(const E& it)
    {
        tail->next=new Node<E>(it,NULL);
        tail=tail->next;
        ++cnt;
    }
    E remove()
    {
        assert(curr->next!=NULL) ;
        E it=curr->next->element;
        Node<E>* tmp=curr->next;
        if (tail==curr->next) tail=curr;
        curr->next=curr->next->next;
        delete tmp;
        --cnt;
        return it;
    }
    void moveToStart()
    {curr=head;}
    void moveToEnd()
    {curr=tail;}
    void prev()
    {
        if(curr==head) return;
        Node<E>* temp=head;
        while(temp->next!=curr) temp=temp->next;
        curr=temp;
    }
    void next()
    {
        if(curr==tail) return;
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
    void reverse()
    {
        if (head==tail) return;
        while (head->next!=tail){
            curr=head->next;
            head->next=curr->next;
            curr->next=tail->next;
            tail->next=curr;
        }
        while (tail->next!=NULL) tail=tail->next;
    }
    void print()
    {
        curr=head;
        while (curr->next!=NULL){
            curr=curr->next;
            cout<<curr->element<<" ";
        }
        cout<<endl;
    }
};
#endif // LINKLIST_H_INCLUDED
