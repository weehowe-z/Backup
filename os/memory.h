//this file is the main memory
//first version by array  (pretent to implement as red black tree
#ifndef MEM_H
#define MEM_H

#include <queue>
#include <math.h>
#include <vector>

int process_name_to_int(string process_name);
int process_address_to_int(string address);



class addressinfo//to combine two important parameter
{
	public:
	int name;
	int address;
	//int reference_bit;
	//int priority;
	
	
	addressinfo(int n,int add)
	{
		name=n;
		address=add;
	//	reference_bit=1;
	//	priority=0;
	}
	
	//addressinfo(int n,int add,int prior)
//	{
//		name=n;
//		address=add;
	//	reference_bit=bit;
		//priority=prior;
//	}
	
	addressinfo(string n,string add)
	{
		name=process_name_to_int(n)-1;
		address=process_address_to_int(add);
		//reference_bit=1;
		//priority=0;
	}
};


class memory
{
public:	
	int mode;
	int size;
	int size_max;
	int size_process;
	int** mem;//as all the address is at most FF
	queue<addressinfo> fifoqueue;
	//priority_queue<addressinfo,vector<addressinfo>,greater<addressinfo> > lruqueue;
	vector<addressinfo> lruqueue;
		
	int size_max_cmu[10];
	int size_cmu[10];
	queue<addressinfo> fifoqueue_cmu[10];		
		
	memory(int maxsize,int process_num,int process_mode)
	{
		mode=process_mode;

		size = 0;
		size_max = maxsize;
		size_process=process_num;
		mem= new int*[size_process];
		for (int i=0;i<size_process;++i) mem[i]=new int[256];
		for (int i=0;i<size_process;++i)
		{
			for (int j=0;j<256;++j) mem[i][j]=0;
		}
		//for cmu alg
		if (mode==5)
		{
			if (maxsize<10) mode=0;//if not enough change to fifo
			for (int i=0;i<10;++i)
			{
				size_max_cmu[i]=maxsize/10;
				size_cmu[i]=0;
			}
		}
	}
		
	~memory()
	{
		for (int i=0;i<size_process;++i) delete []mem[i];
		delete []mem;
	}
	
	
	void append(int name,int address)
	{
		//cout<<mode<<endl;
		if (mode==0)
		{
			if (size==size_max)
			{
				//printf("memory is full, replace mem[%d][%d]\n",fifoqueue.front().name,fifoqueue.front().address);
				mem[fifoqueue.front().name][fifoqueue.front().address]=0;
				mem[name][address]=1;
				fifoqueue.pop();
				fifoqueue.push(addressinfo(name,address));
			}
			else 
			{
				fifoqueue.push(addressinfo(name,address));
				mem[name][address]=1;
				++size;
			}
		}
		else if (mode==1)
		{
			if (size==size_max)
			{
				mem[lruqueue.begin()->name][lruqueue.begin()->address]=0;
				mem[name][address]=1;
				lruqueue.erase(lruqueue.begin());
				lruqueue.push_back(addressinfo(name,address));
			}
			else
			{
				lruqueue.push_back(addressinfo(name,address));
				mem[name][address]=1;
				++size;
			}
		}
		
		
		//SEC CHANCE
		else if (mode==2)
		{
			//2 refer to has two chances
			if (size==size_max)
			{
				while(mem[fifoqueue.front().name][fifoqueue.front().address]==2)
				{
					//cout<<i++<<endl;
					mem[fifoqueue.front().name][fifoqueue.front().address]=1;
					fifoqueue.push(addressinfo(fifoqueue.front().name,fifoqueue.front().address));
					fifoqueue.pop();
				}
				//printf("memory is full, replace mem[%d][%d]\n",fifoqueue.front().name,fifoqueue.front().address);
				mem[fifoqueue.front().name][fifoqueue.front().address]=0;
				mem[name][address]=2;
				fifoqueue.pop();
				fifoqueue.push(addressinfo(name,address));
			}
			else 
			{
				fifoqueue.push(addressinfo(name,address));
				mem[name][address]=2;
				++size;
			}
		}
		
		//MY algorithm second-lru
		else if (mode==3)
		{
			if (size==size_max)
			{
				while(mem[lruqueue.begin()->name][lruqueue.begin()->address]==2)
				{
					mem[lruqueue.begin()->name][lruqueue.begin()->address]=1;
					lruqueue.push_back(addressinfo(lruqueue.begin()->name,lruqueue.begin()->address));
					lruqueue.erase(lruqueue.begin());
				}
				mem[lruqueue.begin()->name][lruqueue.begin()->address]=0;
				mem[name][address]=2;
				lruqueue.erase(lruqueue.begin());
				lruqueue.push_back(addressinfo(name,address));
			}
			else
			{
				lruqueue.push_back(addressinfo(name,address));
				mem[name][address]=2;
				++size;
			}
		}
		else if (mode==5)
		{
			int part= name%10;
			if (size_cmu[part]==size_max_cmu[part])
			{
				//printf("memory is full, replace mem[%d][%d]\n",fifoqueue_cmu[part].front().name,fifoqueue_cmu[part].front().address);
				mem[fifoqueue_cmu[part].front().name][fifoqueue_cmu[part].front().address]=0;
				mem[name][address]=1;
				fifoqueue_cmu[part].pop();
				fifoqueue_cmu[part].push(addressinfo(name,address));
			}
			else 
			{
				fifoqueue_cmu[part].push(addressinfo(name,address));
				mem[name][address]=1;
				++size_cmu[part];
			}
		}
		
	}
	
	bool find(int process_id,string process_address)
	{		
		if (mode==0)
		{
			int name = process_id;
			int address = process_address_to_int(process_address);
			if (mem[name][address]==1) return true;
			else return false;
		}
		else if (mode==1)
		{
			int name = process_id;
			int address = process_address_to_int(process_address);
			if (mem[name][address]==1) 
			{
				vector<addressinfo>::iterator it;
				int i=0;
				for (it=lruqueue.begin();it->name!=name||it->address!=address;++it)
				{
					++i;
				}
				lruqueue.push_back(addressinfo(name,address));
				lruqueue.erase(lruqueue.begin()+i);
				return true;
			}
			else return false;
		}
		else if (mode==2)
		{
			int name = process_id;
			int address = process_address_to_int(process_address);
			if (mem[name][address]==2) 
			{
				return true;
			}
			else if (mem[name][address]==1)
			{
				mem[name][address]=2;
				return true;
			}
			else return false;
		}
		//second use
		else if (mode==3)
		{
			int name = process_id;
			int address = process_address_to_int(process_address);
			if (mem[name][address]==2) 
			{
				vector<addressinfo>::iterator it;
				int i=0;
				for (it=lruqueue.begin();it->name!=name||it->address!=address;++it)
				{
					++i;
				}
				lruqueue.push_back(addressinfo(name,address));
				lruqueue.erase(lruqueue.begin()+i);
				return true;
			}
			else if (mem[name][address]==1)
			{
				mem[name][address]==2;
				return true;
			}
			else return false;
		}
		else if (mode==5)
		{
			int name = process_id;
			int address = process_address_to_int(process_address);
			if (mem[name][address]==1) return true;
			else return false;
		}
		
	}
	
	int getsize()
	{
		return size;
	} 
};

int process_name_to_int(string process_name)
{
	char* temp;
	temp=(char*)process_name.data();//ignore the P
	return atoi(temp+1);
}

int process_address_to_int(string address)
{
	int num=0;
	if (address[3]!='\0')
	{
		if (address[2]>='0'&&address[2]<='9') num+=(address[2]-'0')*16;
		else if (address[2]>='a'&&address[2]<='f') num+=(address[2]-'a'+10)*16;	
		if (address[3]>='0'&&address[3]<='9') num+=(address[3]-'0');
		else if (address[3]>='a'&&address[3]<='f') num+=(address[3]-'a'+10);
	}
	else
	{
		if (address[2]>='0'&&address[2]<='9') num+=(address[2]-'0');
		else if (address[2]>='a'&&address[2]<='f') num+=(address[2]-'a'+10);	
	}
	return num;
}


#endif