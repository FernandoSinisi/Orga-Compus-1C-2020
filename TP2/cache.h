#ifndef TP2_CACHE_H
#define TP2_CACHE_H

#include "cache_way.h"
#include <stdlib.h>

#define BLOCK_SIZE 128
#define CACHE_SIZE 4096
#define WAYS 4
#define WAY_SIZE 1024

typedef struct {
    int total_accesses;
    int total_misses;
    way_t ways[WAYS];
} cache_t;

int cache_init(cache_t* this);
unsigned int cache_get_offset(unsigned int address);
unsigned int cache_get_tag(unsigned int address);
unsigned int cache_get_index(unsigned int address);
unsigned int cache_find_set(cache_t* this, unsigned int address);
unsigned int cache_select_oldest(cache_t* this, unsigned int setnum);

// lee el dato de cache si está presente, sino actualiza los misses
// devuelve el byte si está presente, sino devuelve -1.
char cache_read(cache_t* this, unsigned int address);

// escribe el dato a cache si está presente el bloque, sino actualiza los misses
// devuelve 0 si se escribio, 1 si no se encuentra
int cache_write(cache_t* this, unsigned int address, unsigned char value);

int cache_compare_tag(cache_t* this, unsigned int tag, unsigned int set);
float cache_get_miss_rate(cache_t* this);
int cache_destroy(cache_t* this);

#endif //TP2_CACHE_H
