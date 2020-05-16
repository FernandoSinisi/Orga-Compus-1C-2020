#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "matrix.h"

#define _POSIX_C_SOURCE 200809L
#define OPT_HELP "-h"
#define OPT_VERSION "-V"
#define OUT_PREFIX "-o"

const char VERSION[] = "Version 1.0\n";

const char HELP[] = "Uso:\n\tconway -h\n\tconway -V\n\tconway i M N inputfile [-o outputprefix]\nOpciones:\n\t-h, --help Imprime este mensaje.\n\t-V, --versión Da la versión del programa.\n\t-o Prefijo de los archivos de salida.\nEjemplos:\n\tconway 10 20 20 glider -o estado\nLos archivos de salida se llamarán estado_n.pbm.\nSi no se da un prefijo para los archivos de salida,\nel prefijo será el nombre del archivo de entrada.\n";

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

int get_num(char* str){
	if(str[0]=='0' && strlen(str)==1) return 0;
	for(int i = 0; i < strlen(str)-1;i++){
		if(!isdigit(str[i]))return -1;
	}
	int num = atoi(str);
	if (num==0) return -1;
	return num;
}

int verify_argv(int argc, char *argv[]) {

    if (argc == 2) {
        if (!strcmp(argv[1], OPT_HELP)) {
            fprintf(stdout, HELP);
            return 1;
        }
        if (!strcmp(argv[1], OPT_VERSION)) {
            fprintf(stdout, VERSION);
            return 1;
        }
        fprintf(stderr, "Parametro desconocido: %s\n", argv[1]);
        return -1;
    }
    if (argc == 7) {
		int i = get_num(argv[1]);
		int m = get_num(argv[2]);
		int n = get_num(argv[3]);
		
        if (!strcmp(argv[5], OUT_PREFIX) && i > 0 && m > 0 && n > 0) {
            fprintf(stdout, "%s\n", "Aca ejecutaria juego\n");
            return 0;
        }
        fprintf(stderr, "%s\n", "Error: Parametros incorrectos. Pruebe convay -h para ver ejemplo");
        return -1;
    }

    fprintf(stderr, "%s\n", "Error: Numero de parametros incorrecto.");
    return -1;
}

int add_values(char* line,ssize_t len, matrix_t* matrix_a ){
	fprintf(stdout, "tamaño de la linea %ld\n", len);
	fprintf(stdout, "linea %s\n", line);
	const char *space = " ";
	char *token;
	int num;
	int cont = 0;
	int pos[2];
	
	token = strtok(line, space);
	
	while( token != NULL ) {
		fprintf(stdout, "contador %d\n", cont);
		fprintf(stdout, "token %s\n", token);
		num = get_num(token);
		fprintf(stdout, "numero leido %d\n", num);
		if(num == -1 || cont >= 2){
			fprintf(stderr, "%s\n", "Error: Archivo de entrada invalido");
			return -1;
		}
		pos[cont] = num;
		fprintf(stdout, "pos en contador %d\n", pos[cont]);
		cont++;
		token = strtok(NULL, space);
	}
	if(cont != 2){
		fprintf(stderr, "%s\n", "Error: Archivo de entrada invalido");
		return -1;
	}
	add_value(matrix_a, pos);
	return 0;
}


int init_matrix(matrix_t* matrix_a,FILE * input_file){
	
	int r;
	char* line = NULL;
	size_t size = 0;
	
	ssize_t len = len = getline(&line, &size, input_file);
	while(len != -1){
		r = add_values(line,len,matrix_a);
		if(r != 0){
			fprintf(stderr, "Error, Problema en la lectura del archivo \n");
			free((void*)line);
			fclose(input_file);
			return -1;;
		}
		len = getline(&line, &size, input_file);
	}
	free((void*)line);
	fclose(input_file);
	return 0;
}

/* *****************************************************************
 *                    FUNCIONES PRINCIPALES
 * *****************************************************************/

int run(size_t i, size_t m, size_t n ,FILE * input_file){
	
	int r;
	matrix_t* matrix_a = create_matrix(m, n);
    if (!matrix_a) {
    	return -2;
    }
    
    r = init_matrix(matrix_a,input_file);
    if(r != 0){
		destroy_matrix(matrix_a);
		return -1;
	}
    
	
	return 0;
}


int main(int argc, char *argv[]) {

    int r = verify_argv(argc, argv);
    if (r > 0) {
        return 0;
    } else if (r < 0) {
        return -r;
    }
        
    FILE *input_file = fopen(argv[4],"r");
    
	if(!input_file){
		fprintf(stderr, "Error, no se puede abrir el archivo\n");
		return -1;
	}
    
    size_t i = get_num(argv[1]);
	size_t m = get_num(argv[2]);
	size_t n = get_num(argv[3]);
    
    r = run(i,m,n,input_file);


    if (r < 0) {
        exit(-r);
    }

    fclose(input_file);
    return 0;
}

