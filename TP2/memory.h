#ifndef TP2_MEMORY_H
#define TP2_MEMORY_H

#include "cache.h"

#define MEMSIZE_BYTES 65536

typedef struct {
    cache_t cache;
} memory_t;

void memory_init(memory_t* this);
unsigned char memory_read_byte(memory_t* this, unsigned int address);
void memory_read_tocache(memory_t* this, unsigned int blocknum, unsigned int way, unsigned int set);
void memory_write_byte(memory_t* this, unsigned int address, unsigned char value);
float memory_get_cache_miss_rate(memory_t* this);
void memory_flush_cache(memory_t* this);
int memory_destroy(memory_t* this);

#endif //TP2_MEMORY_H