#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct matrix {
    size_t rows;
    size_t cols;
    double* array;
};

typedef struct matrix matrix_t;

// Constructor de matrix_t
matrix_t* create_matrix(size_t rows, size_t cols);

// Destructor de matrix_t
void destroy_matrix(matrix_t* m);

// Imprime matrix_t sobre el file pointer fp en el formato solicitado por el enunciado
int print_matrix(FILE* fp, matrix_t* m);

//Agrega un valor 1 (celda viva) en la coordenada indicada
int add_value(matrix_t* matrix_a, int* pos);


#endif
