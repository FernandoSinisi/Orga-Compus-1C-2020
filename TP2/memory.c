#include "memory.h"
#include "log.h"

void memory_init(memory_t *this) {

}

unsigned char memory_read_byte(memory_t *this, unsigned int address) {
    console_log_debug("Reading byte from address: %d\n", address);
    return 0;
}

void memory_read_tocache(memory_t *this, unsigned int blocknum, unsigned int way, unsigned int set) {

}

void memory_write_byte(memory_t *this, unsigned int address, unsigned char value) {
    console_log_debug("Writing %d to address %d\n", value, address);
}

float memory_get_cache_miss_rate(memory_t *this) {
    console_log_debug("Getting cache miss rate\n");
    return 0;
}

void memory_flush_cache(memory_t *this) {
    console_log_debug("Flushing cache\n");
}

int memory_destroy(memory_t *this) {
    return 0;
}
