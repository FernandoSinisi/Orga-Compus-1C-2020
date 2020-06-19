#include "memory.h"
#include "input_file.h"

int main(int argc, char** argv){
    memory_t memory;
    memory_init(&memory);

    input_file_t file;
    input_file_init(&file, argv[1]);

    while(input_file_read_command(&file) == 0){
        input_file_execute_command(&file, &memory);
    }

    input_file_destroy(&file);
    memory_destroy(&memory);
    return 0;
}