#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include "block.h"

Block update_block(Block block, long long time) {
    if (block.last_update + block.delay < time) {
        block.last_update = time;
        char *line = (char *) malloc(1000 * sizeof(*line));
        fprintf(stderr, "COMMAND: %s\n", block.command);
        FILE *output = popen(block.command, "r");
        if (output == NULL) {
            block.current_output = "ERROR";
            return block;
        }
        fgets(line, 1000, output);
        pclose(output);
        strtok(line, "\n");
        fprintf(stderr, "RESULT: %s\n", line);
        block.current_output = line;
    }
    return block;
}