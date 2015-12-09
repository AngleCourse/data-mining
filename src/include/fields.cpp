
/**
 * 本文件实现了访问日志和日志各字段的接口
 */
#include <algorithm>
#include "./fields.h"
TimeInitial::TimeInitial(string time){
   this->time = time; 
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

HostInitial::HostInitial(string host){
    this->ip = host;
}
string HostInitial::getIP(){
    return ip;
}

URLInitial::URLInitial(string url){
    this->url = url;
}
string URLInitial::getURL(){
	return url;
}

DNSInitial::DNSInitial(string dns){
    int count = 0;

	seperate_dns = new string[dns.]	
	this->dns 	= dns;
}

LogEntry::LogEntry(long id, string time, string host, string url, string defdns, string dns){
	this->id 	= id;
	this->time 	= time;
	this->host 	= host;
	this->url 	= url;
	this->defdns= defdns;
	this->dns 	= dns;	
}
TimeInitial LogEntry::getTime(){
	return time;
}
HostInitial LogEntry::getHost(){
	return host;
}
URLInitial LogEntry::getURL(){
	return url;
}
string LogEntry::getDefaultDNS(){
	return defdns;
}
DNSInitial LogEntry::getDNS(){
	return dns;
}
