#include <iostream>
using namespace std;

class Node
{
 public:
    int data;
    Node* next;
    Node(int num=0,Node* n=NULL)
    {
        data=num;
        next=n;
    }

};

class LList
{
public:
    Node* head;
    Node* tail;
    LList()
    {
        head=tail=new Node();
    }
    ~LList()
    {
        while (head->next!=NULL)
        {
            Node* tmp;
            tmp=head;
            head=head->next;
            delete tmp;
        }
        delete head;
    }
    void insert(int num)
    {
        tail->next=new Node(num,NULL);
        tail=tail->next;
    }
    void print()
    {
        Node* tmp=head;
        while (tmp->next!=NULL)
        {
            tmp=tmp->next;
            cout<<tmp->data<<" ";
        }
    }
    void reverse()
    {
        Node* tmpt=tail;
        Node* tmph=head->next;
        while (head->next!=tmpt){
            tail->next=head->next;
            tail=tail->next;
            head->next=head->next->next;
            tail->next=NULL;
        }
    }
};
int main()
{
    LList a;
    a.insert(5);
    a.insert(7);
    a.insert(9);
    a.insert(10);
    a.print();
    cout<<endl;
    a.reverse();
    a.print();
    return 0;
}
