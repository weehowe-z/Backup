#include <iostream>
using namespace std;
void merge(int a[],int left,int mid,int right);
void mergeSort(int a[],int left,int right);
int main()
{
    int n,*num;
    cin>>n;
    num=new int[n];
    for (int i=0;i<n;++i) cin>>num[i];
    mergeSort(num,0,n-1);
    for (int i=0;i<n;++i) cout<<num[i]<<" ";
    delete []num;
    return 0;
}
void merge(int a[],int left,int mid,int right)
{
    int *tmp=new int[right-left+1];
    int i=left,j=mid,k=0;
    while(i<mid&&j<=right){
        if (a[i]<a[j]) tmp[k++]=a[i++];
        else tmp[k++]=a[j++];
    }
    while(i<mid)  tmp[k++]=a[i++];
    while(j<=right) tmp[k++]=a[j++];
    for (i=0,k=left;k<=right;++k) a[k]=tmp[i++];
    delete []tmp;
}
void mergeSort(int a[],int left,int right)
{
    int  mid=(left+right)/2;
    if (left==right) return;
    mergeSort(a,left,mid);
    mergeSort(a,mid+1,right);
    merge(a,left,mid+1,right);
}
