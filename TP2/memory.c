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
    console_log_debug("Reading byte from address %d", address);
    return this->memory[address];
    //todo falta verificar en cache primero, y si no esta traer el bloque a cache
}

void memory_read_tocache(memory_t *this, unsigned int blocknum, unsigned int way, unsigned int set) {

}

void memory_write_tocache(memory_t *this, unsigned int address, unsigned char value) {
}

void memory_write_byte(memory_t *this, unsigned int address, unsigned char value) {
    console_log_debug("Writing %d to address %d", value, address);
    unsigned int block_number = address / (MEMSIZE_BYTES / BLOCK_SIZE);
    this->memory[address] = value;
}

float memory_get_cache_miss_rate(memory_t *this) {
    console_log_debug("Getting cache miss rate");
    return cache_get_miss_rate(&this->cache);
}

void memory_flush_cache(memory_t *this) {
    console_log_debug("Flushing cache");
}

int memory_destroy(memory_t *this) {
    cache_destroy(&this->cache);
    free(this->memory);
    this->memory = NULL;
    this = NULL;
    return 0;
}
