#include <iostream>
#include <fstream>
// #include "time.h"
#define NUM_OF_THREADS 1024;

using namespace std;

void preKMP(char* pattern, int f[])
{
    int m = strlen(pattern), k;
    f[0] = -1;
    for (int i = 1; i < m; i++)
    {
        k = f[i - 1];
        while (k >= 0)
        {
            if (pattern[k] == pattern[i - 1])
                break;
            else
                k = f[k];
        }
        f[i] = k + 1;
    }
}
 
__global__ void KMP(char* pattern, char* target,int f[],int c[],int n, int m)
{
    int index = blockIdx.x*blockDim.x + threadIdx.x;
    int i = n * index;
    int j = n * (index + 2)-1;

    if(i>m)
        return;
    if(j>m)
        j=m;

    int k = 0;        
    while (i < j)
    {
        if (k == -1)
        {
            i++;
            k = 0;
        }
        else if (target[i] == pattern[k])
        {
            i++;
            k++;
            if (k == n)
            {
                c[i - n] = i-n;
                i = i - k + 1;
            }
        }
        else
            k = f[k];
    }
    return;
}
 
int main(int argc, char* argv[])
{
    ifstream fin;
    ofstream fout;

    if (argc != 3){
        cout<<"Plz specify input file and output file!\n";
        return -1;
    }

    fin.open(argv[1]);

    if (!fin){
        cout<<"Input file dose not exist!\n";
        return -1;       
    } 

    fout.open(argv[2]);


    cout<<"\n--------------------\n";
    cout<<"Input:\t"<<argv[1]<<endl;
    cout<<"Algorithm:\tKMP\n";


    const int L = 40000000;
    const int S = 40000000;
    int M = NUM_OF_THREADS;

    int cSize = 4;
    char *tar,*pat;
    tar = (char*)malloc(L*cSize);
    pat = (char*)malloc(S*cSize);
    
    //device copy
    char *d_tar, *d_pat;

    fin>>tar>>pat;

    int m = strlen(tar);
    int n = strlen(pat);

    cout<<"Target length:\t"<<m<<endl;
    cout<<"Pattern length:\t"<<n<<endl;
    cout<<"----\n";
    int *f;//next table
    int *c;//place table

    f = new int[m];
    c = new int[m];

    int *d_f;
    int *d_c;
    for(int i = 0;i<m; i++)
    {
        c[i] = -1;
    }     
    
    preKMP(pat, f);

    cout<<"Copy data to GPU\n";

    clock_t copy_start,copy_end,other_start,other_end;
    double copy_time_spent,total_time_spent;


    copy_start = clock();

    cudaMalloc((void **)&d_tar, m*cSize);
    cudaMalloc((void **)&d_pat, n*cSize);
    cudaMalloc((void **)&d_f, m*cSize);
    cudaMalloc((void **)&d_c, m*cSize);

    cudaMemcpy(d_tar, tar, m*cSize, cudaMemcpyHostToDevice);
    cudaMemcpy(d_pat, pat, n*cSize, cudaMemcpyHostToDevice);
    cudaMemcpy(d_f, f, m*cSize, cudaMemcpyHostToDevice);
    cudaMemcpy(d_c, c, m*cSize, cudaMemcpyHostToDevice);

    copy_end = clock();
    copy_time_spent = (double)(copy_end - copy_start)* 1000 / CLOCKS_PER_SEC;
    cout<<"Time spent:\t"<<copy_time_spent<<"ms"<<endl;
    cout<<"----\n";
    other_start = clock();

    // if(n>10000000)
    //     M = 128;

    float time_elapsed=0;
    cudaEvent_t start,stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);

    cudaEventRecord(start,0);
    KMP<<<(m/n+M)/M,M>>>(d_pat, d_tar ,d_f, d_c, n, m);
    cudaEventRecord(stop,0); 
 
    cudaEventSynchronize(start);    //Waits for an event to complete.
    cudaEventSynchronize(stop);    //Waits for an event to complete.Record之前的任务
    cudaEventElapsedTime(&time_elapsed,start,stop);    //计算时间差

    cout<<"String Matching\n";
    printf("Time spent:\t%.2fms\n", time_elapsed);  
    cout<<"----\n";

    cudaMemcpy(c, d_c, m*cSize, cudaMemcpyDeviceToHost);

    for(int i = 0;i<m; i++)
    { 
        if(c[i]!=-1)
        {
            fout<<c[i]<<'\n';
        }
    }

    cudaFree(d_tar); 
    cudaFree(d_pat);
    cudaFree(d_f);
    cudaFree(d_c);
    
    delete []f;
    delete []c;



    other_end = clock();
    total_time_spent = (double)(copy_end - copy_start + other_end - other_start)* 1000 / CLOCKS_PER_SEC;
    cout<<"Total time:\t"<<total_time_spent<<"ms"<<endl;
    cout<<"--------------------\n\n";
    



    return 0;
}