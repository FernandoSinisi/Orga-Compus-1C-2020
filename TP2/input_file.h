#ifndef CACHE_INPUT_FILE_H
#define CACHE_INPUT_FILE_H

#include <stdio.h>
#include <stdint.h>
#include "memory.h"

#define READ_CMD 1000
#define WRITE_CMD 2000
#define FLUSH_CMD 3000
#define MR_CMD 4000
#define CMD_LEN 3

typedef struct{
    FILE* file;
    uint32_t current_cmd[CMD_LEN];
} input_file_t;

void input_file_init(input_file_t* this, char* filename);
int input_file_read_command(input_file_t* this);
int input_file_execute_command(input_file_t* this, memory_t* memory);
int input_file_destroy(input_file_t* this);

#endif //CACHE_INPUT_FILE_H
