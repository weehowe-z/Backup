#include <iostream>
using namespace std;
//quickSort Implement
void findPairs(int A[],int n, int key);
template <typename E>
inline int findPivot(E A[],int i, int j);
template <typename E>
void quickSort(E A[],int i,int j);
template <typename E>
inline int partition(E A[],int l,int r,E& pivot);

int main()
{
    int n;
    cin>>n;
    int * num;
    num=new int[n];
    for (int i=0;i<n;++i) cin>>num[i];
    quickSort(num,0,n-1);
     for (int i=0;i<n;++i) cout<<num[i]<<" ";
    return 0;
}


template <typename E>
inline int findPivot(E A[],int i, int j)
{
    return (i+j)/2;
}
template <typename E>
inline int partition(E A[],int l,int r,E& pivot)
{
    while (l<r){
        while(A[l]<pivot){++l;};//move l right
        while((l<r)&& (pivot<A[--r]));
        swap(A[l],A[r]);
    }
    return l;
}
template <typename E>
void quickSort(E A[],int i,int j)
{
    if(j<=i) return;//don't sort  the array with only one or no elements;
    int pivotIndex= findPivot(A,i,j);
    swap(A[pivotIndex],A[j]);//set pivot at the end
    //k will be the first position in the right array
    int k = partition<E>(A,i,j,A[j]);
    swap(A[k],A[j]);
    quickSort<E>(A,i,k-1);
    quickSort<E>(A,k+1,j);
}

