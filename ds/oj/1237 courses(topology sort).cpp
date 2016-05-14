#include <iostream>
#define UNVISTED 0
#define VISTED 1

using namespace std;
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

class Graphm
{
private:
    int numVertex;
    int numEdge;
    int **matrix;
    int *mark;   //point to mark array
public:
    Graphm(int numVertex)
    {
        init(numVertex);
    }
    ~Graphm()
    {
        delete []mark;
        for (int i=0;i<numVertex;++i) delete []matrix[i];
        delete []matrix;
    }

    void init(int n)
    {
        int i;
        numVertex=n;
        numEdge=0;
        mark=new int[numVertex];
        for (int i=0;i<numVertex;++i) mark[i]=UNVISTED;
        matrix= new int* [numVertex];
        for (int i=0;i<numVertex;++i) matrix[i]=new int[numVertex];
       for (int i=0;i<numVertex;++i){
        for (int j=0;j<numVertex;++j) matrix[i][j]=0;
       }
    }
    int getNumVertex() {return numVertex;}
    int getNumEdge() {return numEdge;}
    // return v's first neighbor
    int first(int v)
    {
        for (int i=0;i<numVertex;++i){
            if (matrix[v][i]!=0) return i;
        }
        return numVertex;//return n if none
    }
    int next(int v,int w)
    {
        for (int i=w+1;i<numVertex;++i){
            if (matrix[v][i]!=0) return i;
        }
        return numVertex;//return n if none
    }
    //set Edge
    void setEdge(int v1,int v2,int weight){
        if (weight<=0) {std::cout<<"Invalid weight\n";return;}
        if (matrix[v1][v2]==0) ++numEdge;
        matrix[v1][v2]=weight;
    }

    void deleteEdge(int v1,int v2)
    {
        if (matrix[v1][v2]!=0) --numEdge;
        matrix[v1][v2]=0;
    }
    bool isEdge(int v1,int v2)
    {
        if (matrix[v1][v2]!=0) return true;
            else return false;
    }
    int getWeight(int v1,int v2)
    {
        return matrix[v1][v2];
    }
    int getMark(int v)
    {
        return mark[v];
    }
    void setMark(int v,int val)
    {
        mark[v]=val;
    }
};

int topsort(Graphm* G,LQueue<int>* Q);

int main()
{
    int m,n,a,b;
    cin>>n>>m;
    Graphm* graph;
    LQueue<int>* queue;
    queue=new LQueue<int>;
    graph=new Graphm(n);
    for (int i=0;i<m;++i) {
        cin>>a>>b;
        graph->setEdge(b-1,a-1,1);
    }
    cout<<topsort(graph,queue)<<endl;
    delete graph;
    delete queue;
    return 0;
}

int topsort(Graphm* G,LQueue<int>* Q)
{
     int number=0;
    LQueue<int> temp;
    int count[G->getNumVertex()];
    for (int v=0;v<G->getNumVertex();++v) count[v]=0;
    for (int v=0;v<G->getNumVertex();++v){
        for (int w=G->first(v);w<G->getNumVertex();w=G->next(v,w)) ++count[w];
    }
    for (int v=0;v<G->getNumVertex();++v) {
        if (count[v]==0) Q->enqueue(v);
    }
    while (true){
        while (Q->length()!=0){
            temp.enqueue(Q->dequeue());
        }
        ++number;
        while (temp.length()!=0){
            int v=temp.dequeue();
            for (int w=G->first(v);w<G->getNumVertex();w=G->next(v,w)){
                    --count[w];
                    if (count[w]==0) Q->enqueue(w);
            }
        }
    if (Q->length()==0) break;
    }
    return number;
}
