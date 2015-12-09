#include <iostream>
#include <fstream>
#include <vector>
#include "./fields.h"
#include "./loadlog.h"
using std::string;
using std::ifstream;
using std::getline;

// 容器的默认容量
const long INITIAL_SIZE = 200000;

LogList** loadfiles(string* files, int num){
    LogList** loglists = new LogList*[num];
    for(int i = 0; i<num; i++){
        // ifstream(const char *, openmode)
        // So needs a type cast. 
        ifstream input(files[i].c_str(), std::ifstream::in);
        LogList log(input);
        loglists[i] = &log;
    }
}
LogList::LogList(ifstream & input){
	logs.reserve(INITIAL_SIZE);
	// 下面开始加载
	loadlogs(input);
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
		return LogEntry();
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
void LogList::loadlogs(ifstream & input){
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
		LogEntry entry = LogEntry(logs.size()+1, time, host, url, defdns, dns);
		logs.push_back(entry);
#ifdef DEBUG
        if(logs.size() > D_LOAD_LENGTH){
            input.close();
            break;
        }
#endif
	}	
}


