#ifndef NEURON_LAYER_H
#define NEURON_LAYER_H

//this file is for the neuron layer class

#include "Neuron.h"

class NeuronLayer
{
public:
	int neuronNum;
	Neuron *neurons; //array of neurons

	NeuronLayer(int neuronNumber = 10 ,int inputPerNeuron = 10)
	{
		neuronNum = neuronNumber;
		neurons = new Neuron[neuronNum];
		//initialize the neurons
		for (int i = 0;i<neuronNum;++i) neurons[i].init(inputPerNeuron);
		
	}
	~NeuronLayer(void)
	{
		delete []neurons;
	}
};

#endif