#include <stdlib.h>

#include "cache_line.h"


int line_init(line_t* line) {
    line->bytes = (char*)malloc(sizeof(char) * LINE_SIZE);
    if (line->bytes == NULL) {return -1;}

    line->valid = false;
    return 0;
}

void line_destroy(line_t* line) {
    free(line->bytes);
}