#include <stdio.h>
#include "cache.h"
#include "log.h"

int _cache_compare_update_count(cache_t* this, unsigned int tag, unsigned int set) {
    int way;
    if ((way = cache_compare_tag(this, tag, set)) < 0) {
        this->total_misses++;
        console_log("Cache miss");
        return -1;
    }
    console_log("Cache hit");
    cache_update_counts(this, set);
    way_reset_line_count(&this->ways[way], set);
    return way;
}

int cache_init(cache_t *this) {
    this->total_accesses = 0;
    this->total_misses = 0;
    int r;
    for (int i=0; i<WAYS; i++)
        if((r = way_init(&this->ways[i])) != 0)
            return r;
    return 0;
}

unsigned int cache_get_offset(unsigned int address) {
    return address % BLOCK_SIZE;
}

unsigned int cache_find_set(unsigned int address) {
    return (address / BLOCK_SIZE) % (WAY_SIZE / BLOCK_SIZE);
}

unsigned int cache_get_tag(unsigned int address) {
    return (address / BLOCK_SIZE) / (WAY_SIZE / BLOCK_SIZE);
}

unsigned int cache_select_oldest(cache_t *this, unsigned int setnum) {
    int max_count = -1;
    int max_count_way = -1;
    int curr_count;
    for (int i = 0; i < WAYS; i++) {
        if (!way_valid_line(&this->ways[i], setnum)) {
            return i; // Si no es valido uso ese;
        }
        if ((curr_count = way_get_line_count(&this->ways[i], setnum)) > max_count) {
            max_count = curr_count;
            max_count_way = i;
        }
    }
    return max_count_way;
}

float cache_get_miss_rate(cache_t *this) {
    if (this->total_accesses == 0){
        return 0;
    }
    return (float)this->total_misses/(float)this->total_accesses;
}

int cache_write(cache_t *this, unsigned int address, unsigned char value) {
    this->total_accesses++;

    int way;
    unsigned int set = cache_find_set(address);
    unsigned int tag = cache_get_tag(address);
    unsigned int offset = cache_get_offset(address);

    if ((way = _cache_compare_update_count(this, tag, set)) < 0) {
        return -1;
    }
    way_write_byte(&this->ways[way], set, offset, value);
    return 0;
}

int cache_read(cache_t *this, unsigned int address, unsigned char* data_save) {
    this->total_accesses++;

    int way;
    unsigned int set = cache_find_set(address);
    unsigned int tag = cache_get_tag(address);
    unsigned int offset = cache_get_offset(address);

    if ((way = _cache_compare_update_count(this, tag, set)) < 0) {
        return -1;
    }

    *data_save = way_get_byte(&this->ways[way], set, offset);
    return 0;
}

int cache_save_block(cache_t *this, unsigned char *block, unsigned int way, 
                     unsigned int set, unsigned int tag) {
    way_write_block(&this->ways[way], block, set, tag);
    return 0;
}

int cache_compare_tag(cache_t* this, unsigned int tag, unsigned int set) {
    for (int i = 0; i < WAYS; i++) {
        if (way_tag_match(&this->ways[i], tag, set)) {
            return i;
        }
    }
    return -1;
}

void cache_update_counts(cache_t* this, unsigned int index) {
    for (int i = 0; i < WAYS; i++) {
        way_update_line_count(&this->ways[i], index);
    }
}

int cache_flush(cache_t* this) {
    for (int i = 0; i < WAYS; i++) {
        way_flush(&this->ways[i]);
    }
    return 0;
}

int cache_destroy(cache_t *this) {
    for (int i=0; i<WAYS; i++){
        way_destroy(&this->ways[i]);
    }
    return 0;
}


