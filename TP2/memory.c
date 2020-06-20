#include <stddef.h>
#include <stdio.h>
#include "memory.h"
#include "log.h"

void memory_init(memory_t *this) {
    this = malloc(sizeof(memory_t));
    if (!this) {
        //TODO CAMBIAR POR console_log_error
        fprintf(stderr, "Error: no se pudo crear la memoria.\n");
        return;
    }
    this->memory = malloc(sizeof(unsigned char) * MEMSIZE_BYTES);
    if (!this->memory) {
        fprintf(stderr, "Error: no se pudo alocar la memoria.\n");
        free(this);
        return;
    }

    this->cache = malloc(sizeof(cache_t));
    if (!this->cache) {
        fprintf(stderr, "Error: no se pudo alocar la memoria cache.\n");
        free(this->memory);
        free(this);
        return;
    }
    cache_init(this->cache);
    fprintf(stdout, "Memoria creada.\n");
    fprintf(stdout, "Miss rate %5f .\n",this->cache->miss_rate);
}

unsigned char memory_read_byte(memory_t *this, unsigned int address) {
    console_log_debug("Reading byte from address %d", address);
    return this->memory[address];
    //todo falta verificar en cache primero, y si no esta traer el bloque a cache
}

void memory_read_tocache(memory_t *this, unsigned int blocknum, unsigned int way, unsigned int set) {

}

void memory_write_byte(memory_t *this, unsigned int address, unsigned char value) {
    console_log_debug("Writing %d to address %d", value, address);
    unsigned int block_number = address / (MEMSIZE_BYTES / BLOCK_SIZE);
    fprintf(stdout, "Writing %d to address %d\n", value, address);
    this->memory[address] = value;
    fprintf(stdout, "Writed in memory OK\n");
    //todo verificar si esta en cache y escribir en cache si está
    //memory_write_tocache(address, value);
}

float memory_get_cache_miss_rate(memory_t *this) {
    console_log_debug("Getting cache miss rate");
    return cache_get_miss_rate(this->cache);
}

void memory_flush_cache(memory_t *this) {
    console_log_debug("Flushing cache");
}

int memory_destroy(memory_t *this) {
    cache_destroy(this->cache);
    free(this->memory);
    free(this);
    return 0;
}
