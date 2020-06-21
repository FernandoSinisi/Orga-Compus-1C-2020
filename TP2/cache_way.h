#ifndef CACHE_CACHE_WAY_H
#define CACHE_CACHE_WAY_H

typedef struct {
    char* bytes;
} way_t;

int way_init(way_t* this);
int way_destroy(way_t* this);

#endif //CACHE_CACHE_WAY_H
