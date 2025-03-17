// logger.c
#include "logMacro.h"
#include <time.h>
#include <stdio.h>

void log_message(int level, const char* message) {
    LOG(level, message);
}
