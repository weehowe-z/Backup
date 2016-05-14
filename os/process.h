#ifndef PROCESS_H
#define PROCESS_H
#include <string>
#include <iomanip>
#include <iostream>
//#include "memory.h"
using namespace std;


extern int process_name_to_int(string process_name);
class process
{
public:
	string name;
	double start_time;
	double cpu_time;
	int IO_count;
	int need_cycle;
	int id;
	
	process(string process_name="Unkown",double stime=0,double ctime=0,int IO=0,int ncycle=0)
	{
		name=process_name;
		start_time=stime;
		cpu_time=ctime;
		IO_count=IO;
		need_cycle=ncycle;
		id=process_name_to_int(name)-1;
	}
	
	void print()
	{
		cout<<fixed << setprecision(2); 
		cout<<"id:"<<id<<" name:"<<name<<" start time:"<<start_time<<" cpu time:"<<cpu_time<<" need time:"<<need_cycle<<endl;
	}
	
};

#endif