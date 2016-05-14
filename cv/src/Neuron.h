#ifndef NEURON_H
#define NEURON_H

//this file is for the neuron class
#include <cmath>

class Neuron
{
public:
	int inputNum;
	double *weight;
	double activation;//activation is f( sum of input[i]*weight[i] )	// here I use sigmod function
	double error;

	Neuron(){}
	~Neuron()
	{
		delete []weight;
	}

	void init(int input_num)
	{
		inputNum = input_num+1;//there is a bias
		weight = new double[inputNum];
		activation = 0;
		error = 0;
	}

};
#endif 