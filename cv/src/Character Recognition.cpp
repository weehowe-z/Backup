#include <iostream>
#include "NeuralNet.h"
#include "Neuron.h"
#include "NeuronLayer.h"
#include <fstream>
#include <string>
#include <atlimage.h>
#include <stdlib.h>

//img size 28*28px

using namespace std;

#define SAMPLE_NUM 100      //sample number per character
#define TEST_NUM 20   //default test case, 10 case per character  total 100
#define LENGTH 28  // bmp size
#define INPUT_DIMENSION 28*28
#define OUTPUT_DIMENSION 10  // 0~9 10 types
#define HIDDEN_LAYER_NEURON_NUM 10
#define TRAINNING_SPEED 0.005
#define MAX_EPOCH 200
#define MIN_ERROR 0.0005


int main()
{
	int a;//use for pause

	char readParaFlag;//if read the parameters (network) which have been trained
	//char modifyParaFlag;// if the user want to modify the training parameters
	bool needTrainningFlag=false;
	vector<vector<double> > inSet;
	vector<vector<double> > outSet;
	vector<vector<double> > testSet;
	vector<vector<double> > testoutSet;//use to calculate the hit ratio in test default
	vector<vector<double> > selfDefSet;
	vector<double> temp_vec;

	int sample_num = SAMPLE_NUM;
	int test_num = TEST_NUM;
	int input_dimension = INPUT_DIMENSION;
	int output_dimension = OUTPUT_DIMENSION;
	int hidden_layer_neuron_num = HIDDEN_LAYER_NEURON_NUM;
	int max_epoch = MAX_EPOCH;
	double trainning_speed = TRAINNING_SPEED;
	double min_error =MIN_ERROR;

	ifstream infile;
	ofstream outfile;//to save the parameters


	//deal with the trainning data
	CImage img;
	COLORREF pixel;
	int maxY=LENGTH;
	int maxX=LENGTH;
	int avg;
	byte r,g,b;
	string path;
	char temp_char[10];
	string temp_string;

	string pathHead="..\\Data\\Train\\";
	for (int i=0;i<OUTPUT_DIMENSION;++i){
		for (int j=1;j<=SAMPLE_NUM;++j){
			temp_string=itoa(j,temp_char,10);//change j to an int
			path=pathHead+char('0'+i)+" ("+temp_string+").bmp";
			img.Load((char*)path.data());
		//	maxY=img.GetHeight();
		//	maxX=img.GetWidth();
			for (int x=0;x<maxX;++x){
				for (int y=0;y<maxY;++y){
					pixel=img.GetPixel(x,y);
					r=GetRValue(pixel);  
					g=GetGValue(pixel);  
					b=GetBValue(pixel);
					avg=(int)((r+g+b)/3);
					if (avg>128) temp_vec.push_back(1);
					else temp_vec.push_back(0);
				}
			}
			inSet.push_back(temp_vec);
			temp_vec.clear();
			
			for (int x=0;x<i;++x) temp_vec.push_back(0);
			temp_vec.push_back(1);
			for (int x=i+1;x<OUTPUT_DIMENSION;++x) temp_vec.push_back(0);
			
			outSet.push_back(temp_vec);
			temp_vec.clear();

			img.Destroy();//important!!!!
		}
	}

	//deal with the test data
	pathHead="..\\Data\\Test_Default\\";
	for (int i=0;i<OUTPUT_DIMENSION;++i){
		for (int j=1;j<=TEST_NUM;++j){
			temp_string=itoa(j,temp_char,10);//change j to an int
			path=pathHead+char('0'+i)+" ("+temp_string+").bmp";
				img.Load((char*)path.data());
				//maxY=img.GetHeight();
				//maxX=img.GetWidth();
				for (int x=0;x<maxX;++x){
					for (int y=0;y<maxY;++y){
						pixel=img.GetPixel(x,y);
						r=GetRValue(pixel);  
						g=GetGValue(pixel);  
						b=GetBValue(pixel);
						avg=(int)((r+g+b)/3);
						if (avg>128) temp_vec.push_back(1);
						else temp_vec.push_back(0);
					}
				}
				testSet.push_back(temp_vec);
				temp_vec.clear();


				for (int x=0;x<i;++x) temp_vec.push_back(0);
				temp_vec.push_back(1);
				for (int x=i+1;x<OUTPUT_DIMENSION;++x) temp_vec.push_back(0);
				testoutSet.push_back(temp_vec);
				temp_vec.clear();
				
				img.Destroy();
		}
	}

	/*cout<<"Do you need to read the trained parameters? y or n >> ";
	cin>>modifyParaFlag;
	if (modifyParaFlag=='y'){
		needTrainningFlag = true;
	}
	*/
	NeuralNet network(INPUT_DIMENSION,OUTPUT_DIMENSION,HIDDEN_LAYER_NEURON_NUM,TRAINNING_SPEED,MAX_EPOCH,MIN_ERROR);
	
	
	cout<<"Do you need to read the trained parameters? y or n >> ";
	cin>>readParaFlag;
	if (readParaFlag=='y'){
		needTrainningFlag=false;
		infile.open("..\\Trained_Parameters.txt");
		network.readParameter(infile);
		infile.close();
	}
	else if (readParaFlag=='n'){
		needTrainningFlag=true;
		outfile.open("..\\Trained_Parameters.txt");
		network.train(inSet,outSet);
		network.saveParameter(outfile);
		outfile.close();
	}
	else {
		cout<<"error input!\n";
		return -1;
	}
	cout<<endl<<endl;


	//default test
	int count=0;
	int hitcount=0;
	for (int i=0;i<OUTPUT_DIMENSION;++i)
	{
		for (int j=0;j<TEST_NUM;++j)
		{
			network.calculateOutput(testSet[count],temp_vec);
			cout<<"recognize bmp "<<i<<"("<<j+1<<")"<<endl;
			for (int k=0;k<OUTPUT_DIMENSION;++k) cout<<temp_vec[k]<<" ";
			cout<<endl;
			int index=0;
			for (int k=0;k<OUTPUT_DIMENSION;++k){
				if (temp_vec[k]>temp_vec[index]) index=k;
			}
			cout<<"This number is likely to be "<<index<<endl;
			if (testoutSet[count][index]==1) {cout<<"hit\n";++hitcount;}
			temp_vec.clear();
			++count;
		}
	}

	cout<<"------------------------------------------\n";
	cout<<"Hit ratio: "<<double(hitcount)/count<<endl;


	int self_define_num;
	cout<<"\nPlz input the image number you want to recognize>> ";
	cin>>self_define_num;
	

	pathHead="..\\Data\\Test_User\\";
	for (int i=0;i<self_define_num;++i){
			// if input n need bmp from 0.bmp to N-1.bmp
			temp_string=itoa(i,temp_char,10);//change j to an int
			path=pathHead+temp_string+".bmp";
			img.Load((char*)path.data());
				for (int x=0;x<maxX;++x){
					for (int y=0;y<maxY;++y){
						pixel=img.GetPixel(x,y);
						r=GetRValue(pixel);  
						g=GetGValue(pixel);  
						b=GetBValue(pixel);
						avg=(int)((r+g+b)/3);
						if (avg>128) temp_vec.push_back(1);
						else temp_vec.push_back(0);
					}
				}
				selfDefSet.push_back(temp_vec);
				temp_vec.clear();
				img.Destroy();
	}

	for (int i=0;i<self_define_num;++i){
			network.calculateOutput(selfDefSet[i],temp_vec);
			cout<<"recognize "<<i<<".bmp"<<endl;
			//for (int k=0;k<OUTPUT_DIMENSION;++k) cout<<temp_vec[k]<<" ";
			//cout<<endl;
			int index=0;
			for (int k=0;k<OUTPUT_DIMENSION;++k){
				if (temp_vec[k]>temp_vec[index]) index=k;
			}
			cout<<"This number is likely to be "<<index<<endl;
			temp_vec.clear();
	}

	cout<<"Press any key and enter to exit>> ";
	cin>>a;
	return 0;
}