#include "memory.h"
#include "input_file.h"
#include "utils.h"


int main(int argc, char** argv){
    int r;
    memory_t* memory = malloc(sizeof(memory_t));
    if (!memory) {
        //TODO CAMBIAR POR console_log_error
        fprintf(stderr, "Error: no se pudo crear la memoria.\n");
        return -1;
    }

    r = verify_argv(argc,argv);
    if (r != 0) {
        return r;
    }

    input_file_t file;
    r = input_file_init(&file, argv[1]);
    if (r != 0) {
        return r;
    }

    r = memory_init(memory);
    if(r == 0){
        while(input_file_read_command(&file) == 0){
            input_file_execute_command(&file, memory);
        }
    }

    input_file_destroy(&file);
    memory_destroy(memory);
    return 0;
}