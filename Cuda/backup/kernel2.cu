#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <cstring>
using namespace std;


#define NUM_THREADS 1000
#define NUM_BLOCKS 10000
#define NB 4


// void preKMP2(string pattern, unsigned int next[]);
// void KMPSearch2(string target, string pattern);


__device__ void preKMP(const char *pat, int M, int *lps)
{
	int len = 0;  // length of the previous longest prefix suffix
	int i;

	lps[0] = 0; // lps[0] is always 0
	i = 1;

	// the loop calculates lps[i] for i = 1 to M-1
	while (i < M)
	{
		if (pat[i] == pat[len])
		{
			len++;
			lps[i] = len;
			i++;
		}
		else // (pat[i] != pat[len])
		{
			if (len != 0)
			{
				// This is tricky. Consider the example
				// AAACAAAA and i = 7.
				len = lps[len - 1];

				// Also, note that we do not increment i here
			}
			else // if (len == 0)
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}
__device__ void KMPSearch(int*c, int* lps, const char *pat, const char *txt, int size_pattern, int size_target, int bid)
{
	int M = size_pattern;
	int N = size_target;
	int j = 0;  // index for pat[]

	// Preprocess the pattern (calculate lps[] array)
	// moved to the kernel function

	int i = 0;  // index for txt[]
	while (i < N)
	{
		if (pat[j] == txt[i])
		{
			j++;
			i++;
		}

		if (j == M)
		{
			printf("Found pattern at index %d \n", i - j + bid*NB);
			c[bid* NB +i - j] =1 ;
			
			j = lps[j - 1];
		}
		// mismatch after j matches
		else if (i < N && pat[j] != txt[i])
		{
			// Do not match lps[0..lps[j-1]] characters,
			// they will match anyway
			if (j != 0)
				j = lps[j - 1];
			else
				i = i + 1;
		}
	}
	free(lps);
}


void preCuda(int *c, const char *a, const char *b, unsigned int sizec, int sizea, int sizeb);

__global__ void kmpKernel(int *c, int *lps, const char *txt, const char *pat, int size_target, int size_pattern)
{
	int tid = threadIdx.x;
	int bid = blockIdx.x;
	int idx = bid * blockDim.x + tid;
	//printf("Found pattern at index %d \n", bid);
	if (idx*NB <size_target-size_pattern)
	{
		preKMP(pat, size_pattern, lps);
		KMPSearch(c, lps, pat, txt + idx*NB, size_pattern, NB + size_pattern - 1, idx);

	}
	if (idx*NB > size_target-size_pattern && (idx + 1) * NB < size_target-size_pattern)
	{
		preKMP(pat, size_pattern, lps);
		KMPSearch(c, lps, pat, txt + idx*NB, size_pattern, size_target - idx*NB, idx);
	}
}

int main()
{
	ifstream fin("input2.txt");

	// ifstream fin("input2.txt");
	ofstream fout("out.txt");
	// fout = fopen("out.txt","w");
	char *target = new char[40000000];
	char *pattern = new char[4000];
	int *rs = new int[40000000];
	for (int i = 0; i<40000000; ++i) rs[i] = -1;

	fin.getline(target, 40000000, '\n');
	fin.getline(pattern, 4000, '\n');

	//cout << target << "\n" << pattern << "\n";
	const int sizec = 40000000;

	int size_target = strlen(target);
	int size_pattern = strlen(pattern);

	preCuda(rs, target, pattern, sizec, size_target, size_pattern);

	for (int i = 0; i<40000000; ++i)
	{
		if (rs[i]==1	)
		fout << i <<  "\n";
	}

	delete []target;
	delete []pattern;

	return 0;
}

// Helper function for using CUDA to add vectors in parallel.
void preCuda(int *c, const char *a, const char *b, unsigned int sizec, int sizea, int sizeb)
{
	char *dev_a = 0;
	char *dev_b = 0;
	int *dev_c = 0;
	int *dev_lps = 0;

	// Choose which GPU to run on, change this on a multi-GPU system.
	// string target(a),pattern(b);
	// KMPSearch2(target,pattern);
	// return;
	// Allocate GPU buffers for three vectors (two input, one output)    .
	cudaMalloc((void**)&dev_c, sizec * sizeof(int));
	cudaMalloc((void**)&dev_lps, sizeb * sizeof(int));
	cudaMalloc((void**)&dev_a, sizea * sizeof(char));
	cudaMalloc((void**)&dev_b, sizeb * sizeof(char));

	// Copy input vectors from host memory to GPU buffers.
	cudaMemcpy(dev_a, a, sizea * sizeof(char), cudaMemcpyHostToDevice);


	cudaMemcpy(dev_b, b, sizeb * sizeof(char), cudaMemcpyHostToDevice);


	// Launch a kernel on the GPU with one thread for each element.
	kmpKernel << <NUM_BLOCKS, NUM_THREADS >> >(dev_c, dev_lps, dev_a, dev_b, sizea, sizeb);
	cudaDeviceSynchronize();

	cudaMemcpy(c, dev_c, sizec * sizeof(int), cudaMemcpyDeviceToHost);


	cudaFree(dev_c);
	cudaFree(dev_a);
	cudaFree(dev_b);
	cudaFree(dev_lps);

}


void preKMP2(string pattern,unsigned int next[])
{
	unsigned int pattern_len = pattern.length();
	unsigned int k; //  longest suffix
    next[0] = 0;
    for (int i = 1; i < pattern_len; ++i)
    {
		while(k > 0 && pattern[i] != pattern[k]) k = next[k-1];
		if (pattern[i] == pattern[k]) ++k;
		next[i] = k;	
    }
}


void KMPSearch2(string target, string pattern){
	clock_t begin, end;
	double time_spent;

	cout<<"--------------------\n";
	cout<<"Alogrithm:\tKMP\n\n";
	begin = clock();

	unsigned int target_len = target.length();
	unsigned int pattern_len = pattern.length();
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int *next = new unsigned int[pattern_len];

	preKMP2(pattern,next);

	while (i <= target_len - pattern_len){
		// cout<<"OUT target["<<i<<"]\n";
		// cout<<"OUT pattern["<<j<<"]\n";
		while (j < pattern_len){
			// cout<<"inner "<<j<<endl;
			if ((target[i+j]) != pattern[j]) break;
			++j;
		}
		// cout<<"current j "<<j<<endl;
		if (j == 0){
			++i;
		}
		else if  (j == pattern_len) {
			cout<<"Match @ position "<< i << endl;
			j = 0;
			++i;
		}
		else {
			i += j - next[j-1];
			j = next[j-1]; 
			// cout<<"afedfdfd "<<j<<endl;
		}
	}


	delete []next;

	end = clock();
	time_spent = (double)(end - begin)* 1000 / CLOCKS_PER_SEC;
	cout<<"\ntime spent:\t"<<time_spent<<"ms"<<endl;
	cout<<"--------------------\n";

}