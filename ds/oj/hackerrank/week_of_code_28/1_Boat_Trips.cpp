#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n,c,m;
    vector<int> p;

    cin>>n>>c>>m;

    for (int i = 0 ; i < n; ++i){
        int x;
        cin>>x;
        p.push_back(x);
    }

    int maxNum = *max_element(p.begin(),p.end());

    if (maxNum > c*m) cout<<"No\n";
    else cout<<"Yes\n";

    return 0;
}
