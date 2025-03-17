
#include <string.h>
#include <time.h>
#include <stdio.h>

//Format of Log outcome
const char* tdFormat = "%d-%02d-%02d %02d:%02d:%02d [%s] %s\n";


typedef enum{
	WARN,
	INFO,
	ERROR,
	UNKNOWN,
}eLevels;

// this is inline and much faster however it's difficult to follow
void Log(eLevels Lvl, const char* Txt) {  // Added const for string literal safety
    time_t t = time(NULL);
    struct tm tm;
    localtime_r(&t, &tm);  // Thread-safe version
    
    fprintf(stderr, "%d-%02d-%02d %02d:%02d:%02d [%s] %s\n",
           tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
           tm.tm_hour, tm.tm_min, tm.tm_sec,
           (const char*[]){"WARN", "INFO", "ERROR", "UNKNOWN"}[Lvl], Txt);
}



