
#ifndef LOADLOG_H
#define LOADLOG_H
#include <fstream>
/**
 *
 */
class LogList{
    public:
        LoadList();
        LoadList(ifstream input);
        long getNumofLogs();
        LogEntry* getLogs();
}
#endif
