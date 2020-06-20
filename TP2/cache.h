#ifndef TP2_CACHE_H
#define TP2_CACHE_H

#include "cache_way.h"
#include <stdlib.h>

#define BLOCK_SIZE 128
#define CACHE_SIZE 4096
#define WAYS 4
#define WAY_SIZE 1024

typedef struct {
    float miss_rate;
    way_t* ways;
} cache_t;

int cache_init(cache_t* this);
unsigned int cache_get_offset(unsigned int address);
unsigned int cache_get_tag(unsigned int address);
unsigned int cache_get_index(unsigned int address);

unsigned int cache_find_set(cache_t* this, unsigned int address);
unsigned int cache_select_oldest(cache_t* this, unsigned int setnum);
int cache_compare_tag(cache_t* this, unsigned int tag, unsigned int set);
float cache_get_miss_rate(cache_t* this);
int cache_destroy(cache_t* this);

#endif //TP2_CACHE_H
