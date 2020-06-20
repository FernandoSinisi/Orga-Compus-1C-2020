#include <stdio.h>
#include "cache.h"
#include "log.h"

int cache_init(cache_t *this) {
    this->miss_rate = 0;
    this->ways = malloc(sizeof(way_t) * WAYS);
    if(!this->ways){
        //TODO console_log_error
        fprintf(stderr, "Error: no se pudo crear las vias de la memoria cache \n");
        return -1;
    }
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

float cache_get_miss_rate(cache_t *this) {
    return this->miss_rate;
}

int cache_destroy(cache_t *this) {
    free(this->ways);
    this->ways = NULL;
    free(this);
    this = NULL;
    return 0;
}
