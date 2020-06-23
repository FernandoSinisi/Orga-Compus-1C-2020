#include <string.h>
#include "input_file.h"
#include "log.h"

#define MAX_LINE_SIZE 14
#define MAX_CMD_LEN 6

int input_file_init(input_file_t *this, char *filename) {
    this->file = fopen(filename, "r");
    if (!this->file) {
        console_log_error("Could not open file: %s", filename);
        return -1;
    }
    return 0;
}

int parse_command(input_file_t *this, char *line) {
    char cmd[MAX_CMD_LEN];
    int arg1 = -1;
    int arg2 = -1;
    int r = sscanf(line, "%s %d, %d", cmd, &arg1, &arg2);

    if (r == EOF) {
        console_log_error("Could not parse command: %s", cmd);
        return 1;
    }

    if (strncmp(cmd, "R", 1) == 0) {
        this->current_cmd[0] = READ_CMD;
        if (arg1 < 0)
            return 1;
        this->current_cmd[1] = arg1;
    } else if (strncmp(cmd, "W", 1) == 0) {
        this->current_cmd[0] = WRITE_CMD;
        if (arg1 < 0 || arg2 < 0)
            return 1;
        this->current_cmd[1] = arg1;
        this->current_cmd[2] = arg2;
    } else if (strncmp(cmd, "FLUSH", 5) == 0) {
        this->current_cmd[0] = FLUSH_CMD;
    } else if (strncmp(cmd, "MR", 2) == 0) {
        this->current_cmd[0] = MR_CMD;
    } else {
        console_log_error("Invalid instruction: %s", cmd);
        return 1;
    }

    return 0;
}

int input_file_read_command(input_file_t *this) {
    char line[MAX_LINE_SIZE];
    char *read = fgets(line, MAX_LINE_SIZE, this->file);
    if (read == NULL)
        return 1;
    if (parse_command(this, line))
        return 1;
    return 0;
}

int input_file_execute_command(input_file_t *this, memory_t *memory) {
    float mr = 0;
    unsigned char read = 0;
    switch (this->current_cmd[0]) {
        case READ_CMD:
            console_log("Reading from address %d", this->current_cmd[1]);
            read = memory_read_byte(memory, this->current_cmd[1]);
            console_log("Data read from memory: %u", read);
            break;
        case WRITE_CMD:
            console_log("Writing %d to address %d", this->current_cmd[2], this->current_cmd[1]);
            memory_write_byte(memory, this->current_cmd[1], this->current_cmd[2]);
            break;
        case FLUSH_CMD:
            console_log("Flushing cache");
            memory_flush_cache(memory);
            break;
        case MR_CMD:
            mr = memory_get_cache_miss_rate(memory);
            console_log("Cache miss rate: %5f", mr);
            break;
        default:
            return 1;
    }
    return 0;
}

int input_file_destroy(input_file_t *this) {
    fclose(this->file);
    return 0;
}
