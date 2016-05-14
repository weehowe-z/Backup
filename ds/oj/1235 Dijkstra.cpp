#include <iostream>
#define INFINITY 9999999
#define UNDEFINED -1
#define UNVISTED 0
#define VISTED 1
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

class Node
{
public:
    Edge element;
    Node* next;
    Node()
    {
        next=NULL;
    }
    Node(Edge e,Node* n)
    {
        element=e;
        next=n;
    }
};

class LList
{
public:
    Node* head;
    Node* tail;
    int length;
    LList()
    {
        length=0;
        head=tail=new Node;
    }
 ~ LList()
    {
        Node* tmp;
        while (head->next!=NULL){
            tmp=head;
            head=head->next;
            delete tmp;
        }
        delete head;
    }
    void append(const Edge it)
    {
        tail->next=new Node(it,NULL);
        tail=tail->next;
        ++length;
    }
};


class Graphl
{
private:
    int numVertex;
    int numEdge;
    int **matrix;
    int *mark;   //point to mark array
public:
    Graphl(int numVertex)
    {
        init(numVertex);
    }
    ~Graphl()
    {
        delete []mark;
        for (int i=0;i<numVertex;++i) delete []matrix[i];
        delete []matrix;
    }

    void init(int n)
    {
        numVertex=n;
        numEdge=0;
        mark=new int[numVertex];
        for (int i=0;i<numVertex;++i) mark[i]=UNVISTED;
        matrix= new int* [numVertex];
        for (int i=0;i<numVertex;++i) matrix[i]=new int[numVertex];
        for (int i=0;i<numVertex;++i){
            for (int j=0;j<numVertex;++j) matrix[i][j]=INFINITY;
        }
        for (int i=0;i<numVertex;++i) matrix[i][i]=0;
    }
    int getNumVertex() {return numVertex;}
    int getNumEdge() {return numEdge;}
    // return v's first neighbor
    int first(int v)
    {
        for (int i=0;i<numVertex;++i){
            if (matrix[v][i]!=INFINITY&&v!=i) return i;
        }
        return numVertex;//return n if none
    }
    int next(int v,int w)
    {
        for (int i=w+1;i<numVertex;++i){
            if (matrix[v][i]!=INFINITY&&v!=i) return i;
        }
        return numVertex;//return n if none
    }
    //set Edge(0 is invalid for 0 represents for no edge)
    void setEdge(int v1,int v2,int weight){
        //if (weight<=0) {std::cout<<"Invalid weight\n";return;}
        if (matrix[v1][v2]==INFINITY) ++numEdge;
        if (weight<matrix[v1][v2]){
        matrix[v1][v2]=weight;
        //matrix[v2][v1]=weight;//for the question's case
        }
    }

    void deleteEdge(int v1,int v2)
    {
        if (matrix[v1][v2]!=INFINITY) --numEdge;
        matrix[v1][v2]=INFINITY;
    }
    bool isEdge(int v1,int v2)
    {
        if (matrix[v1][v2]!=INFINITY&&v1!=v2) return true;
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
    int findMin(int distanceMatrix[])
    {
        int v;
        for (int i=0;i<numVertex;++i){
            if (mark[i]==UNVISTED) {v=i;break;}
        }
        for (int i=v+1;i<numVertex;++i){
            if (mark[i]==UNVISTED&& distanceMatrix[i]<distanceMatrix[v]) v=i;
        }
        return v;
    }

    void Dijkstra_Algorithm(int source,int destination)
    {
        AStack stk;
        int minDistanceMatrix[numVertex];
        int prevNode[numVertex];
        for (int i=0;i<numVertex;++i) minDistanceMatrix[i]=INFINITY;
        for (int i=0;i<numVertex;++i) prevNode[i]=UNDEFINED;
        minDistanceMatrix[source]=0;

        for (int i=0;i<numVertex;++i) mark[i]=UNVISTED;
        for (int i=0;i<numVertex;++i){
            int v=findMin(minDistanceMatrix);
            mark[v]=VISTED;
            for (int w=first(v);w<numVertex;w=next(v,w)){
                if (minDistanceMatrix[v]+getWeight(v,w)<minDistanceMatrix[w]) {
                    minDistanceMatrix[w]=minDistanceMatrix[v]+getWeight(v,w);
                    prevNode[w]=v;
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
    G->Dijkstra_Algorithm(s-1,t-1);
    return 0;
}
