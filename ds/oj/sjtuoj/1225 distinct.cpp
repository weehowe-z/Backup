#include <iostream>
using namespace std;

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

int main()
{
    long int N;
    long int num=1;
    long int prev;
    cin>>N;
    int *arr;
    arr=new int[N];
    for (long int i=0;i<N;++i) cin>>arr[i];
    quickSort(arr,0,N-1);
    prev=arr[0];
    for (long int i=1;i<N;++i) {
        if (arr[i]!=prev) {prev=arr[i];++num;}
    }
    delete []arr;
    cout<<num;
    return 0;
}
