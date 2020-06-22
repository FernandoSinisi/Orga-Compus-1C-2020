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

bool line_is_valid(line_t* line);

bool line_tag_match(line_t* line, int tag);

char line_get_byte_at(line_t* line, int offset);

#endif // CACHE_LINE_H
