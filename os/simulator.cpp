//in order to improve the performance of the simulator,I rewrite the simulator with c++
//for using stl library~


#include "cse356header.h"
#include "process.h"
#include "memory.h"

#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;


#define CYCLETIME 100000
#define CONTEXT_SWITCH_CYCLE 50
#define PAGING_CYCLE 1000

#define FIFO 0
#define LRU 1
#define SEC_CH 2
#define SEC_LRU 3
#define LUCKY 4
#define CMU 5
//Communism algorithm


int main(int argc,char* argv[])
{
	
	
	
	
	
	if (argc!=5){
		printf("Plz Input like this:\n");	
		printf("./simulator pages quantum pr-policy trace-file!\n");
		return -1;
	}
	
	int page_num=atoi(argv[1]);//is the number of physical pages
	int quantum=atoi(argv[2]);//is the number of cycles in a scheduling quantum  
	string pr_policy=argv[3];//is one of "fifo", "lru" or "2ch‐alg" page replacement policies
	//is the name of the scheduling trace file
	
	
	printf("\nInit information:\n");
	printf("page number: %d pages\n",page_num);
	printf("quantum: %d cycles\n",quantum);
	printf("page replacement policy: %s\n\n",pr_policy.c_str());
	
	
	queue<process> trace_queue;
	queue<process> ready_queue;
	queue<process> block_queue;
	queue<addressinfo> pending_queue;
	
	string temp_s;//to save the reading char;
	char* temp_c;
	
	
	ifstream trace_sch;
	trace_sch.open(argv[4]);
	if (!trace_sch){
				printf("Error,failed to open file '%s'.\n",argv[4]);
				exit(-1);
			}
	
	//read the process info
	while(trace_sch>>temp_s){
		process tmp;
		tmp.name=temp_s;
		trace_sch>>temp_s;
		tmp.start_time=atof((char*)temp_s.data());
		trace_sch>>temp_s;
		tmp.cpu_time=atof((char*)temp_s.data());
		trace_sch>>temp_s;
		tmp.IO_count=atoi((char*)temp_s.data());
		tmp.need_cycle=tmp.cpu_time*CYCLETIME;
		tmp.id=process_name_to_int(tmp.name)-1;
		tmp.print();
		trace_queue.push(tmp);
	}
	
	int total_process_num=trace_queue.size();
	cout<<"process number: "<<total_process_num<<endl<<endl;
	
	
	unsigned long cycle=0;
	unsigned long running_cycle=0;
	unsigned long wasting_cycle=0;
	int paging_cycle=0;
	int context_switch_cycle=0;
	double time=0;
	process current_process;
	

	string last_running_process;
	ifstream *memfile;
	ofstream result;
	
	int *pagefault;
	queue<string> *mem_ref;
	
	memfile = new ifstream[total_process_num];
	pagefault= new int[total_process_num];
	mem_ref =new queue<string>[total_process_num];
	
	
	//open the result file
	string pagenum_s=argv[1];
	string quantum_s=argv[2];
	string data_s=argv[4];
	string temp=pagenum_s+"_"+quantum_s+"_"+pr_policy+"_"+data_s;
	result.open((char*)temp.data());
	result<<"Process\telapsed_time\tpage_fault\n";
	//open all the process traces
	for (int i=0;i<total_process_num;++i) 
	{
		
		string temp=".mem";
		temp=trace_queue.front().name+temp;
		temp_c=(char*)temp.data();
		memfile[i].open(temp_c);
		if (!memfile[i]) 
		{
			printf("Error,failed to open file.\n");
			exit(-1);
		}
		//init page fault
		pagefault[i]=0;
		//inti memref
		while(memfile[i]>>temp)//!!if using eof may casue problem but it depends
		{
			mem_ref[i].push(temp);
		}
		
		
		
		cout<<"mem trace["<<i<<"] size "<<mem_ref[i].size()<<endl;
		
		trace_queue.push(trace_queue.front());
		trace_queue.pop();
	}
	cout<<endl;
	
	int previous_process_id=trace_queue.front().id;
	
	//init the memory
	
	memory *mem;
	if (pr_policy=="fifo") mem = new memory(page_num,total_process_num,FIFO);
	else if (pr_policy=="lru") mem = new memory(page_num,total_process_num,LRU);
	else if (pr_policy=="2ch-alg") mem = new memory(page_num,total_process_num,SEC_CH);
	else if (pr_policy=="2ch-lru") mem =new memory(page_num,total_process_num,SEC_LRU);
	else if (pr_policy=="lucky") mem =new memory(page_num,total_process_num,LUCKY);
	else if (pr_policy=="cmu") mem =new memory(page_num,total_process_num,CMU);
	
	//stop only no process in any queue
	while(trace_queue.size()!=0||ready_queue.size()!=0||block_queue.size()!=0||running_cycle!=0)
	{
		//cout<<"now cycle "<<cycle<<endl;
		time=double(cycle)/CYCLETIME;
		//deal with the arrvial event
		if (trace_queue.front().start_time==time)
		{
			ready_queue.push(trace_queue.front());
			cout<<"process enqueue: "<<trace_queue.front().name<<" at "<<time<<endl;
			trace_queue.pop();
		} 
		
		//whether is doing content switch
		if (context_switch_cycle==0)
		{
			
			//if no running process and has a ready process
			if (running_cycle==0&&ready_queue.size()!=0)
			{
				current_process=ready_queue.front();
				ready_queue.pop();
				running_cycle=quantum;
				
				/*if (previous_process_id!=current_process.id)
				{
					context_switch_cycle=50;
					previous_process_id=current_process.id;
					continue;
				}
				*/
			}
			
			//if np process can run
			if (running_cycle==0&&ready_queue.size()==0)
			{
			    wasting_cycle++;
			}
			
			//if there is process still running
			if (running_cycle>0)
			{	
				if (mem->find(current_process.id,mem_ref[current_process.id].front()))
				{	
					--running_cycle;
					mem_ref[current_process.id].pop();
					//cout<<"Now Cycle: "<<cycle<<" Runing: "<<current_process.name<<endl;
					//cout<<"The process still has "<<current_process.need_cycle<<" cycles to run\n";
					current_process.need_cycle-=1;
					
					//running time expired
					if (running_cycle==0 && current_process.need_cycle>0) 
					{
						ready_queue.push(current_process); 
						context_switch_cycle=50;
					}
					//if finish the task
					else if (current_process.need_cycle==0){
						cout<<"\nNow Cycle: "<<cycle<<endl;
						cout<<current_process.name<<"'s process finished\n";
						cout<<current_process.name<<"'s elapsed time: "<<double(cycle)/CYCLETIME-current_process.start_time<<endl;
						cout<<current_process.name<<"'s total page faults: "<<pagefault[current_process.id]<<endl;
						cout<<endl;
						result<<current_process.name<<"\t"<<double(cycle)/CYCLETIME-current_process.start_time<<"\t\t"<<pagefault[current_process.id]<<endl;
						running_cycle=0;
					}
				}
			
				else 
				{
					++pagefault[current_process.id];
					block_queue.push(current_process);
					pending_queue.push(addressinfo(current_process.name,mem_ref[current_process.id].front()));
					running_cycle=0;
					context_switch_cycle=50;
				}
			} 
		}
		
		// if is doing context switch
		else 
		{
			--context_switch_cycle;
			++wasting_cycle;
			//if (context_switch_cycle==0) cout<<"Context switch finished at "<<cycle<<endl;
		}
		
		//deal with the page replacement
		
		////has something pending
		if (paging_cycle==0&&pending_queue.size()!=0)
		{
			paging_cycle=PAGING_CYCLE;
		}
		
		if (paging_cycle!=0)
		{
			--paging_cycle;
			//if after paging,has finished
			if (paging_cycle==0)
			{
				mem->append(pending_queue.front().name,pending_queue.front().address);
				pending_queue.pop();
				ready_queue.push(block_queue.front());
				block_queue.pop();
				
			}
		}
		++cycle;
	}
	
	unsigned long total_page_faults=0;
	for(int i=0;i<total_process_num;++i) total_page_faults+=pagefault[i];
	
	printf("Total time: %.2fs\n",double(cycle)/CYCLETIME);
	printf("Total cycle: %ld\n",cycle);
	printf("Total idle cycle: %ld\n",wasting_cycle);
	printf("Total page faults: %ld\n",total_page_faults);
	
	result<<endl;
	result<<"Total time: "<<double(cycle)/CYCLETIME<<endl;
	result<<"Total cycle: "<<cycle<<endl;
	result<<"Total idle cycle: "<<wasting_cycle<<endl;
	result<<"Total page faults: "<<total_page_faults<<endl;
	
	trace_sch.close();
	for (int i=0;i<total_process_num;++i) memfile[i].close();
	result.close();
	delete []mem_ref;
	delete []memfile;
	delete []pagefault;
	delete mem;
	return 0;
}

