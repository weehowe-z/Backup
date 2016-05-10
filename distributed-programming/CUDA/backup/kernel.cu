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
char txt[40000001];
char pat[4001];



__device__ void computeLPSArray(const char *pat, int M, int *lps)
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
           len = lps[len-1];

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


__device__ void KMPSearch(int*c, int* lps, const char *pat, const char *txt, int sizepat, int sizetxt, int bid)
{
    int M = sizepat;
    int N = sizetxt;
    int j  = 0;  // index for pat[]

    // Preprocess the pattern (calculate lps[] array)
	// moved to the kernel function
    
	//printf("lps finished\n");
	int x=0;
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
          cout<<("Found pattern at index %d \n", i-j + bid*NB);
		  c[bid* NB + x] = i-j;
		  x++;
		  j = lps[j-1];
      }
      // mismatch after j matches
      else if (i < N && pat[j] != txt[i])
      {
        // Do not match lps[0..lps[j-1]] characters,
        // they will match anyway
        if (j != 0)
         j = lps[j-1];
        else
         i = i+1;
      }
    }
    free(lps); // to avoid memory leak
	//printf("finished\n");
}


void addWithCuda(int *c, const char *a, const char *b, unsigned int sizec, int sizea, int sizeb);

// __global__ void kmpKernel(int *c, int *lps, const char *a, const char *b, int sizea, int sizeb)
// {
// 	//int tid = threadIdx.x;
// 	int bid = blockIdx.x;
// 	//int idx = bid * blockDim.x + tid;
// 	if ( bid*NB <sizea)
// 	{
// 		computeLPSArray(b, sizeb, lps);
// 		KMPSearch(c, lps, b,a+bid*NB, sizeb, NB + sizeb - 1, bid);

// 	}
// }


__global__ void kmpKernel(int *c, int *lps, const char *txt, const char *pat, int sizetxt, int sizepat)
{
  int tid = threadIdx.x;
  int bid = blockIdx.x;
  int idx = bid * blockDim.x + tid;
  //printf("Found pattern at index %d \n", bid);
  if (idx*NB <sizetxt-sizepat)
  {
    computeLPSArray(pat, sizepat, lps);
    KMPSearch(c, lps, pat, txt + idx*NB, sizepat, NB + sizepat - 1, idx);

  }
  if (idx*NB >sizetxt-sizepat && (idx + 1)*NB<sizetxt-sizepat)
  {
    computeLPSArray(pat, sizepat, lps);
    KMPSearch(c, lps, pat, txt + idx*NB, sizepat, sizetxt - idx*NB, idx);
  }
}

int main()
{
	// ifstream fin("input.txt");
	// ofstream fout("output.txt");
	// //char *txt = new char[4000] ;
	// //char *txt = "AABAACAADAABAAABAA";
	// //char *pat = new char[1000];

	// int *rs = new int[4001];
	// for (int i=0;i<1000;++i) rs[i] = -1;

	// fin.getline(txt,40000001,'\n');
 //    fin.getline(pat,4001,'\n');

	// //cout << txt <<"\n"<< pat <<"\n";
	// const int sizec = 4001;
	
	// int len_txt = strlen(txt);
	// int len_pat = strlen(pat);
	
	// cout<<"haha\n";
	// addWithCuda(rs, txt, pat, sizec, len_txt, len_pat);
	// cout<<"haha\n";
 
  ifstream fin("input.txt");
  ofstream fout("out.txt");
  char *txt = new char[40000000];
  //char *txt = "AABAACAADAABAAABAA";
  char *pat = new char[4000];
  int *rs = new int[40000000];
  for (int i = 0; i<40000000; ++i) rs[i] = -1;

  fin.getline(txt, 40000000, '\n');
  fin.getline(pat, 4000, '\n');

  //cout << txt << "\n" << pat << "\n";
  const int sizec = 40000000;

  int len_txt = strlen(txt);
  int len_pat = strlen(pat);


  addWithCuda(rs, txt, pat, sizec, len_txt, len_pat);


  return 0;
}

// Helper function for using CUDA to add vectors in parallel.
void addWithCuda(int *c, const char *a, const char *b, unsigned int sizec, int sizea, int sizeb)
{
    char *dev_a = 0;
    char *dev_b = 0;
    int *dev_c = 0;
	int *dev_lps = 0;
   

    // Allocate GPU buffers for three vectors (two input, one output)    .
    cudaMalloc((void**)&dev_c, sizec * sizeof(int));
 
	cudaMalloc((void**)&dev_lps, sizeb * sizeof(int));


    cudaMalloc((void**)&dev_a, sizea * sizeof(char));
   

    cudaMalloc((void**)&dev_b, sizeb * sizeof(char));

    // Copy input vectors from host memory to GPU buffers.
    cudaMemcpy(dev_a, a, sizea * sizeof(char), cudaMemcpyHostToDevice);
    cudaMemcpy(dev_b, b, sizeb * sizeof(char), cudaMemcpyHostToDevice);

    // Launch a kernel on the GPU with one thread for each element.
    kmpKernel<<<NUM_BLOCKS, 1>>>(dev_c, dev_lps, dev_a, dev_b, sizea, sizeb);

    
    // cudaDeviceSynchronize waits for the kernel to finish, and returns
    // any errors encountered during the launch.
    cudaDeviceSynchronize();

    // Copy output vector from GPU buffer to host memory.
    cudaMemcpy(c, dev_c, sizec * sizeof(int), cudaMemcpyDeviceToHost);

    cudaFree(dev_c);
    cudaFree(dev_a);
    cudaFree(dev_b);
	cudaFree(dev_lps);

}
