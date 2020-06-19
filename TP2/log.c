#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "log.h"

int console_log_debug(char *format, ...) {
    char* debug = getenv("debug");
    if (!debug)
        return 0;
    va_list argptr;
    va_start(argptr, format);
    vprintf(format, argptr);
    va_end(argptr);
    return 0;
}

int console_log(char *format, ...) {
    va_list argptr;
    va_start(argptr, format);
    vprintf(format, argptr);
    va_end(argptr);
    return 0;
}
