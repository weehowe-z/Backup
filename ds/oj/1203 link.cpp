#include <iostream>
using namespace std;

template<typename E>
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
    Node()
    {
        next=NULL;
    }
};
template <typename E>
class LList
{
template <typename U>
friend LList<U>* operator+(const LList<U>& list1,const LList<U>& list2);
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
        delete head;
    }
    void append(const E it)
    {
        tail->next=new Node<E>(it,tail->next);
        tail=tail->next;
    }
    void print() const
    {
        Node<E>* temp=head;
        while (temp->next!=NULL)
        {
            temp=temp->next;
            cout<<temp->element<<" ";
        }
        cout<<endl;
    }

};
template <typename E>
LList<E>* operator+(const LList<E>& list1,const LList<E>& list2)
{
    LList<E>* newList;
    newList=new LList<E>;
    Node<E>* p;
    p=list1.head;
    while (p->next!=NULL){
        p=p->next;
        newList->append(p->element);
    }
    p=list2.head;
    while (p->next!=NULL){
        p=p->next;
        newList->append(p->element);
    }
    return newList;

}
int main()
{
    char signal[7];
    cin.getline(signal,7);
    int num1,num2;
    cin>>num1>>num2;
    switch(signal[0])
    {
    case 'i':
        {LList<int> a,b;
        LList<int> *c;
        int d;
        for (int i=0;i<num1;++i) {cin>>d;a.append(d);}
        for (int i=0;i<num2;++i) {cin>>d;b.append(d);}
        c=a+b;
        c->print();
        break;}
    case 'd':
        {LList<double> e,f;
        LList<double> *g;
        double h;
        for (int i=0;i<num1;++i) {cin>>h;e.append(h);}
        for (int i=0;i<num2;++i) {cin>>h;f.append(h);}
        g=e+f;
        g->print();
        break;}
    case 'c':
        {LList<char> x,y;
        LList<char> *z;
        char a1;
        for (int i=0;i<num1;++i) {cin>>a1;x.append(a1);}
        for (int i=0;i<num2;++i) {cin>>a1;y.append(a1);}
        z=x+y;
        z->print();}
    }

    return 0;
}
