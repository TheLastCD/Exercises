
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


int* iReturnDateTime() // statically declare time and date
{
    static int data[6];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    data[0] = tm.tm_year + 1900;
    data[1] = tm.tm_mon + 1;
    data[2] = tm.tm_mday;
    data[3] = tm.tm_hour;
    data[4] = tm.tm_min;
    data[5] = tm.tm_sec;
    return data;

}

char* cReturnLevelchar(eLevels lvl) {
    switch(lvl) {
        case WARN:
            return "WARN";
        case INFO:
            return "INFO";
        case ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

void Log(eLevels Lvl, char* Txt) {
	int* iDateTime = iReturnDateTime();
	char* Level = cReturnLevelchar(Lvl);
	printf(tdFormat,
		iDateTime[0], iDateTime[1], iDateTime[2],  // Date
		iDateTime[3], iDateTime[4], iDateTime[5],  // Time
		Level, Txt);
}



