#ifndef NEURON_NET_H
#define NEURON_NET_H
#include "Neuron.h"
#include "NeuronLayer.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

#define WEIGHT_FACTOR 0.5  //change the initialized random weight parameters, now is -0.5~0.5
#define BIAS 1   //arguments of bias

using namespace std;

double Sigmod(double x);

class NeuralNet
{
public:
	int inputLayerNeuronNum;
	int outputLayerNeuronNum;
	int hiddenLayerNeuronNum;
	int hiddenLayerNum;

	NeuronLayer *hiddenLayer,*outputLayer;

	int maxEpoch;// threshold: most trainning times
	double minError;// threshold: min total error

	int epoch;// have trainned for xx times
	double learningRate;
	double errorSum;
	double error;
	
	//vector<double> vecError;//be careful to use using namespace std;

	NeuralNet(int input,int output, int hidden,double learn_rate,int epoch_max,double error_min)
	{

		inputLayerNeuronNum = input;
		outputLayerNeuronNum = output;
		hiddenLayerNeuronNum = hidden;
		hiddenLayerNum=1;//can only handle 1 hidden layer so far, for more the method is just the same
		
		learningRate=learn_rate;
		maxEpoch=epoch_max;
		minError=error_min;


		hiddenLayer=new NeuronLayer(hiddenLayerNeuronNum,inputLayerNeuronNum);
		outputLayer=new NeuronLayer(outputLayerNeuronNum,hiddenLayerNeuronNum);


		//errorSum=INITIAL_ERROR_SUM;
		epoch=0;

		initializeNetWork();
		// print the initialized information
		cout<<fixed<<setprecision(2);
		cout<<"Network info:\n";
		cout<<"Input layer neuron number: "<<inputLayerNeuronNum<<endl;
		cout<<"Hidden layer neuron number: "<<hiddenLayerNeuronNum<<endl;
		cout<<"Output layer neuron number: "<<outputLayerNeuronNum<<endl;
		cout<<"Learning speed rate: "<<learningRate<<endl;
		cout<<"Max trainning epoch: "<<maxEpoch<<endl;
		cout<<fixed<<setprecision(4)<<"Min error sum: "<<minError<<endl;
		cout<<fixed<<setprecision(2);
	}
	~NeuralNet()
	{
		delete hiddenLayer;
		delete outputLayer;

	}
	void initializeNetWork()
	{
		srand((unsigned int)time(NULL));
		//initialize the hidden layer's weight
		for (int i=0;i<hiddenLayer->neuronNum;++i){
			for (int j=0;j<hiddenLayer->neurons[i].inputNum;++j){
				hiddenLayer->neurons[i].weight[j]=WEIGHT_FACTOR*(rand()/(RAND_MAX+1.0)-rand()/(RAND_MAX+1.0));
				//random value from -0.5 to 0.5 can be modifyed by weight factor
			}
		}
		//initialize the output layer's weight
		for (int i=0;i<outputLayer->neuronNum;++i){
			for (int j=0;j<outputLayer->neurons[i].inputNum;++j){
				outputLayer->neurons[i].weight[j]=WEIGHT_FACTOR*(rand()/(RAND_MAX+1.0)-rand()/(RAND_MAX+1.0));
			}
		}


	}
	void calculateOutput(vector<double> &input,vector<double> &output)
	{
		int i,j;
		//calculate the output of hidden layer
		for (i=0;i<hiddenLayer->neuronNum;++i){
			double inputSum=0;
			//handle n dimensions
			for (j=0;j<hiddenLayer->neurons[i].inputNum-1;++j){
				inputSum+=hiddenLayer->neurons[i].weight[j]*input[j];
			}
			//handle n+1 dimension (bias)
			inputSum+=hiddenLayer->neurons[i].weight[j]*BIAS;
			//calcuate the activation
			hiddenLayer->neurons[i].activation=Sigmod(inputSum);
		}
		//calculate the output of output layer;
		for (i=0;i<outputLayer->neuronNum;++i){
			double inputSum=0;
			for (j=0;j<outputLayer->neurons[i].inputNum-1;++j){
				inputSum+=outputLayer->neurons[i].weight[j]*hiddenLayer->neurons[j].activation;
			}
			inputSum+=outputLayer->neurons[i].weight[j]*BIAS;
			//calculate activation
			outputLayer->neurons[i].activation=Sigmod(inputSum);

			//save the output 
			output.push_back(outputLayer->neurons[i].activation);
		}
	}
	void trainSingleEpoch(vector<vector<double> > &setIn,vector<vector<double> > &setOut)
	{
		int i,j,k;
		double weightUpdate;
		double err;
		
		errorSum=0;
		for (i=0;i<(int)setIn.size();++i){
			vector<double> vecOutputs;
			//foward propagation
			calculateOutput(setIn[i],vecOutputs);
			//update the output layer weight
			for (j=0;j<outputLayer->neuronNum;++j){
				err=((double)setOut[i][j]-vecOutputs[j])*vecOutputs[j]*(1-vecOutputs[j]);
				outputLayer->neurons[j].error=err;
				errorSum+=((double)setOut[i][j]-vecOutputs[j])*((double)setOut[i][j]-vecOutputs[j]);
				for (k=0;k<hiddenLayer->neuronNum;++k){
					//calculate the weight to be updated        delta w=c(di-oi)oi(1-oi)xk
					weightUpdate=err*learningRate*hiddenLayer->neurons[k].activation;
					outputLayer->neurons[j].weight[k]+=weightUpdate;
				}
				//upadte the bias
				weightUpdate=err*learningRate*BIAS;
				outputLayer->neurons[j].weight[k]+=weightUpdate;
			}
			//upatde the hidden layer weight
			for (j=0;j<hiddenLayer->neuronNum;++j){
				err=0;
				for (k=0;k<outputLayer->neuronNum;++k){
					err+=outputLayer->neurons[k].error*outputLayer->neurons[k].weight[j];
				}
				err*=hiddenLayer->neurons[j].activation*(1-hiddenLayer->neurons[j].activation);
				//update the input weight 
				for (k=0;k<hiddenLayer->neurons[j].inputNum-1;++k){
					weightUpdate=err*learningRate*setIn[i][k];
					hiddenLayer->neurons[j].weight[k]+=weightUpdate;
					//leave for add momentum
				}
				//update the bias
				weightUpdate=err*learningRate*BIAS;
				hiddenLayer->neurons[j].weight[k]+=weightUpdate;
			}
		}
		epoch++;	
	}
	void train(vector<vector<double> > &setIn,vector<vector<double> > &setOut)
	{
		while (true)
		{
			cout<<"training epoch= "<<epoch<<endl;
			trainSingleEpoch(setIn,setOut);
			//if convergence
			if (0.5*errorSum/(setIn.size()*outputLayerNeuronNum)<minError) {
				cout<<"error sum smaller than threshold,finish trainning\n";
				break;
			}
			if (epoch>maxEpoch){
				cout<<"epoch larger than threshold,finish trainning\n";
				break;
			}
		}
	}
	//void readGraph()
	void saveParameter(ofstream &out)
	{
		//out<<inputLayerNeuronNum<<" "<<outputLayerNeuronNum<<" "<<hiddenLayerNeuronNum<<endl;
		//out<<learningRate<<" "<<maxEpoch<<" "<<minError<<endl;
		for (int i=0;i<hiddenLayer->neuronNum;++i){
			for (int j=0;j<hiddenLayer->neurons[i].inputNum;++j)
				out<<hiddenLayer->neurons[i].weight[j]<<endl;
		}
		for (int i=0;i<outputLayer->neuronNum;++i){
			for (int j=0;j<outputLayer->neurons[i].inputNum;++j)
				out<<outputLayer->neurons[i].weight[j]<<endl;
		}
	}

	//important!!!!!
	//I do not check the validity, so be carefull the main parameter must be the same
	void readParameter(ifstream &in)
	{
		for (int i=0;i<hiddenLayer->neuronNum;++i){
			for (int j=0;j<hiddenLayer->neurons[i].inputNum;++j)
				in>>hiddenLayer->neurons[i].weight[j];
		}
		for (int i=0;i<outputLayer->neuronNum;++i){
			for (int j=0;j<outputLayer->neurons[i].inputNum;++j)
				in>>outputLayer->neurons[i].weight[j];
		}
	}

};

//Sigmod function (dose not consider lamada)   because it is coherent with the learning speed
double Sigmod(double x)
{
	return 1/(1+exp(-x));
}




#endif 
