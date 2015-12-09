#include <iostream>
#include <fstream>
#include <vector>
#include "./fields.h"
#include "loadlog.h"
using std::string;
using std::ifstream;
LogList::LogList(ifstream input){
	logs.reserve(LogList::INITIAL_SIZE);
	// 下面开始加载
	loadlog(input);
	// 重置迭代器
	reset();
}
long LogList::getNumofLogs(){
    return logs.size();
}
LogEntry LogList::getNextLogEntry(){
	if (it != logs.end()){
		/* code */
		return *it++;
	}else{
		return NULL;
	}
}
void LogList::reset(){
	it = logs.begin();
}
void LogList::print(int num){
#ifndef DEBUG
    return;
#endif
    LogEntry entry;
    std::vector<LogEntry>::iterator it1 = logs.begin();
    for(int i = 1; i <= num; i++){
    	entry = *it1++;
    	std::cout<<entry.getID()<<": "<<entry.getTime().toString()
    			<<" "<<entry.getHost().getIP()<<" "<<
    			entry.getURL().getURL()<<" "<<entry.getDefaultDNS()
    			<<" "<<entry.getDNS().toString()<<std::endl;		
    }
}
void LogList::loadlogs(ifstream input){
	string field;
	string time, host, url, defdns, dns;
	while(!getline(input, field, '|').eof()){
		time = field;
		getline(input, field, '|');
		host = field;
		getline(input, field, '|');
		url = field;
		getline(input, field, '|');
		defdns = field;
		getline(input, field);
		dns 	= field.substr(0, field.size()-1);
		LogEntry entry = LogEntry(time, host, url, defdns, dns)
		logs.push_back(entry);
	}	
}


