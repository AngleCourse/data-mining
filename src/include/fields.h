/**
 * 本文件中定义了日志和日志的字段, 以及访问日志和日志字段的接口 
 */
#ifndef FIELDS_H
#define FIELDS_H
#include <string>
using std::string;
/**
 * 日志中的时间字段, 包括小时、分钟、秒和毫秒，格式为24小时制
 */
class TimeInitial{
    public:
        TimeInitial(string time);
        /**
         * 返回此时间字段对应的小时,即为主机在一天的几点发起的DNS请求
         */
        string getHour();
        /**
         * 返回此时间字段对应的分钟数
         */
        string getMin();
        /**
         * 返回此时间字段对应的秒
         */
        string getSec();
        /**
         * 返回此时间字段对应的毫秒
         */
        string getMill();
    private:
        // Corresponding to the 'time' field in the log record
        string time;
};
/**
 * 日志中的主机IP地址字段，IP均为IPV4
 */
class HostInitial{
    public:
        HostInitial(string host);
        /**
         * 返回主机IP地址
         */
        string getIP();
    private:
        // Host IP address. IPV4
        string ip;
};
/**
 * 日志中的URL字段
 */
class URLInitial{
    public:
        URLInitial(string url);
        /**
         * 返回URL
         */
        string getURL();
    private:
        // Corresponding 'URL' field in every log record 
        string url;
};
/**
 * 日志中的一次DNS查询中涉及到的所有的DNS服务器, 不包括
 * 本地域名服务器的地址
 */
class DNSInitial{
    public:
        DNSInitial(string dns);
        /**
         * 返回本次DNS查询中所有由本地域名服务器发起查询的DNS服务器的数量
         */
        int getNumofDNS();
        /**
         * 返回本次DNS查询中所有由本地域名服务器发起查询的DNS服务器的地址
         */
        string* getDNS();
    private:
        // Corresponding 'DNS' field in every log record, exclude the IP address
        // of local default DNS server.
        string dns;
};
class LogEntry{
    public:
        LogEntry(long id, string time, string host, string url, string defdns, string dns);
        /**
         * 返回本条日志对应的ID序号
         */
        long getID();
        /**
         * 返回本条日志的时间字段
         */
        TimeInitial getTime();
        /**
         * 返回发起DNS查询的用户主机
         */
        HostInitial getHost();
        /**
         * 返回用户主机请求的URL
         */
        URLInitial getURL();
        /**
         * 返回本地DNS服务器地址
         */
        string getDefaultDNS();
        /**
         * 返回所有本地DNS服务器发起查询的DNS服务器
         */
        DNSInitial getDNS();
    private:
        // Log ID
        long id;
        // Time to start request DNS translate
        TimeInitial time;
        // Host of DNS request
        HostInitial Host;
        // Request URL
        URLInitial url;
        // Local DNS server
        string defdns;
        // All of the DNS Server envolved during a DNS translation, except
        // the loal DNS server.
        DNSInitial dns;
};
#endif
