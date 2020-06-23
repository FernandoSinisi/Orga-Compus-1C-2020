#include <stdlib.h>

#include "cache.h"
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

bool line_tag_match(line_t* line, unsigned int tag) {
    return line->tag == tag;
}

char line_get_byte_at(line_t* line, unsigned int offset) {
    return line->bytes[offset];
}

void line_write_byte_at(line_t* line, unsigned int offset, unsigned char value) {
    line->bytes[offset] = value;
}

void line_fill_block(line_t* line, unsigned char* block, unsigned int tag) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        line->bytes[i] = block[i];
    }
    line->count_since_access = 0;
    line->valid = true;
    line->tag = tag;
}