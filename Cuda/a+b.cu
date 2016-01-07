#include <iostream>
#include <time.h>
using namespace std;

//Calculate on the kernel
__global__ void add(int* a, int* b, int* c)
{
	*c = *a + *b;
}


int main(int argc, char const *argv[])
{
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

	cout<<"Begin to allocate GPU space\n";
	gpu_begin = clock();

	//allocate GPU space
	cudaMalloc((void **)&d_a, size);
	cudaMalloc((void **)&d_b, size);
	cudaMalloc((void **)&d_c, size);

	//copy input to device
	cudaMemcpy(d_a, &a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, &b, size, cudaMemcpyHostToDevice);

	add<<<1,1>>>(d_a, d_b, d_c);

	cudaMemcpy(&c, d_c, size, cudaMemcpyDeviceToHost);

	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);

	gpu_end = clock();
	gpu_time_spent = (double)(gpu_end - gpu_begin) / CLOCKS_PER_SEC;





	//kernel
	cout<<"c is "<<c<<endl;
	cout<<"time_spent "<<gpu_time_spent<<"s"<<endl;

	return 0;
}