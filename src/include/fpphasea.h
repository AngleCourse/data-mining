#ifndef FPPHASEA_H
#define FPPHASEA_H
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>
#include "./loadlog.h"
#include "./fields.h"
using namespace std;

vector< vector<int> > trans_ip_int(const vector<LogEntry> &entry_ip, map<string,int> &ip_map);//将整个Log中的ip转换成整形的id 
void count_sort_ip(vector< vector<int> > &ip_int_link,vector<int> &order,vector<int> &count);//对整个LOG中的每个ip进行计数，并按照计数从大到小的顺序进行排序 
void sort_transaction(vector< vector< int > > &unsorted_transaction, vector< int > &order); //对每个transaction中的ip按照给定的顺序进行排序 
int   max_index(const vector<int> & ivec);//找到整数数组中的最大值得索引值 


vector< vector<int> > trans_ip_int(const vector<LogEntry> &entry_t, map<string,int> &ip_map)//根据整个数据库，将每个transaction的ip从string转化成唯一的int值，并返回。 
{
	vector< vector<int> > entry_int_link;//每个transaction是从0开始编号的 
	vector <int> temp;
	for(int i=0;i<entry_t.size();i++)
	{
		string* s = entry_t[i].getDNS().getDNS();//string类型的字符数组可能出错   返回的是第几个字符 
		temp.clear();
		for(int j=0;j<entry_t[i].getDNS().getNumofDNS();j++)
		{
			map<string ,int >::const_iterator I_ip = ip_map.find(s[j]);
			//cout<<s[j]<<endl;
			//I_ip = ip_map.find(s[j]);
			if(I_ip == ip_map.end())
			{
				if(ip_map.size()==ip_map.max_size()) 
					cout<<"map overflow!!!!!!!!"<<endl; 
				else
					ip_map.insert(pair<string,int>(s[j],ip_map.size()+1));//转化而来的ip的id是从1开始计数的 
			}
			int index = ip_map[s[j]];
			temp.push_back(index);
			
				
		}
		entry_int_link.push_back(temp);//将每个transaction中的ip从string链路转化成int链 
	}
	
	return entry_int_link;
	
}
void count_sort_ip(vector< vector<int> > &ip_int_link,vector<int> &order,vector<int> &count)
{
	map<int,int> ipKey_and_num;
	map<int,int> ipKey_and_num2;
	map<int,int>::iterator I_ip;
	for(int i=0;i<ip_int_link.size();i++)
	{
		for(int j=0;j<ip_int_link[i].size();j++)
		{
			if((I_ip=ipKey_and_num.find(ip_int_link[i][j]))==ipKey_and_num.end())
				ipKey_and_num.insert(pair<int,int>(ip_int_link[i][j],1));  
			else
				ipKey_and_num[ip_int_link[i][j]] = ipKey_and_num[ip_int_link[i][j]]+1;
		}
	}
    map<int, int>::iterator it = ipKey_and_num.begin();
	while(it != ipKey_and_num.end())
	{
#ifdef DEBUG
        cout<<"while 1**";
#endif
		int temp=0;
		int lable = 0;
        int k = 0;
        for(it = ipKey_and_num.begin(); it != ipKey_and_num.end(); it++){
           k = (*it).first;
           if(ipKey_and_num[k]>temp)
			{
				temp = ipKey_and_num[k];
				lable = k;
			}
        }
        /**
		for(int k=1;k<=ipKey_and_num.size();k++)
		{

			if(ipKey_and_num[k]>temp)
			{
				temp = ipKey_and_num[k];
				lable = k;
			}
			
		}
        */
		order.push_back(lable);
		count.push_back(temp);
		ipKey_and_num.erase(lable);
	}
} 

void sort_transaction(vector< vector<int> > &unsorted_transaction, vector<int> &order)//将每个transaction中的ip进行排序 
{
	
	for(int i=0;i<unsorted_transaction.size();i++)
	{
		vector<int> count;
		for(int j=0;j<unsorted_transaction[i].size();j++)
		{
			vector<int>::const_iterator iter;
   			iter=find(order.begin(),order.end(),unsorted_transaction[i][j]);
    		count.push_back(iter-order.begin());//得到该事务各个项在倒序序列的序号
		}
		vector<int> tmp = unsorted_transaction[i];
		vector<int> reverse_tmp;
		while(count.size()>0)
	   {
#ifdef DEBUG
           cout<<"while 2 **";
#endif
		    int index=max_index(count);
		    reverse_tmp.push_back(tmp[index]);
		    tmp.erase(tmp.begin()+index);
		    count.erase(count.begin()+index);
	   }
	   reverse(reverse_tmp.begin(),reverse_tmp.end());
	   unsorted_transaction[i]=reverse_tmp;
	}
}
int   max_index(const vector<int> & ivec)
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
#endif
