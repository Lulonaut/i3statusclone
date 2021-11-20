#include "block.h"
#include "stdio.h"
#include "string.h"

Block update_block(Block block, long long time, int force) {
    if (block.last_update + block.delay < time || force == 1) {
        block.last_update = time;
        char line[100000];
        FILE *output = popen(block.command, "r");
        if (output == NULL) {
            block.current_output = "ERROR";
            return block;
        }
        fgets(line, 100000, output);
        pclose(output);
        fprintf(stderr, "\nLine:%s\n", line);
        strtok(line, "\n");
        block.current_output = line;
    }
    return block;
}