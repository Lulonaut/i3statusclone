#ifndef BLOCK_H__
#define BLOCK_H__

typedef struct {
    char *label;
    char *command;
    long long delay;
    char *current_output;
    long long last_update;

} Block;


Block update_block(Block block, long long time, int force);

#endif //BLOCK_H__
