#include <iostream>
#define INFINITE 9999999
#define EMPTY -1
#define UNVISTED 0
#define VISTED 1

using namespace std;

class Graphm//undirected
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
            for (int j=0;j<numVertex;++j) matrix[i][j]=INFINITE;
        }
        for (int i=0;i<numVertex;++i) matrix[i][i]=0;
    }
    int getNumVertex() {return numVertex;}
    int getNumEdge() {return numEdge;}
    // return v's first neighbor
    int first(int v)
    {
        for (int i=0;i<numVertex;++i){
            if (matrix[v][i]!=INFINITE&&v!=i) return i;
        }
        return numVertex;//return n if none
    }
    int next(int v,int w)
    {
        for (int i=w+1;i<numVertex;++i){
            if (matrix[v][i]!=INFINITE&&v!=i) return i;
        }
        return numVertex;//return n if none
    }
    //set Edge(0 is invalid for 0 represents for no edge)
    void setEdge(int v1,int v2,int weight){
        //if (weight<=0) {std::cout<<"Invalid weight\n";return;}
        if (matrix[v1][v2]==INFINITE) ++numEdge;
        if (weight<matrix[v1][v2]){
        matrix[v1][v2]=weight;
        matrix[v2][v1]=weight;//for the question's case
        }
    }

    void deleteEdge(int v1,int v2)
    {
        if (matrix[v1][v2]!=INFINITE) --numEdge;
        matrix[v1][v2]=INFINITE;
    }
    bool isEdge(int v1,int v2)
    {
        if (matrix[v1][v2]!=INFINITE&&v1!=v2) return true;
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

    void Floyd_Warshall_Algorithm()//obtain single source shortest path from all the vertex
    {
        int** minDistanceMatrix;
        minDistanceMatrix=new int*[numVertex];
        for (int i=0;i<numVertex;++i) minDistanceMatrix[i]=new int[numVertex];
        for (int i=0;i<numVertex;++i){
            for (int j=0;j<numVertex;++j) minDistanceMatrix[i][j]=matrix[i][j];
        }
        for (int k=0;k<numVertex;++k){
            for (int i=0;i<numVertex;++i){
                for (int j=0;j<numVertex;++j){
                    if (i==j||i==k||j==k) continue;
                    minDistanceMatrix[i][j]=min(minDistanceMatrix[i][j],minDistanceMatrix[i][k]+minDistanceMatrix[k][j]);
                }
            }
        }
        for (int i=0;i<numVertex;++i){
            for (int j=0;j<numVertex;++j) {
                    if (minDistanceMatrix[i][j]!=INFINITE) cout<<minDistanceMatrix[i][j]<<" ";//-1 represents for no path
                            else cout<<"- ";
            }
            cout<<endl;
        }
        for (int i=0;i<numVertex;++i) delete []minDistanceMatrix[i];
        delete []minDistanceMatrix;
    }

    bool Bellman_Ford_Algorithm(int source,int destination)//if by Adjacency Matrix is in O(N^3)
    {
        // Step 1: initialize graph
        int* minDistanceMatrix;
        int* predecessor;
        minDistanceMatrix=new int[numVertex];
        predecessor=new int[numVertex];
        for (int i=0;i<numVertex;++i){
            minDistanceMatrix[i]=INFINITE;
            predecessor[i]=EMPTY;
        }
        minDistanceMatrix[source]=0;
        // Step 2: relax edges repeatedly
        for (int i=0;i<numVertex-1;++i){
            for (int v=0;v<numVertex;++v){
                for (int w=first(v);w<numVertex;w=next(v,w)){
                    if (getWeight(v,w)+minDistanceMatrix[v]<minDistanceMatrix[w]){
                        minDistanceMatrix[w]=minDistanceMatrix[v]+getWeight(v,w);
                        predecessor[w]=v;
                    }
                }
            }
        }
        // Step 3: check for negative-weight cycles
       for (int i=0;i<numVertex-1;++i){
            for (int v=0;v<numVertex;++v){
                for (int w=first(v);w<numVertex;w=next(v,w)){
                    if (getWeight(v,w)+minDistanceMatrix[v]<minDistanceMatrix[w]){
                        cout<<"error: there is a cycle whose edges sum to a negative value";
                        return false;
                    }
                }
            }
        }
        /*cout<<destination+1<<" ";
        while (destination!=source){
            destination=predecessor[destination];
            cout<<destination+1<<" ";
        }
        cout<<endl;
        cout<<"BG"<<endl;
        */
        /*for (int i=0;i<numVertex;++i) cout<<minDistanceMatrix[i]<<" ";
        cout<<endl;
        for (int i=0;i<numVertex;++i) cout<<predecessor[i]+1<<" ";
        cout<<endl;
        */
        cout<<minDistanceMatrix[destination]<<endl;
        delete []predecessor;
        delete []minDistanceMatrix;
    }
};

int main()
{
    int m,n,u,v,l;
    int s,t;
    Graphm* G;
    cin>>n>>m;
    cin>>s>>t;
    G=new Graphm(n);
    for (int i=0;i<m;++i){
        cin>>u>>v>>l;
        G->setEdge(u-1,v-1,l);
    }
    G->Bellman_Ford_Algorithm(s-1,t-1);
    return 0;
}
