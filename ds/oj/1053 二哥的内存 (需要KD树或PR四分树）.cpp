#include <iostream>
using namespace std;
class Node
{
public:
    int num;
    int x;
    int y;
    Node* next;
    Node(int n=0,int xs=0,int ys=0,Node* nextVal=NULL)
    {
        num=n;
        x=xs;
        y=ys;
        next=nextVal;
    }
};
class LList
{
private:
    Node* head;
    Node* tail;
public:
    LList()
    {
        head=tail=new Node;
    }
    ~LList()
    {
        Node* temp;
        while (head->next!=NULL){
            temp=head;
            head=head->next;
            delete temp;
        }
        delete head;
    }
    void append(const int n,const int x,const int y)
    {
        tail->next=new Node(n,x,y,tail->next);
        tail=tail->next;
    }
    bool hasNumber(const int x,const int y)
    {
        Node* temp=head;
        while (temp->next!=NULL){
            temp=temp->next;
            if (temp->x==x&&temp->y==y) return true;
        }
        return false;
    }
    void print(const int x,const int y)
    {
        if (hasNumber(x,y)){
             Node* temp=head;
            while (temp->next!=NULL){
                temp=temp->next;
                if (temp->x==x&&temp->y==y) cout<<temp->num<<endl;
            }
        }
            else cout<<0<<endl;
    }
    void changeRow(const int x1,const int x2)
    {
        Node* temp=head;
        while (temp->next!=NULL){
            temp=temp->next;
            if (temp->x==x1) temp->x=x2;
                else if (temp->x==x2) temp->x=x1;
        }
    }
     void changeCol(const int y1,const int y2)
    {
        Node* temp=head;
        while (temp->next!=NULL){
            temp=temp->next;
            if (temp->y==y1) temp->y=y2;
                else if (temp->y==y2) temp->y=y1;
        }
    }
};
int main()
{
    int n,m,x,y,z,op;
    cin>>n;
    LList A;
    for (int i=0;i<n;++i){
        cin>>x>>y>>z;
        A.append(z,x,y);
    }
    cin>>m;
    for (int i=0;i<m;++i){
        cin>>op>>x>>y;
        switch(op)
        {
            case 0:
                {A.changeRow(x,y);break;}
            case 1:
                {A.changeCol(x,y);break;}
            case 2:
                A.print(x,y);
        }
    }
    return 0;
}
