#include <iostream>
#include <string>
using namespace std;


void preKMP(string pattern, int next[]);
void KMPSearch(string target, string pattern);

int main(int argc, char const *argv[])
{

    int n;
    cin >> n;
    string target,pattern;
    for (int i = 0 ;i<n ;++i){
        cin>>pattern;
        cin>>target;
        KMPSearch(target,pattern);
    }
	return 0;
}

void preKMP(string pattern,int next[])
{
	int pattern_len = pattern.length();
	int k; //  longest suffix
    next[0] = 0;
    for (int i = 1; i < pattern_len; ++i)
    {
		while(k > 0 && pattern[i] != pattern[k]) k = next[k-1];
		if (pattern[i] == pattern[k]) ++k;
		next[i] = k;	
    }
}


void KMPSearch(string target, string pattern){

    int num = 0;
	int target_len = target.length();
	int pattern_len = pattern.length();
	int i = 0;
	int j = 0;
	int *next = new int[pattern_len];

	preKMP(pattern,next);

	while (i <= target_len - pattern_len){
		while (j < pattern_len){
			if ((target[i+j]) != pattern[j]) break;
			++j;
		}
		if (j == 0){
			++i;
		}
		else if  (j == pattern_len) {
    		num++;
			j = 0;
			++i;
		}
		else {
			i += j - next[j-1];
			j = next[j-1]; 
		}
	}
	cout<< num<<endl;
	delete []next;
}