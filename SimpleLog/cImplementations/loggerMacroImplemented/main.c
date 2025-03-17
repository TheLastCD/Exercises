// main.c
#include "logMacro.h"

void log_message(int level, const char* message);

int main() {
    log_message(1, "This is a warning message");
    return 0;
}
