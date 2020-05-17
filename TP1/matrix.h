#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct matrix {
    unsigned int rows;
    unsigned int cols;
    unsigned char* array;
};

typedef struct matrix matrix_t;

// Constructor de matrix_t
matrix_t* create_matrix(unsigned int rows, unsigned int cols);

// Destructor de matrix_t
void destroy_matrix(matrix_t* m);

// Imprime matrix_t sobre el file pointer fp en el formato solicitado por el enunciado
int print_matrix(FILE* fp, matrix_t* m);

//Agrega un valor 1 (celda viva) en la coordenada indicada
int add_value(matrix_t* matrix_a, unsigned int* pos);

//Realiza una iteracion del juego
int iterate_matrix(matrix_t* matrix);


#endif
