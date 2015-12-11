
/**
 * 本文件实现了访问日志和日志各字段的接口
 */
#include <algorithm>//std::count
#include <iostream>
#include <sstream> //std::isstringstream
#include <string>
#include "./fields.h"
//#define DEBUG
using std::string;
TimeInitial::TimeInitial(string& time){
   (this->time).assign(time); 
}
string TimeInitial::getHour(){
    return time.substr(0, 2);
}
string TimeInitial::getMin(){
    return time.substr(3, 2);
}
string TimeInitial::getSec(){
    return time.substr(6, 2);
}
string TimeInitial::getMill(){
    return time.substr(9);
}
string TimeInitial::toString(){
	return getHour()+":"+getMin()+":"+getSec()+"."+getMill();
}

HostInitial::HostInitial(string& host){
    (this->ip).assign(host);
}
string HostInitial::getIP(){
    return ip;
}

URLInitial::URLInitial(string& url){
    (this->url).assign(url);
}
string URLInitial::getURL(){
	return url;
}

DNSInitial::DNSInitial(string & dns){
    numofdns = std::count(dns.begin(),
            dns.end(), '|');
	seperate_dns = new string[numofdns];
    if((numofdns = filter(numofdns, dns)) == 0){
        (this->dns).assign("");
    }
    (this->dns).assign(dns);
}
int DNSInitial::getNumofDNS(){
    return numofdns;
}
int DNSInitial::filter(int num, string & dns){
    std::istringstream iss (dns);
    string last;
    for(int i = 0; i < num && !std::getline(iss, seperate_dns[i], '|').eof();i++){
        //下面检测是否会有连续的两个或两个以上DNS服务器地址
        //这种情况是本地服务器重复请求
        if(!last.empty() && (last.compare(seperate_dns[i]) == 0)){
#ifdef DEBUG
            std::cout<<"last: " <<last
                <<" current: "<<seperate_dns[i]<<" \n";
#endif
            return 0;
        }
        last.assign(seperate_dns[i]);
    }
    return num;
}
string* DNSInitial::getDNS(){
    return seperate_dns;
}
void DNSInitial::remap(){
    delete[] seperate_dns;
    seperate_dns = new string[numofdns];
    std::istringstream iss (dns);
    for(int i = 0; !std::getline(iss, seperate_dns[i], '|').eof();i++);
}
string DNSInitial::toString(){
#ifdef DEBUG
    string s;
    for(int i = 0; i< numofdns; i++){
        s.assign(s +" " + seperate_dns[i]);
    }
    return s;
#endif
    return dns;
}
DNSInitial::~DNSInitial(){
    //delete [] seperate_dns;
}
LogEntry::LogEntry(){
    this->id = 0;
    this->time = NULL;
    this->host = NULL;
    this->url  = NULL;
    this->dns  = NULL;
}

LogEntry::LogEntry(long id, string& time, string & host, string & url, string & defdns, string & dns){
	this->id = id;
	this->time = new TimeInitial(time);
	this->host = new HostInitial(host);
	this->url  = new URLInitial(url);
    (this->defdns).assign(defdns);
	this->dns  = new DNSInitial(dns);	
}
LogEntry::~LogEntry(){
    //delete this->time;
    //delete this->host;
    //delete this->url;
    //delete this->dns;
}
long LogEntry::getID(){
    return this->id;
}
TimeInitial LogEntry::getTime() const{
	return *time;
}
HostInitial LogEntry::getHost() const{
    return *host;
}
URLInitial LogEntry::getURL() const{
	return *url;
}
string LogEntry::getDefaultDNS() const{
    return defdns;
}
DNSInitial LogEntry::getDNS() const{
	return *dns;
}
bool LogEntry::isEmpty(){
    return id == 0; 
}
