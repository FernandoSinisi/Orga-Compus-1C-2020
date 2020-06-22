#ifndef CACHE_CACHE_WAY_H
#define CACHE_CACHE_WAY_H

#include "cache_line.h"

#define N_SETS 8

typedef struct {
    line_t lines[N_SETS];
} way_t;

// Inicializa la via, devuelve 0 en caso de exito, -1 en caso de que
// no se pueda pedir la memoria necesaria
int way_init(way_t* this);

bool way_tag_match(way_t* this, int tag, int index);

char way_get_byte(way_t* this, int index, int offset);

int way_destroy(way_t* this);

int way_get_line_count(way_t* this, int index);

void way_update_line_count(way_t* this, int index);

void way_reset_line_count(way_t* this, int index);

// Solo resetea el contador y setea el bit de validez a invalido
void way_flush(way_t* this);

#endif //CACHE_CACHE_WAY_H
