#! /usr/bin/python
import random
import numpy as np

class Neuron(object):
	def __init__(self, inputNum):
		super(Neuron, self).__init__()
		self.inputNum = inputNum + 1
		self.weights = []
		self.activation = 0
		self.error = 0

	def initNeuron(self):
		for i in xrange(0, self.inputNum):
			weight = random.uniform(-0.5, 0.5)
			self.weights.append(weight)
	
	def activate(self, inputSum):
		self.activation = self.sigmod(inputSum)

	def sigmod(x, derivation = False):
		if derivation == True:
			return x(1-x)
		else:
			return 1/(1+np.exp(-x))

		
class NeuronLayer(object):
	def __init__(self, neuronNum, inputNumPerNeuron):
		super(NeuronLayer, self).__init__()
		self.neuronNum = neuronNum
		self.inputNumPerNeuron = inputNumPerNeuron
		self.neurons = []
		for i in xrange(0, self.neuronNum):
			neuron = Neuron(inputNumPerNeuron)
			self.neurons.append(neuron)

	def initLayer(self):
		for i in xrange(0, self.neuronNum):
			self.neurons[i].initNeuron()


class BPNeuronNetwork(object):
	def __init__(self, inputNum = 10, hiddenNum = 10, outputNum = 10, learnRate = 0.05, maxEpoch = 5000, minError = 0.05, initFatcor = 0.5):
		super(BPNeuronNetwork, self).__init__()
		self.inputNum = inputNum
		self.hiddenNum = hiddenNum
		self.outputNum = outputNum
		self.learnRate = learnRate
		self.maxEpoch = maxEpoch
		self.minError = minError
		self.bias = 1

		self.hiddenLayer = NeuronLayer(self.hiddenNum, self.inputNum)
		self.outputLayer = NeuronLayer(self.outputNum, self.hiddenNum)
		self.epoch = 0

		self.initNetwork()

	def __repr__(self):
		info = ""
		info += "inputNum " + str(self.inputNum) + '\n'
		info += "hiddenNum " + str(self.hiddenNum) + '\n'
		info += "outputNum " + str(self.outputNum) + '\n'
		info += "learnRate " + str(self.learnRate) + '\n'
		info += "maxEpoch " + str(self.maxEpoch) + '\n'
		info += "minError " + str(self.minError) + '\n'
		return info

	def initNetwork(self):
		self.hiddenLayer.initLayer()
		self.outputLayer.initLayer()

	def cal(self, input):
		hiddenLayerInputNum = hiddenLayer.inputNumPerNeuron
		outputLayerInputNum = hiddenLayer.inputNumPerNeuron

		#handle hidden layer
		for i in xrange(0,self.hiddenNum):
			inputSum = 0
			for j in xrange(0,hiddenLayerInputNum):
				inputSum += self.hiddenLayer.neurons[i].weights[j]*input[j];
			inputSum += self.hiddenLayer.neurons[i].weights[hiddenLayerInputNum]*self.bias
			self.hiddenLayer.neurons[i].activate()	
		#handle output layer
		output = []
		for i in xrange(0,self.outputNum):
			inputSum = 0
			for j in xrange(0,outputLayerInputNum):
				inputSum += self.outputLayer.neurons[i].weights[j]*self.hiddenLayer.neurons[j].activation;
			inputSum += self.outputLayer.neurons[i].weights[outputLayerInputNum]*self.bias
			self.outputLayer.neurons[i].activate()			
			output.append(self.outputLayer.neurons[i].activation)

		return output

	def trainSingleEpoch(self, input):
		errorSum = 0


	def sigmod(slef, x, derivation = False):
		if derivation == True:
			return x(1-x)
		else:
			return 1/(1+np.exp(-x))


if __name__ == '__main__':
	BPNN = BPNeuronNetwork()
	print BPNN
