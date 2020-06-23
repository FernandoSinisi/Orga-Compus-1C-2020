#include <stdio.h>
#include "memory.h"
#include "log.h"

int memory_init(memory_t *this) {
    this->memory = (unsigned char *) malloc(sizeof(unsigned char) * MEMSIZE_BYTES);
    if (!this->memory) {
        return -1;
    }
    return cache_init(&this->cache);
}

unsigned char memory_read_byte(memory_t *this, unsigned int address) {
    console_log_debug("memory: reading byte from address %d", address);
    unsigned char data;
    int r = cache_read(&this->cache, address, &data);
    if (r < 0){
        unsigned int set = cache_find_set(address);
        unsigned int way = cache_select_oldest(&this->cache, set);
        unsigned int tag = cache_get_tag(address);
        unsigned int blocknum = address/BLOCK_SIZE;
        _memory_read_tocache(this, blocknum, way, set, tag);
        return this->memory[address];
    }
    return data;
}

void _memory_read_tocache(memory_t *this, unsigned int blocknum,
                          unsigned int way, unsigned int set, unsigned int tag) {
    unsigned char block[BLOCK_SIZE];
    for (int i = 0; i < BLOCK_SIZE; i++){
        block[i] = this->memory[BLOCK_SIZE*blocknum + i];
    }
    cache_save_block(&this->cache, block, way, set, tag);
}

void _memory_write_tocache(memory_t *this, unsigned int address, unsigned char value) {
    cache_write(&this->cache, address, value);
}

void memory_write_byte(memory_t *this, unsigned int address, unsigned char value) {
    console_log_debug("memory: writing %d to address %d", value, address);
    this->memory[address] = value;
    _memory_write_tocache(this, address, value);
}

float memory_get_cache_miss_rate(memory_t *this) {
    console_log_debug("memory: getting cache miss rate");
    return cache_get_miss_rate(&this->cache);
}

void memory_flush_cache(memory_t *this) {
    console_log_debug("memory: flushing cache");
    cache_flush(&this->cache);
}

int memory_destroy(memory_t *this) {
    cache_destroy(&this->cache);
    free(this->memory);
    this->memory = NULL;
    return 0;
}
