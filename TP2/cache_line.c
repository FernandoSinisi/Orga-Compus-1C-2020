#include <stdlib.h>

#include "cache_line.h"


int line_init(line_t* line) {
    line->bytes = (char*)malloc(sizeof(char) * LINE_SIZE);
    if (line->bytes == NULL) {return -1;}

    line->valid = false;
    line->count_since_access = 0;
    return 0;
}

void line_destroy(line_t* line) {
    free(line->bytes);
}

bool line_is_valid(line_t* line) {
    return line->valid;
}

bool line_tag_match(line_t* line, int tag) {
    return line->tag == tag;
}

char line_get_byte_at(line_t* line, int offset) {
    return line->bytes[offset];
}