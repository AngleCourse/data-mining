
#ifndef LOADLOG_H
#define LOADLOG_H
#include <fstream>
#include <vector>
#include "./fields.h"


extern const long INITIAL_SIZE;

/**
 * 将日志文件加载进内存, 并且转化成数组格式再用于数据挖掘的核心算法
 */
class LogList{
    public:
        /**
         * 从"input"中加载日志文件到内存中
         */
        LogList(std::ifstream & input);
        /**
         * 返回本次加载的日志数量
         */
        long getNumofLogs();
        /**
         * 从第一条日志开始逐条返回日志记录。
         * 
         * Note：当日志全部返回时，后续调用返回空值；可以通过调用reset()
         *       来重置
         */
        LogEntry getNextLogEntry();
        /**
         * 重置迭代器，getNextLogEntry下次返回第一条日志记录
         */
        void reset();
        /**
         * 打印读入的前 num 条日志, 只用于测试
         */
        void print(int num);
    private:
        /**
         * Load log file from the specified input.
         */
        void loadlogs(std::ifstream & input);
        std::vector<LogEntry> logs;
        std::vector<LogEntry>::iterator it;
};

LogList** loadfiles(string* files, int num);
#endif