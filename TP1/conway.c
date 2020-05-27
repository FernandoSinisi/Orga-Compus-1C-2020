#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "matrix.h"

#define OPT_HELP "-h"
#define OPT_VERSION "-V"
#define OUT_PREFIX "-o"

const char VERSION[] = "Version 1.0\n";

const char HELP[] = "Uso:\n\
					\tconway -h\n\
					\tconway -V\n\
					\tconway i M N inputfile [-o outputprefix]\nOpciones:\n\
					\t-h, --help Imprime este mensaje.\n\
					\t-V, --versión Da la versión del programa.\n\
					\t-o Prefijo de los archivos de salida.\n\
					Ejemplos:\n\
					\tconway 10 20 20 glider -o estado\n\
					Los archivos de salida se llamarán estado_n.pbm.\n\
					Si no se da un prefijo para los archivos de salida,\n\
					el prefijo será el nombre del archivo de entrada.\n";

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/

//convierte string a numero
unsigned int get_num(char* str){
	if(str[0]=='0' && strlen(str)==1) return 0;
	for(int i = 0; i < strlen(str)-1;i++){
		if(!isdigit(str[i]))return -1;
	}
	int num = atoi(str);
	if (num==0) return -1;
	return num;
}

//verifica los parámetros de entrada del programa
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
    if (argc == 5 || argc == 7) {
		int i = get_num(argv[1]);
		int m = get_num(argv[2]);
		int n = get_num(argv[3]);
		
		int numbers_ok =  i > 0 && m > 0 && n > 0;
		int prefix_needed = argc == 7;

		if ((prefix_needed && !strcmp(argv[5], OUT_PREFIX)) || !prefix_needed){
			if (numbers_ok) {
				fprintf(stdout, "%s\n", "Ejecutando juego...\n");
				return 0;
			}			
		}
        fprintf(stderr, "%s\n", "Error: Parametros incorrectos. \
        						Pruebe convay -h para ver ejemplo");
        return -1;
    }

    fprintf(stderr, "%s\n", "Error: Numero de parametros incorrecto.");
    return -1;
}

//agrega una linea del archivo a la matriz
int add_values(char* line,size_t len, matrix_t* matrix_a ){
	const char *space = " ";
	char *token;
	int num;
	int cont = 0;
	unsigned int pos[2];
	int r;
	
	token = strtok(line, space);
	
	while( token != NULL ) {
		num = get_num(token);
		if(num == -1 || cont >= 2){
			fprintf(stderr, "%s\n", "Error: Archivo de entrada invalido");
			return -1;
		}
		pos[cont] = num;
		cont++;
		token = strtok(NULL, space);
	}
	if(cont != 2){
		fprintf(stderr, "%s\n", "Error: Archivo de entrada invalido");
		return -1;
	}
	r = add_value(matrix_a, pos);
	if (r){
		fprintf(stderr, "%s\n", "La matriz no tiene el tamaño adecuado");
		return 1;
	}
	return 0;
}

//lee el archivo y agrega los valores a la matriz usando add_values
int init_matrix(matrix_t* matrix_a,FILE * input_file){
	
	int r;
	char* line = NULL;
	size_t size = 0;
	
	size_t len = getline(&line, &size, input_file);
	while(len != -1){
		r = add_values(line,len,matrix_a);
		if(r != 0){
			free((void*)line);
			return -1;;
		}
		len = getline(&line, &size, input_file);
	}
	free((void*)line);
	return 0;
}

/* *****************************************************************
 *                    FUNCIONES PRINCIPALES
 * *****************************************************************/

//realiza el loop principal del juego
int run(unsigned int i, unsigned int m, unsigned int n ,
		FILE * input_file, char* output_prefix){
	
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
	
	size_t prefix_len = strlen(output_prefix);
	for (int j = 0; j < i; j++){
		/*
		Obtengo el nombre del archivo de salida:
		[output_prefix]_[j].pbm
		*/
		char filename[50] = {0};
		char num[4] = {0};
		sprintf(num, "%03d", j+1);
		strcpy(filename, output_prefix);
		strcpy(&filename[prefix_len], "_");
		strcpy(&filename[prefix_len+1], num);
		strcpy(&filename[prefix_len+1+3], ".pbm");

		//Creo el archivo
		FILE* output = fopen(filename, "w+");

		//Hago la iteracion del juego
		r = iterate_matrix(matrix_a);
		if (r) return -1;

		//Imprimo matriz
		fprintf(stdout, "Grabando %s...", filename);
		fflush(stdout);
		r = print_matrix(output, matrix_a);
		if (r) return -1;
		fprintf(stdout, "OK\n");

		//Guardo y cierro archivo
		fflush(output);
		fclose(output);
	}
	
	destroy_matrix(matrix_a);
	return 0;
}

/*
 * realiza las comprobaciones iniciales y lanza el juego usando
 * las funciones anteriores
 */
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
    
    unsigned int i = get_num(argv[1]);
	unsigned int m = get_num(argv[2]);
	unsigned int n = get_num(argv[3]);
    
	if (argc == 7){
		r = run(i, m, n, input_file, argv[6]);
	} else {
		r = run(i, m, n, input_file, argv[4]);
	}

    if (r < 0) {
		fprintf(stderr, "Error, Ejecucion fallida de convay\n");
        exit(-r);
    }

    fclose(input_file);
    return 0;
}

