#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include "log.h"

int console_log_debug(char *format, ...) {
    char* debug = getenv("debug");
    if (debug == NULL)
        return 0;
    va_list argptr;
    va_start(argptr, format);
    vprintf(format, argptr);
    printf("\n");
    va_end(argptr);
    return 0;
}


int console_log_error(char *format, ...) {
    va_list argptr;
    va_start(argptr, format);
    vfprintf(stderr, format, argptr);
    printf("\n");
    va_end(argptr);
    return 0;
}

int console_log(char *format, ...) {
    va_list argptr;
    va_start(argptr, format);
    vprintf(format, argptr);
    printf("\n");
    va_end(argptr);
    return 0;
}
