#ifndef CACHE_LINE_H
#define CACHE_LINE_H

#include <stdbool.h>

#define LINE_SIZE 128

typedef struct {
    char* bytes;
    unsigned int tag;
    unsigned int count_since_access;
    bool valid;
} line_t;

int line_init(line_t* line);

void line_destroy(line_t* line);

#endif // CACHE_LINE_H
