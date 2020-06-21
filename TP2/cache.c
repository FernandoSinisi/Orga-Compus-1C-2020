#include <stdio.h>
#include "cache.h"
#include "log.h"

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

unsigned int cache_get_index(unsigned int address) {
    return (address / BLOCK_SIZE) % (WAY_SIZE / BLOCK_SIZE);
}

unsigned int cache_get_tag(unsigned int address) {
    return (address / BLOCK_SIZE) / (WAY_SIZE / BLOCK_SIZE);
}

unsigned int cache_find_set(cache_t *this, unsigned int address) {
    return 0;
}

unsigned int cache_select_oldest(cache_t *this, unsigned int setnum) {
    return 0;
}

float cache_get_miss_rate(cache_t *this) {
    if (this->total_accesses == 0){
        return 0;
    }
    return (float)this->total_misses/(float)this->total_accesses;
}

int cache_write(cache_t *this, unsigned int address, unsigned char value) {
    return -1;
}

int cache_read(cache_t *this, unsigned int address, unsigned char* data_save) {
    return -1;
}

int cache_save_block(cache_t *this, unsigned char *block, unsigned int way, unsigned int set) {
    return 0;
}

int cache_flush() {
    return 0;
}

int cache_destroy(cache_t *this) {
    for (int i=0; i<WAYS; i++){
        way_destroy(&this->ways[i]);
    }
    return 0;
}
