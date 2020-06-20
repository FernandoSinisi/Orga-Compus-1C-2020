#include "utils.h"

//verifica los parámetros de entrada del programa
int verify_argv(int argc, char *argv[]) {
    if (argc == 2) {
        fprintf(stdout, "Nombre del archivo: %s\n", argv[1]);
        return 0;
    }

    fprintf(stderr, "%s\n", "Error: Numero de parametros incorrecto.");
    return -1;
}
