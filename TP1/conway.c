#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


#define _POSIX_C_SOURCE 200809L
#define OPT_HELP "-h"
#define OPT_VERSION "-V"
#define OUT_PREFIX "-o"

const char VERSION[] = "Version 1.0\n";

const char HELP[] = "Uso:\n\tconway -h\n\tconway -V\n\tconway i M N inputfile [-o outputprefix]\nOpciones:\n\t-h, --help Imprime este mensaje.\n\t-V, --versión Da la versión del programa.\n\t-o Prefijo de los archivos de salida.\nEjemplos:\n\tconway 10 20 20 glider -o estado\nLos archivos de salida se llamarán estado_n.pbm.\nSi no se da un prefijo para los archivos de salida,\nel prefijo será el nombre del archivo de entrada.\n";

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
    char *ptr;
    if (argc == 7) {
        if (!strcmp(argv[5], OUT_PREFIX) && strtol(argv[1], &ptr, 10) && strtol(argv[2], &ptr, 10) && strtol(argv[3], &ptr, 10)) {
            fprintf(stdout, "%s\n", "Aca ejecutaria juego\n");
            return 0;
        }
        fprintf(stderr, "%s\n", "Error: Parametros incorrectos. Pruebe convay -h para ver ejemplo");
        return -1;

    }

    fprintf(stderr, "%s\n", "Error: Numero de parametros incorrecto.");
    return -1;
}


int main(int argc, char *argv[]) {

    int r = verify_argv(argc, argv);
    if (r > 0) {
        return 0;
    } else if (r < 0) {
        return -r;
    }

    FILE *input_file = stdin;
    
    //r = run(input_file);


    if (r < 0) {
        exit(-r);
    }

    fclose(input_file);
    return 0;
}

