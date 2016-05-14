#include <iostream>
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
    //set Edge(0 is invalid for 0 represents for no edge)
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
    void Floyd_Warshall_Algorithm()
    {
        int** minDistanceMatrix;
        minDistanceMatrix=new int*[numVertex];
        for (int i=0;i<numVertex;++i) minDistanceMatrix[i]=new int[numVertex];
        for (int i=0;i<numVertex;++i){
            for (int j=0;j<numVertex;++j) minDistanceMatrix[i][j]=matrix[i][j];//-1 represents for no path
        }
        for (int k=0;k<numVertex;++k){
            for (int i=0;i<numVertex;++i){
                for (int j=0;j<numVertex;++j){
                    if (i==j||i==k||j==k) continue;
                    minDistanceMatrix[i][j]=min(minDistanceMatrix[i][k],minDistanceMatrix[k][j]);
                }
            }
        }
        for (int i=0;i<numVertex;++i){
            for (int j=0;j<numVertex;++j) cout<<minDistanceMatrix[i][j]<<" ";//-1 represents for no path
            cout<<endl;
        }
    }
};
