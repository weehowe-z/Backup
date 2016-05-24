#include <iostream>

using namespace std;
class fraction
{
friend ostream& operator<<(ostream& os,const fraction& x);
friend bool operator<=(const fraction& x,const fraction& y);
friend bool operator==(const fraction& x,const fraction& y);
private:
int fenzi;
int fenmu;
void reduceFraction()
{
        bool flag =false;
        for (int i=2; i<=fenzi; ++i) {
                if (fenmu%i==0&&fenzi%i==0) {
                        fenzi/=i;
                        fenmu/=i;
                        flag =true;
                        break;
                }
        }
        if (flag) reduceFraction();
}
public:
fraction(int fz=1,int fm=1)
{
        fenzi=fz;
        fenmu=fm;
        reduceFraction();
}
};
ostream& operator<<(ostream& os,const fraction& x)
{
        os<<x.fenzi<<"/"<<x.fenmu;
        return os;
}
bool operator<=(const fraction& x,const fraction& y)
{
        if (x.fenzi*y.fenmu<=x.fenmu*y.fenzi) return true;
        else return false;
}
bool operator==(const fraction& x,const fraction& y)
{
        if (x.fenzi*y.fenmu==x.fenmu*y.fenzi) return true;
        else return false;
}

class Node
{
public:
fraction f;
Node* next;
Node(fraction fra,Node* n)
{
        f=fra;
        next=n;
}
Node()
{
        next=NULL;
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
        while (head->next!=NULL) {
                temp=head;
                head=head->next;
                delete temp;
        }
        delete head;
}
void insert(const fraction fra)
{
        if (head->next==NULL) {
                head->next=new Node(fra,NULL);
                return;
        }
        Node* temp=head;
        while (temp->next!=NULL) {
                if (fra<=temp->next->f) break;
                temp=temp->next;
        }

        if (temp->next==NULL||(temp->next!=NULL&&!(fra==temp->next->f))) temp->next=new Node(fra,temp->next);
}
void print()
{
        Node* temp=head;
        while (temp->next!=NULL) {
                temp=temp->next;
                cout<<temp->f<<endl;
        }
        //cout<<endl;
}
};
int main()
{
        LList c;
        int k;
        cin>>k;
        for (int i=1; i<=k; ++i) {
                for (int j=0; j<=i; ++j)
                        c.insert(fraction(j,i));
        }
        c.print();
        return 0;
}
