#include <iostream>
#include <fstream>
#include <vector>
#include <ctime> //clock, clock_t, CLOCKS_PER_SEC
#include "./fields.h"
#include "./loadlog.h"
//#define DEBUG
//#define D_LOAD_LENGTH 100
using std::string;
using std::ifstream;
using std::getline;

// 容器的默认容量
const long INITIAL_SIZE = 200000;


LogList** loadfiles(string* files, int num){
    LogList** loglists = new LogList*[num];
    clock_t t;
    for(int i = 0; i<num; i++){
        // ifstream(const char *, openmode)
        // So needs a type cast. 
        if(files[i].empty()){
            continue;
        }
        ifstream input(files[i].c_str(), std::ifstream::in);
        std::cout<<"Starting loading log file: "<<files[i];
        t = clock();
        LogList* log = new LogList(input);
        t = clock()-t;
        std::cout<<", loads "<< log->getNumofLogs() <<" logs in "
            <<((float)t)/CLOCKS_PER_SEC<<" seconds\n";

        loglists[i] = log;
        input.close();
    }
    return loglists;
}
std::vector<LogEntry> LogList::getLogs(){
    return logs;
}
LogList::LogList(ifstream & input){
	logs.reserve(INITIAL_SIZE);
	// 下面开始加载
	loadlogs(input);
	// 重置迭代器
	reset();
}
int LogList::getNumofLogs(){
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
    num = (num > (int)logs.size())?logs.size():num;
    std::vector<LogEntry>::iterator it1 = logs.begin();
    for(int i = 1; i <= num; i++){
    	std::cout<<it1->getID()<<": "<<it1->getTime().toString();
        std::cout<<" "<<it1->getHost().getIP()<<" "<<
    			it1->getURL().getURL()<<" "<<it1->getDefaultDNS()
    			<<" "<<it1->getDNS().toString()<<std::endl;		
        it1++;
    }
}
void LogList::loadlogs(ifstream & input){
	string field;
	string time, host, url, defdns,dns;
	while(!getline(input, field, '|').eof()){
		time.assign(field);
		getline(input, field, '|');
        host.assign(field);
		getline(input, field, '|');
        url.assign(field.substr(field.find("?", 0)+2));
		getline(input, field, '|');
        defdns.assign(field);
		getline(input, field);
        //eliminate \r.
        dns.assign(field.substr(0, field.size()-1));
		LogEntry *entry = new LogEntry(logs.size()+1, time, host, url, defdns, dns);
        if(entry->getDNS().getNumofDNS() == 0){
            delete entry;
        }else{logs.push_back(*entry);}
#ifdef DEBUG
        if(logs.size() >= D_LOAD_LENGTH){
            break;
        }
#endif
	}	
#ifdef DEBUG
    this->print(D_LOAD_LENGTH);
#endif
}


