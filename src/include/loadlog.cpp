#include <iostream>
#include <algorithm> // find
#include <fstream>
#include <vector>
#include <ctime> //clock, clock_t, CLOCKS_PER_SEC
#include <map>
#include "./fields.h"
#include "./loadlog.h"
//#define DEBUG
//#define D_LOAD_LENGTH 100
using std::string;
using std::ifstream;
using std::getline;

// 容器的默认容量
const long INITIAL_SIZE = 40000;


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
        std::cout<<"Starting loading log file: "<<files[i]
            <<"\n";
        t = clock();
        LogList* log = new LogList(input);
        t = clock()-t;
        std::cout<<"Loads "<< log->getNumofLogs() <<" logs in "
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
void LogList::calStatis(LogEntry & entry){
    int key = entry.getDNS().getNumofDNS();
    if(count.find(key) == count.end()){
        count.insert(std::pair<int, int> (key, 1));
    }else{
        count[key] = count[key]+1;
    }
    
     
}
void LogList::printStatis(){
    std::cout<<"Data distribution: \n";
    std::map<int, int> temp;
    for(std::map<int, int>::iterator it = count.begin();
            it != count.end(); ++it){
        temp.insert(std::pair<int, int>(it->second, it->first));
    }
    int num = 0;
    for(std::map<int, int>::reverse_iterator it = temp.rbegin();
            it != count.rend(); ++it){
        if(num++ > temp.size()){
            break;
        }
        std::cout<<"Length "<<it->second<<" "
            <<(((float) it->first)/logs.size()) * 100
            <<"%\t";
    }
    std::cout<<"\n";
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
        }else{
            logs.push_back(*entry);
#ifdef DEBUG_STATISTICS
        calStatis(*entry);
#endif
        }
#ifdef DEBUG
        if(logs.size() >= D_LOAD_LENGTH){
            break;
        }
#endif
	}	
#ifdef DEBUG
    this->print(D_LOAD_LENGTH);
#endif
#ifdef DEBUG_STATISTICS
    this->printStatis();
#endif
}


