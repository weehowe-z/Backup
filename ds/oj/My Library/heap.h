#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED
using namespace std;
//heap class   using complete binary tree in array
template <typename E>
class minHeap
{
private:
    E* Heap;
    int maxSize;//Maximum Size of the heap;
    int num;//number of the elements in the heap;

    void shiftdown(int pos)
    {
        while(!isLeaf(pos)){
            int minc=leftChild(pos);
            int rc=rightChild(pos);
            if((rc<num)&&(Heap[rc]<Heap[minc])) minc=rc;//change
            if (Heap[pos]<Heap[minc]) return;
            swap(Heap[pos],Heap[minc]);
            pos = minc;
        }
    }
public:
    minHeap(E* h ,int n,int max)//constructor
    {
        Heap=h;
        num=n;
        maxSize=max;
        buildHeap();
    }
    int size() const//return the current size
    {
        return num;
    }
    bool isLeaf(int pos) const//judge whether is a leaf
    {
        return (pos>=num/2)&&(pos<num);
    }
    int leftChild(int pos) const
    {
        return 2*pos+1;
    }
    int rightChild(int pos) const
    {
        return 2*pos+2;
    }
    int parent(int pos) const
    {
        return (pos-1)/2;
    }
    void buildHeap()
    {
        for (int i=num/2 -1;i>=0;i--) shiftdown(i);
    }

    void insert(const E& it)
    {
        if (num>=maxSize) return;
        int curr=num++;
        Heap[curr]=it;
        while ((curr!=0)&&(Heap[curr]<Heap[parent(curr)]))
        {
            swap (Heap[curr],Heap[parent(curr)]);
            curr=parent(curr);
        }
    }
    //remove first value
    E removeFirst()
    {
        swap(Heap[0],Heap[--num]);
        if (num!=0) shiftdown(0);
        return Heap[num];
    }
};


#endif // HEAP_H_INCLUDED
