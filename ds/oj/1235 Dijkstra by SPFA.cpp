#include <iostream>
#define INFINITY 9999999
#define UNDEFINED -1
#define UNVISTED 0;
#define VISTED 1;
using namespace std;
class AStack
{
private:
    int maxSize;
    int top;
    int* listArray;
    void doubleSpace()
    {
        int*  temp=listArray;
        maxSize*=2;
        listArray =new int[maxSize];
        for (int i=0;i<top;++i) listArray[i]=temp[i];
        delete temp;
    }
public:
    AStack(int size=10)
    {
        maxSize=size;
        top=0;
        listArray=new int[size];
    }
    ~AStack()
    {
        delete []listArray;
    }

    void clear()
    {
        top=0;
    }
    void push(const int &it)
    {
        if (top==maxSize) doubleSpace();
        listArray[top++]=it;
    }
    int pop()
    {
        return listArray[--top];
    }
    int length() const { return top;}
};
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
    Edge(int w=INFINITY,int v=UNDEFINED)
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
        for (int i=0;i<numVertex;++i) mark[i]=UNVISTED;
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
        return INFINITY;
    }
    void setEdge(int v1,int v2,int weight)
    {
        if (v1==v2) return;
        Node<Edge>* tmp;
        bool flag1=true;
        bool flag2= true;
        tmp=adjList[v1]->head;
        while (tmp->next!=NULL){
            tmp=tmp->next;
            if (tmp->element.vertex==v2) {
                flag1=false;
                if (weight<tmp->element.weight) {flag2=false;tmp->element.weight=weight;}
                break;
            }
        }
        if (flag1) {
            adjList[v1]->append(Edge(weight,v2));
            adjList[v2]->append(Edge(weight,v1));
        }
            else if (!flag2){
                 tmp=adjList[v2]->head;
                 while (tmp->next!=NULL){
                    tmp=tmp->next;
                    if (tmp->element.vertex==v1) tmp->element.weight=weight;
                }
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

    bool Shortest_Path_Faster_Algorithm(int source,int destination)//if by Adjacency Matrix is in O(N^3)
    {
        // Step 1: initialize graph
        AStack stk;
        LQueue<int> Q;
        int minDistanceMatrix[numVertex];
        int prevNode[numVertex];
        for (int i=0;i<numVertex;++i) prevNode[i]=UNDEFINED;
        for (int i=0;i<numVertex;++i) minDistanceMatrix[i]=INFINITY;
        minDistanceMatrix[source]=0;

        Q.enqueue(source);
        while (Q.length>0){
                int v=Q.dequeue();
                for (int w=first(v);w<numVertex;w=next(v,w)){
                    if (getWeight(v,w)+minDistanceMatrix[v]<minDistanceMatrix[w]){
                        minDistanceMatrix[w]=minDistanceMatrix[v]+getWeight(v,w);
                                            prevNode[w]=v;
                        Q.enqueue(w);
                    }
                }
        }
        cout<<minDistanceMatrix[destination]<<endl;
                cout<<source+1<<" ";
        while (prevNode[destination]!=UNDEFINED){
            stk.push(destination+1);
            destination=prevNode[destination];
        }
        while (stk.length()>0) cout<<stk.pop()<<" ";
        cout<<endl;
    }
};
int main()
{
    int m,n,u,v,l;
    int s,t;
    Graphl* G;
    cin>>n>>m;
    cin>>s>>t;
    G=new Graphl(n);
    for (int i=0;i<m;++i){
        cin>>u>>v>>l;
        G->setEdge(u-1,v-1,l);
    }
    G->Shortest_Path_Faster_Algorithm(s-1,t-1);
    return 0;
}
