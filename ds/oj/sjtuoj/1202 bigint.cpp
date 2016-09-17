#include <iostream>
using namespace std;
class Node
{
public:
    int num;
    Node* prev;
    Node* next;
    Node(int n,Node*prevval,Node* nextval)
    {
        num=n;
        prev=prevval;
        next=nextval;
    }
    Node()
    {
        prev=NULL;
        next=NULL;
    }
};
class bigInt
{
friend istream& operator>>(istream &is,bigInt& x);
friend ostream& operator<<(ostream &os,const bigInt&x);
friend bigInt* operator+(const bigInt& x,const bigInt& y);
private:
    Node* head;
    Node* tail;
    int length;
public:
    bigInt()
    {
        tail=new Node(0,NULL,NULL);
        head=new Node(0,NULL,tail);
        tail->prev=head;
        length=0;
    }
    ~bigInt()
    {
        Node* temp;
        while (head->next!=NULL){
            temp=head;
            head=head->next;
            delete temp;
        }
        delete head;
    }
    void headAppend(const int n)
    {
        Node* tmp=head->next;
        head->next=new Node(n,head,head->next);
        tmp->prev=head->next;
        ++length;
    }
    void append(const int n)
    {
        Node* tmp=tail->prev;
        tmp->next=new Node(n,tail->prev,tail);
        tail->prev=tmp->next;
        ++length;
    }
    void print()
    {
       Node* p=head;
        while(p->next!=tail){
        p=p->next;
        cout<<p->num;
    }
    cout<<endl;
    }
};
istream& operator>>(istream &is,bigInt& x)
{
    char num[1000001];
    is.getline(num,1000001);
    int i=0;
    while (num[i]!='\0') {x.headAppend(num[i]-'0');++i;}
    return is;
}
ostream& operator<<(ostream &os,const bigInt&x)
{
    Node* p=x.tail;
    while(p->prev!=x.head){
        p=p->prev;
        os<<p->num;
    }
    os<<endl;
}
bigInt* operator+(const bigInt& x,const bigInt& y)
{
    bigInt* z;
    Node* p=x.head;
    Node* q=y.head;
    z=new bigInt;
    int l=min(x.length,y.length);
    int carry=0;
    for (int i=0;i<l;++i){
        p=p->next;
        q=q->next;
        z->append((p->num+q->num+carry)%10);
        carry=(p->num+q->num+carry)/10;
    }
    if (x.length>l){
        for (int i=l;i<x.length;++i){
            p=p->next;
            z->append((p->num+carry)%10);
            carry=(p->num+carry)/10;
        }
    }
    if (y.length>l){
            for (int i=l;i<y.length;++i){
            q=q->next;
            z->append((q->num+carry)%10);
            carry=(q->num+carry)/10;
        }
    }
    if (carry>0) z->append(carry);
    return z;
}
int main()
{
    bigInt a,b;
    bigInt* c;
    cin>>a;
    cin>>b;
    c=a+b;
    cout<<(*c);
    delete c;
    return 0;
}
