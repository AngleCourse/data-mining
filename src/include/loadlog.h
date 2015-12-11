
#ifndef LOADLOG_H
#define LOADLOG_H
#include <fstream>
#include <vector>
#include <map>
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
        int getNumofLogs();
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
        std::vector<LogEntry> getLogs();
        /**
         * 打印读入的前 num 条日志, 只用于测试
         */
        void print(int num);
    private:
        /**
         * Load log file from the specified input.
         */
        void loadlogs(std::ifstream & input);
        /**
         * Calculate the statistical characteristics.
         * Including data distribution.
         */
        void calStatis(LogEntry & entry);
        /**
         * Print the statistical information.
         */
        void printStatis();
        std::vector<LogEntry> logs;
        std::vector<LogEntry>::iterator it;
        // The following is for statistical usage.
        // pair<length, number_of_entries_with_length>
        std::map<int, int> count;
};
/**
 * 从给定的文件中读出所有日志, num 指定日志文件的数量
 * eg:  LogList[0] 中保存从第一个文件中读出的日志
 *      LogList[1] 中保存从第二个文件中读出的日志
 */
LogList** loadfiles(string* files, int num);
#endif
