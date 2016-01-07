#include <iostream>
#include <time.h>
#include <stdlib.h>
#define N 8
using namespace std;

void random_ints(int* a, int num)
{
	for (int i = 0; i < num; ++i){
		a[i] = rand() % 20;
		cout<<a[i]<<"\t";
	}
	cout<<endl<<endl;
}


//Calculate on the kernel
__global__ void add(int* a, int* b, int* c)
{
	c[blockIdx.x] = a[blockIdx.x] + b[blockIdx.x];
}

int main(int argc, char const *argv[])
{
	int blocks = 1, threads= 1;
	if(argc == 3){
		blocks = atoi(argv[1]); 
		threads = atoi(argv[2]);
	}
	cout<<"--------------------\n";
	cout<<"Blocks: " << blocks <<endl;
	cout<<"Threads: " << threads <<endl;
	cout<<"----------"<<endl;

	srand(time(NULL));

	// clock_t begin, end;
	clock_t gpu_begin, gpu_end;
	// double time_spent;
	double gpu_time_spent;


	//host copy
	int *a,*b,*c;

	//device copy 
	int *d_a,*d_b,*d_c;

	int size = N * sizeof(int);

	a = (int *)malloc(size);
	b = (int *)malloc(size);
	c = (int *)malloc(size);

	for (int i=0; i<N; ++i){
		c[i] = 0;
	}
	random_ints(a, N);
	random_ints(b, N);


	//allocate GPU space
	cudaMalloc((void **)&d_a, size);
	cudaMalloc((void **)&d_b, size);
	cudaMalloc((void **)&d_c, size);


	//copy input to device
	cudaMemcpy(d_a, a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, b, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_c, c, size, cudaMemcpyHostToDevice);
	gpu_begin = clock();

	add<<<blocks,threads>>>(d_a, d_b, d_c);

	gpu_end = clock();
	gpu_time_spent = (double)(gpu_end - gpu_begin)* 1000 / CLOCKS_PER_SEC;



	cudaMemcpy(c, d_c, size, cudaMemcpyDeviceToHost);

	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);

	for (int i=0; i<N; ++i){
		cout<< c[i]<<"\t";
	}
	cout<<endl<<endl<<endl;

	//kernel
	// cout<<"c is "<<c<<endl;
	cout<<"time_spent "<<gpu_time_spent<<"ms"<<endl;
	cout<<"--------------------\n\n";

	free(a);
	free(b);
	free(c);

	return 0;
}