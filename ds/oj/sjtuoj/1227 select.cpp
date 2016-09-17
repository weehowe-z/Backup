#include <iostream>
using namespace std;
template <typename E>
class Node
{
public:
    E element;
    Node<E>* next;
    Node(E e,Node<E>* n)
    {
        element=e;
        next=n;
    }
    Node(){next=NULL;}
};

template <typename E>
class LList
{
  //  friend void insertionSort(Node<E>* phead);
private:
    Node<E>* head;
    Node<E>* tail;
public:
    LList()
    {
        head=tail=new Node<E>;
    }
    ~LList()
    {
        Node<E>* temp;
        while (head->next!=NULL){
            temp=head;
            head=head->next;
            delete temp;
        }
    }
    void insert(const E it)
    {
        tail->next=new Node<E>(it,NULL);
        tail=tail->next;
    }
    void print()
    {
        tail=head;
        while (tail->next!=NULL){
            tail=tail->next;
            cout<<tail->element<<" ";
        }
        cout<<endl;
    }
    void insertionSort()
{
    if (head->next==NULL||head->next->next==NULL) return;
    Node<E>* p;
    Node<E>* q;
    Node<E>* r;
    p=head;
    while (p->next!=NULL){
        r=p;
        p=p->next;
        q=head;
        while (q->next!=p){
            if (p->element<q->next->element){
                    r->next=p->next;
                    p->next=q->next;
                    q->next=p;
                    p=r;
                    break;
            }
            q=q->next;
        }
    }
}
};

int main()
{
    LList<int> a;
    int n,x;
    cin>>n;
    for (int i=0;i<n;++i){
        cin>>x;
        a.insert(x);
    }
    a.insertionSort();
    a.print();
    return 0;
}
