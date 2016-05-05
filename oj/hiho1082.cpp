#include <iostream>
using namespace std;

bool isUpper(char c)
{
    bool b=(c>= 'A' && c <= 'Z')?true:false;
    return b;
}

bool isTarget(string str)
{
    string target = "marshtomp";
    for (int i = 0; i < (int)str.length(); ++i ){
        if (isUpper(str[i])) {
            str[i] = str[i] - 'A' + 'a';
        }
        if (str[i] != target[i]) return false;
    }
    return true;
}

int main()
{
    string str;
    while (getline(cin,str)){
        for (int i = 0; i < (int)str.length() - 8; ++i){
//            cout << " current i "<<i<<endl;
            if (isTarget(str.substr(i,9))){
                str.replace(i, 9, "fjxmlhx");
                i += 6;
            }
        }
        cout<<str<<endl;
    }
}

