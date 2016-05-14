#include <iostream>
#include <cassert>
using namespace std;
int main()
{
    int n,sum=0;
    int *p;
    cout<<"An array will be created dynamically.\n\n";
    cout<<"Input an array size n followed by n integers: ";
    cin>>n;
    cout<<endl;
    p=new int[n];
    assert(p!=NULL);
    for (int i=0;i<n;i++) {
        cout<<"Input the number: ";
        cin>>p[n];
        sum+=p[n];
    }
    delete []p;
    cout<<"Number of elements:"<<n<<endl;
    cout<<"Sum of the elements:"<<sum<<endl;
    return 0;
}
