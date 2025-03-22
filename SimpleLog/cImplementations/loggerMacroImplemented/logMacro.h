#define LOG(LVL, TXT) do {                                   \
    time_t _t = time(NULL);                                  \
    struct tm _tm;                                           \
    localtime_r(&_t, &_tm);                                  \
    fprintf(stderr, "%d-%02d-%02d %02d:%02d:%02d [%s] %s\n", \
        _tm.tm_year+1900, _tm.tm_mon+1, _tm.tm_mday,         \
        _tm.tm_hour, _tm.tm_min, _tm.tm_sec,                 \
        (const char*[]){"ERROR","WARN","INFO","DEBUG"}[LVL], TXT); \
} while(0)
