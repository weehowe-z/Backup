#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

//Calculate on the kernel
__global__ void add(int* a, int* b, int* c)
{
	int i = threadIdx.x;
	*c = *a + *b;
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


	// clock_t begin, end;
	clock_t gpu_begin, gpu_end;
	// double time_spent;
	double gpu_time_spent;


	//host copy
	int a,b,c;
	a = 10;
	b = 20;
	c = 0;

	//device copy 
	int *d_a,*d_b,*d_c;

	int size = sizeof(int);

	gpu_begin = clock();

	//allocate GPU space
	cudaMalloc((void **)&d_a, size);
	cudaMalloc((void **)&d_b, size);
	cudaMalloc((void **)&d_c, size);

	//copy input to device
	cudaMemcpy(d_a, &a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, &b, size, cudaMemcpyHostToDevice);

	add<<<blocks,threads>>>(d_a, d_b, d_c);

	cudaMemcpy(&c, d_c, size, cudaMemcpyDeviceToHost);

	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);

	gpu_end = clock();
	gpu_time_spent = (double)(gpu_end - gpu_begin) / CLOCKS_PER_SEC;





	//kernel
	cout<<"c is "<<c<<endl;
	cout<<"time_spent "<<gpu_time_spent<<"s"<<endl;
	cout<<"--------------------\n\n";

	return 0;
}