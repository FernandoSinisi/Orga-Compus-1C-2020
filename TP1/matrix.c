#include <errno.h>
#include "matrix.h"

void check_fprint(FILE* fp, int copy);

unsigned int coordToArrayIndex(matrix_t* matrix, int x, int y){
    return x*matrix->rows + y;
}

matrix_t* create_matrix(unsigned int rows, unsigned int cols) {
    
    matrix_t* matrix = malloc(sizeof(matrix_t));
    if (!matrix) return NULL;

    matrix->rows = rows;
    matrix->cols = cols;
 
    unsigned int n = rows*cols;
    matrix->array = malloc(sizeof(unsigned char)* n);
    if (!matrix->array) {
        free(matrix);
        return NULL;
    }

    return matrix;
}

void destroy_matrix(matrix_t* m) {
    free(m->array);
    free(m);
}

int add_value(matrix_t* matrix_a, unsigned int *pos){
	fprintf(stdout, "llego al add_value de matrix %d\n", pos[0]);
	fprintf(stdout, "llego al add_value de matrix %d\n", pos[1]);

    int index;
    if (index = coordToArrayIndex(pos[0], pos[1]) > matrix_a->rows*matrix_a->cols - 1){
        return 1;
    }

	matrix_a->array[index] = 1;
	return 0;
}


int print_matrix(FILE* fp, matrix_t* m) {

    size_t i = 0;
    int copy;

    copy = fprintf(fp, "%d", m->rows);
    check_fprint(fp, copy);

    size_t n = m->rows;
    for (; i < n ; i++) {
        copy = fprintf(fp," %d", m->array[i]);
	    check_fprint(fp, copy);
	}

    copy = fprintf(fp, "\n");
    check_fprint(fp, copy);

    return 0;
}

void check_fprint(FILE* fp, int copy) {
    fflush(fp);
    if (copy < 0) {
        fprintf(stderr,"Error en la copia del archivo resultante\n");
        exit(EXIT_FAILURE);
    }
}

int iterate_matrix(matrix_t* matrix) {

}