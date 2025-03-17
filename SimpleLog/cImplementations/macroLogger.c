#include <time.h>
#include <stdio.h>

typedef enum { 
    ERROR, 
    WARN, 
    INFO, 
    UNKNOWN } 
eLevels;

#define LOG_LEVEL INFO

#define LOG(LVL, TXT) do {                                   \
    if(LVL > LOG_LEVEL) break;                               \
    time_t _t = time(NULL);                                  \
    struct tm _tm;                                           \
    localtime_r(&_t, &_tm);                                  \
    fprintf(stderr, "%d-%02d-%02d %02d:%02d:%02d [%s] %s\n",\
        _tm.tm_year+1900, _tm.tm_mon+1, _tm.tm_mday,        \
        _tm.tm_hour, _tm.tm_min, _tm.tm_sec,                \
        (const char*[]){"ERROR","WARN","INFO","UNKNOWN"}[LVL], TXT); \
} while(0)

// Usage:
//LOG(INFO, "System initialized");
