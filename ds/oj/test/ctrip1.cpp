#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int x;
    cin>>x;
    int n;
    cin>>n;
    vector<int> arr;
    for (int i=0 ; i<n ; ++i)
    {
        int tmp;
        cin>>tmp;
        arr.push_back(tmp);
    }

    if (binary_search(arr.begin(),arr.end(),x)) cout<<(lower_bound(arr.begin(),arr.end(),x)-arr.begin())<<endl;
    else {
        int t = -1 - (lower_bound(arr.begin(),arr.end(),x)-arr.begin());
        cout<<t<<endl;

    }
    return 0;
}
