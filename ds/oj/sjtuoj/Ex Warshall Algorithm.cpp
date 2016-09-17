#include <iostream>
#include <fstream>
#define INFINITE 9999999
#define UNVISTED 0
#define VISTED 1

using namespace std;

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
    //set Edge(0 is invalid for 0 represents for no edge)
    void setEdge(int v1,int v2,int weight){
        //if (weight<=0) {std::cout<<"Invalid weight\n";return;}
        if (matrix[v1][v2]==INFINITE) numEdge+=2;
        if (weight<matrix[v1][v2]){
        matrix[v1][v2]=weight;
        //matrix[v2][v1]=weight;//for the question's case
        }
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
    void Warshall()
    {
        int** connectMatrix;
        connectMatrix=new int*[numVertex];
        for (int i=0;i<numVertex;++i) connectMatrix[i]=new int[numVertex];
        for (int i=0;i<numVertex;++i){
            for (int j=0;j<numVertex;++j){
                if (matrix[i][j]!=0&&matrix[i][j]!=INFINITE) connectMatrix[i][j]=1;
                    else connectMatrix[i][j]=0;
            }
        }
        for (int k=0;k<numVertex;++k){
            for (int i=0;i<numVertex;++i){
                for (int j=0;j<numVertex;++j){
                    //if (i==j||i==k||j==k) continue;
                    connectMatrix[i][j]=connectMatrix[i][j]||connectMatrix[i][k]&&connectMatrix[k][j];
                }
            }
        }
        for (int i=0;i<numVertex;++i){
            for (int j=0;j<numVertex;++j) {
                    cout<<connectMatrix[i][j]<<" ";//-1 represents for no path
            }
            cout<<endl;
        }
        for (int i=0;i<numVertex;++i) delete []connectMatrix[i];
        delete []connectMatrix;
    }
};

int main()
{
    int m,n,u,v,l;
    Graphm* G;
    cin>>n>>m;
    G=new Graphm(n);
    for (int i=0;i<m;++i){
        cin>>u>>v>>l;
        G->setEdge(u-1,v-1,l);
    }
    G->Warshall();
    return 0;
}
