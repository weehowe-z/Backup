#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;

void BFSearch(string target, string pattern);



int main(int argc, char const *argv[])
{
	ifstream in("input.txt");
	if (!in) {
		cerr << "error, cannot find input.txt\n";
		return -1;
	}

	string target,pattern;
	in >> target;
	in >> pattern;
	BFSearch(target,pattern);




	ofstream output("output2.txt");
	return 0;
}

void BFSearch(string target, string pattern)
{
	clock_t begin, end;
	double time_spent;

	cout<<"--------------------\n";
	cout<<"Alogrithm:\tBrute Force\n\n";
	begin = clock();

	unsigned int target_len = target.length();
	unsigned int pattern_len = pattern.length();
	unsigned int i = 0;
	while (i <= target_len - pattern_len){
		unsigned int j = 0;
		while (j < pattern_len){
			if ((target[i+j]) != pattern[j]) break;
			++j;
		}
		if (j == pattern_len) {
			cout<<"Match @ position "<< i << endl;
		}
		++i;
	}

	end = clock();
	time_spent = (double)(end - begin)* 1000 / CLOCKS_PER_SEC;
	cout<<"\ntime spent:\t"<<time_spent<<"ms"<<endl;
	cout<<"--------------------\n";
}

void preKMP(string pattern, int next[])
{
	unsigned int pattern_len = pattern.length();
	unsigned int k; //  longest suffix
    next[0] = 0;
    for (int i = 1; i < pattern_len; ++i)
    {
        k = next[i - 1];
        while (k >= 0)
        {
            if (pattern[k] == pattern[i])
                break;
            else
                k = next[k];
        }
        next[i] = k + 1;
    }
}


void KMPSearch(string target, string pattern){

}