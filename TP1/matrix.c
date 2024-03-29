#include <errno.h>
#include "matrix.h"
#define DOT_SIZE 64

extern unsigned int vecinos(unsigned char *a, unsigned int i, unsigned int j,
                            unsigned int M, unsigned int N);

void check_fprint(FILE* fp, int copy);

unsigned int coordToArrayIndex(matrix_t* matrix, int x, int y){
    return x*matrix->cols + y;
}

matrix_t* create_matrix(unsigned int rows, unsigned int cols) {
    
    matrix_t* matrix = malloc(sizeof(matrix_t));
    if (!matrix) return NULL;

    matrix->rows = rows;
    matrix->cols = cols;
 
    unsigned int n = rows*cols;
    matrix->array = malloc(sizeof(unsigned char)* n);
    memset(matrix->array, 0, sizeof(unsigned char) * n);
    if (!matrix->array) {
        free(matrix);
        return NULL;
    }

    return matrix;
}

void destroy_matrix(matrix_t* m) {
    if (m->array){
        free(m->array);
        m->array = NULL;
    }
    if (m){
        free(m);
        m = NULL;
    }
}

int add_value(matrix_t* matrix_a, unsigned int *pos){

    int index = coordToArrayIndex(matrix_a, pos[0], pos[1]);
    int limit = matrix_a->rows * matrix_a->cols;
    if (index >= limit){
        return 1;
    }

	matrix_a->array[index] = 1;
	return 0;
}


int print_matrix(FILE* fp, matrix_t* m) {
    int copy;
    
    /*El formato de archivo .pbm es:
    
    *	P1
    *	M N		   (tamaño de la matriz)
    * 	1 1 1 0 0  (cada numero 1 es un px "pintado")
    * 	0 0 0 1 0
    * 	0 1 1 0 1
    */
    
	copy = fprintf(fp,"P1\n");
    check_fprint(fp, copy);
    copy = fprintf(fp, "%d", m->rows*DOT_SIZE);
    check_fprint(fp, copy);
    copy = fprintf(fp, " ");
    copy = fprintf(fp, "%d", m->cols*DOT_SIZE);
    check_fprint(fp, copy);
    copy = fprintf(fp, "\n");
    check_fprint(fp, copy);
    for (int i = 0; i < m->rows; i++){
        for (int k = 0; k < DOT_SIZE; k++){
            for (int j = 0; j < m->cols; j++){
                int index = coordToArrayIndex(m, i, j);
                for (int l = 0; l < DOT_SIZE; l++){
                    copy = fprintf(fp, "%d ", m->array[index]);
                    check_fprint(fp, copy);
                }
            }
            copy = fprintf(fp, "\n");
            check_fprint(fp, copy);
        }
    }
    fflush(fp);
    return 0;
}

void check_fprint(FILE* fp, int copy) {
    if (copy < 0) {
        fprintf(stderr,"Error en la copia del archivo resultante\n");
        exit(EXIT_FAILURE);
    }
}

int iterate_matrix(matrix_t* matrix) {

    unsigned char* next_matrix = malloc(sizeof(unsigned char)
                                        *matrix->rows
                                        *matrix->cols);
    if (!next_matrix)
        return 1;

    for (unsigned int row = 0; row < matrix->rows; row++){
        for (unsigned int col = 0; col < matrix->cols; col++){
            unsigned int n = vecinos(matrix->array, row, col,
                                     matrix->rows, matrix->cols);
            int index = coordToArrayIndex(matrix, row, col);
            if ((n < 2) || (n > 3)){
                next_matrix[index] = 0;
            } else {
                next_matrix[index] = 1;
            }
        }
    }
    
    if (matrix->array)
        free(matrix->array);
    matrix->array = next_matrix;

    return 0;
}
