

#include "cache_way.h"

int way_init(way_t *this) {
    int r;
    for (int i = 0; i < N_SETS; i++) {
        if ((r = line_init(&this->lines[i])) < 0) {
            return -1;
        }
    }
    return 0;
}

int way_destroy(way_t *this) {
    for (int i = 0; i < N_SETS; i++) {
        line_destroy(&this->lines[i]);
    }
    return 0;
}

bool way_tag_match(way_t* this, int tag, int index) {
    line_t line = this->lines[index];
    return line_is_valid(&line) && line_tag_match(&line, tag);
}

char way_get_byte(way_t* this, int index, int offset) {

    return line_get_byte_at(&this->lines[index], offset);
}

int way_get_line_count(way_t* this, int index) {
    return this->lines[index].count_since_access;
}

void way_update_line_count(way_t* this, int index) {
    this->lines[index].count_since_access++;
}

void way_reset_line_count(way_t* this, int index) {
    this->lines[index].count_since_access = 0;
}

void way_flush(way_t* this) {
    for (int i = 0; i < N_SETS; i++) {
        this->lines[i].count_since_access = 0;
        this->lines[i].valid = false;
    }
}
