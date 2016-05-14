#ifndef LINKEDQUEUE_H_INCLUDED
#define LINKEDQUEUE_H_INCLUDED
template <typename E>
class Node
{
public:
    E element;//Value
    Node* next;
    //Constructor
    Node(const E& elemval,Node* nextval=NULL) {element=elemval;next=nextval;}
    Node(Node* nextval=NULL){next=nextval;}

};


template <typename E>
class LQueue
{
private:
    Node<E>* front;
    Node<E>* rear;
    int size;
public:
    LQueue()//constructor
    {
        front=rear=new Node<E>;
        size =0;
    }
    ~LQueue()
    {
        clear();
        delete front;
    }
    void clear()
    {
        while(front->next!=NULL){
            rear=front;
            front=front->next;
            delete rear;
        }
        rear= front;
        size=0;
    }
    void enqueue(const E& it)
    {
        rear->next=new Node<E>(it,NULL);
        rear=rear->next;
        ++size;
    }
    E dequeue()
    {
        E it =front->next->element;
        Node<E>* ltemp= front->next;
        front->next=ltemp->next;
        if (rear==ltemp) rear=front;
        delete ltemp;
        size--;
        return it;
    }
    int length() const
    {
        return size;
    }
};



#endif // LINKEDQUEUE_H_INCLUDED
