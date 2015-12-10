#include<iostream>
#include<vector>
#include<map>
#include <algorithm> // find
#include "./include/fields.h"
#include "./include/loadlog.h"
using namespace std;

extern LogList ** loadfiles(string *files, int num);
void testing();

vector<  vector<int>  > trans_ip_int(const vector<LogEntry> &entry_ip,map<string,int> &ip_map);
void count_sort_ip(vector< vector<int> > &ip_int_link, vector<int>  &order, vector<int>  &count);
void sort_transaction(vector<  vector<int>  > &unsorted_transaction, vector<int>  order);
int   max_index(const  vector<int>  & ivec);

int main(){
    testing();
    return 0;
}
void testing(){
    cout<< "Starting to test loading module...\n";
    const int num_files = 5;
    string* filenames = new string[num_files];
    filenames[0] = "../raw/CSession_01";
    LogList ** loglists = loadfiles(filenames, num_files);
    cout<< "Testing done.\n";
    cout<<"Starting to test Precomputing module...\n";
    map<string, int> ip_map;
    vector<  vector<int>  > tran_ip = trans_ip_int((loglists[0]->getLogs()), ip_map);   
    vector<int>  order, count;
    count_sort_ip(tran_ip, order, count);
    sort_transaction(tran_ip, order); 
    cout<<"Testing done.\n";
    delete [] filenames;
    
}
/**
int  main() 
{
cout<<"no error!"<<endl;	
}
*/

vector< vector<int> > trans_ip_int(const vector<LogEntry> &entry_t, map<string,int> &ip_map)
{
	vector< vector<int> > entry_int_link;
	for(int i=0;i<entry_t.size();i++)
	{
		string *s = entry_t[i].getDNS().getDNS();
		for(int j=0;j<entry_t[i].getDNS().getNumofDNS();j++)
		{
			map<string ,int >::iterator I_ip;
			I_ip = ip_map.find(s[j]);
			if(I_ip == ip_map.end())
			{
				if(ip_map.size()==ip_map.max_size()) 
					cout<<"map overflow!!!!!!!!"<<endl; 
				else
					ip_map.insert(s[j],ip_map.size()+1);
			}
			entry_int_link[i].push_back(ip_map[s[j]]);
				
		}
	}
	
	return entry_int_link;
	
}
void count_sort_ip(vector< vector<int> > &ip_int_link, vector<int>  &order, vector<int>  &count)
{
	map<int,int> ipKey_and_num;
	map<int,int> ipKey_and_num2;
	map<int,int>::iterator I_ip;
	for(int i=0;i<ip_int_link.size();i++)
	{
		for(int j=0;j<ip_int_link[i].size();j++)
		{
			if((I_ip=ipKey_and_num.find(ip_int_link[i][j]))==ipKey_and_num.end())
				ipKey_and_num.insert(ip_int_link[i][j],1) ;  
			else
				ipKey_and_num[ip_int_link[i][j]] = ipKey_and_num[ip_int_link[i][j]]+1;                             
		}
	}
	while(ipKey_and_num.size()!=0)
	{
        int temp = 0;
        int lable = 0;
		for(int k=1;k<=ipKey_and_num.size();k++)
		{
			if(ipKey_and_num[k]>temp)
			{
				temp = ipKey_and_num[k];
				lable = k;
			}
			
		}
		order.push_back(lable);
		count.push_back(temp);
		ipKey_and_num.erase(lable);
	}
} 

void sort_transaction(vector< vector<int> > &unsorted_transaction, vector<int>  order)
{
	
	for(int i=0;i<unsorted_transaction.size();i++)
	{
		 vector<int>  count;
		for(int j=0;j<unsorted_transaction[i].size();j++)
		{
			 vector<int> ::const_iterator iter;
   			iter=find(order.begin(),order.end(),unsorted_transaction[i][j]);
    		count.push_back(iter-order.begin());
		}
		 vector<int>  tmp = unsorted_transaction[i];
		 vector<int>  reverse_tmp;
		while(count.size()>0)
	   {
		    int index=max_index(count);
		    reverse_tmp.push_back(tmp[index]);
		    tmp.erase(tmp.begin()+index);
		    count.erase(count.begin()+index);
	   }
	   reverse(reverse_tmp.begin(),reverse_tmp.end());
	   unsorted_transaction[i]=reverse_tmp;
	}
}
int   max_index(const  vector<int>  & ivec)
{
	int max_num=-100;
	int index;
	for(int i=0;i<ivec.size();++i)
	{
	   if(ivec[i]>max_num)
	   {
	    max_num=ivec[i];
	    index=i;
	   }
	}
	return   index;
}




























