#include "utils.h"
#include "log.h"

//verifica los parámetros de entrada del programa
int verify_argv(int argc, char *argv[]) {
    if (argc == 2) {
        console_log("File name: %s", argv[1]);
        return 0;
    }

    console_log_error("Invalid parameters, found %d parameters but 1 is required", argc - 1);
    return -1;
}
