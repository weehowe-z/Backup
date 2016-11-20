#ifndef GRAPH_BY_ADJACENCY_LIST_H_INCLUDED
#define GRAPH_BY_ADJACENCY_LIST_H_INCLUDED
#include <iostream>
#define UNVISTED 0
#define VISTED 1
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
        matrix=new int* [numVertex];
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


#endif // GRAPH_BY_ADJACENCY_LIST_H_INCLUDED
