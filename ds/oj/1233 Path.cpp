#include <iostream>
#define INFINITE 9999999
#define NILL -1
#define UNVISITED 0
#define VISITED 1
using namespace std;
template <typename E>
class Node
{
public:
    E element;
    Node<E>* next;
    Node()
    {
        next=NULL;
    }
    Node(E e,Node<E>* n)
    {
        element=e;
        next=n;
    }
};
template <typename E>
class LList
{
public:
    Node<E>* head;
    Node<E>* tail;
    int length;
    LList()
    {
        length=0;
        head=tail=new Node<E>;
    }
 ~ LList()
    {
        Node<E>* tmp;
        while (head->next!=NULL){
            tmp=head;
            head=head->next;
            delete tmp;
        }
        delete head;
    }
    void append(const E it)
    {
        tail->next=new Node<E>(it,NULL);
        tail=tail->next;
        ++length;
    }
    E headremove()
    {
        Node<E>* tmp=head->next;
        E result=tmp->element;
        head->next=tmp->next;
        delete tmp;
        --length;
        if (length==0) tail=head;
        return result;
    }
    void print()
    {
        Node<E>* p=head;
        while (p->next!=NULL){
            p=p->next;
            cout<<p->element<<" ";
        }
    }
};

template <typename E>
class LQueue
{
public:
    int length;
    LList<E>* queue;
    LQueue()
    {
        length=0;
        queue=new LList<E>;
    }
    ~LQueue()
    {
        delete queue;
    }
    void enqueue(const E it)
    {
        queue->append(it);
        ++length;
    }
    E dequeue()
    {
        E result=queue->headremove();
        --length;
        return result;
    }
};
class Edge
{
public:
    int weight;
    int vertex;
    Edge(int w=INFINITE,int v=NILL)
    {
        weight=w;
        vertex=v;
    }
};
class Graphl
{
private:
    int numVertex;
    int *mark;
    LList<Edge>** adjList;
public:
    Graphl(int n)
    {
        numVertex=n;
        adjList=new LList<Edge>*[numVertex];
        for (int i=0;i<numVertex;++i) adjList[i]=new LList<Edge>;
        mark=new int[numVertex];
        for (int i=0;i<numVertex;++i) mark[i]=UNVISITED;
    }
    ~Graphl()
    {
        for (int i=0;i<numVertex;++i) delete adjList[i];
        delete []adjList;
        delete []mark;
    }
    bool isEdge(int v1,int v2)
    {
        Node<Edge>* tmp;
        tmp=adjList[v1]->head;
        while (tmp->next!=NULL){
            tmp=tmp->next;
            if (tmp->element.vertex==v2) return true;
        }
        return false;
    }
    int getWeight(int v1,int v2)
    {
        Node<Edge>* tmp;
        tmp=adjList[v1]->head;
        while (tmp->next!=NULL){
            tmp=tmp->next;
            if (tmp->element.vertex==v2) return tmp->element.weight;
        }
        return INFINITE;
    }
    void setEdge(int v1,int v2,int weight)
    {
        Node<Edge>* tmp;
        bool flag1=true;
        tmp=adjList[v1]->head;
        while (tmp->next!=NULL){
            tmp=tmp->next;
            if (tmp->element.vertex==v2) {
                flag1=false;
                if (weight<tmp->element.weight) tmp->element.weight=weight;
                break;
            }
        }
        if (flag1) {
            adjList[v1]->append(Edge(weight,v2));
        }
    }
    int first(int v)
    {
        if (adjList[v]->head->next==NULL) return numVertex;
        return adjList[v]->head->next->element.vertex;
    }
    int next(int v,int w)
    {
        Node<Edge>* tmp;
        tmp=adjList[v]->head->next;
        while (tmp->next!=NULL){
            if(tmp->element.vertex!=w)  tmp=tmp->next;
                else return tmp->next->element.vertex;
        }
        return numVertex;
    }
    int BFS(int start,int len)
    {
             //   cout<<"Ì½²é"<<start<<"changdu"<<len<<endl;
        if (len<=1) return 1;
        int num=0;
        int v=start;
        mark[v]=VISITED;
        for (int w=first(v);w<numVertex;w=next(v,w)){
            if (mark[w]==UNVISITED) num+=1*BFS(w,len-1);
        }
     //   cout<<"»ØËÝ"<<v<<"num"<<num<<endl;
        mark[v]=UNVISITED;
        return num;
    }
};
int main()
{
    int n,m,start,M,a,b;
    cin>>n>>m>>start>>M;
    Graphl* G;
    G=new Graphl(n);
    for (int i=0;i<m;++i){
        cin>>a>>b;
        G->setEdge(a-1,b-1,1);
    }
    cout<<G->BFS(start-1,M+1);
    return 0;
}

