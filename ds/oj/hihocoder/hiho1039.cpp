#include <iostream>
#include <cstring>
#include <string>
using namespace std;
int simplify(char word[]);
int maxSimplify(string s);
int main()
{
    int T;
    string s;
    cin>>T;
    for (int i=0;i<T;++i){
        cin>>s;
        cout<<maxSimplify(s)<<endl;
    }
    return 0;
}

int simplify(char word[])
{
    int num=0;
    bool exitFlag=true;
    int i=0;
    while (word[i]!='\0'){
        int j=i;
        while (word[j+1]==word[i]) ++j;
        if (i!=j){
            exitFlag=false;
            strcpy(word+i,word+j+1);
            num+=j-i+1;
            continue;
        }
        ++i;
    }

    if (exitFlag) return num;
        else return num+simplify(word);
}
int maxSimplify(string s)
{

    char word[100];
    char simWord[101];
    for (unsigned int i=0;i<s.length();++i) word[i]=s[i];
    word[s.length()]='\0';
    int maxNum=2;
    for (int i=1;i<strlen(word);++i){
        for (char ch='A';ch<='C';++ch){
            for ( int j=0;j<i;++j) simWord[j]=word[j];
            strcpy(simWord+i+1,word+i);
            simWord[i]=ch;
            int simNum=simplify(simWord);
            if (simNum>maxNum) maxNum=simNum;
        }
    }
    return maxNum;
}
