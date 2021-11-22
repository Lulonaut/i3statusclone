#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <locale.h>
#include "block.h"
#include "config.h"


#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

int main() {
    setlocale(LC_ALL, "");

    //change delay to ms and update all blocks
    for (int i = 0; i < 1; i++) {
        blocks[i].delay = blocks[i].delay * 1000;
        blocks[i].last_update = 0;
        blocks[i].current_output = "placeholder";
    }

    printf("{\"version\":1}\n");
    printf("[[]");
    fflush(stdout);
    struct timeval te;
    while (1) {
        gettimeofday(&te, NULL);
        long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;

        int size = (sizeof(blocks) / sizeof(blocks[0]));
        Block new_block;
        for (int i = 0; i < size; i++) {
            new_block = update_block(blocks[i], milliseconds);
            blocks[i] = new_block;
        }

        if (size == 1) {
            printf(",[{\"full_text\":\"%s%s\"}]", blocks[0].label, blocks[0].current_output);
        } else {
            //begin array
            printf(",[");
            for (int i = 0; i < size; ++i) {
                //last run, omit "," and end array
                if (i == size - 1) {
                    printf("{\"full_text\":\"%s%s\"}]", blocks[i].label, blocks[i].current_output);
                } else {
                    printf("{\"full_text\":\"%s%s\"},", blocks[i].label, blocks[i].current_output);
                }
            }
        }

        printf("\n");
        fflush(stdout);
        sleep(1);
    }
    //unreachable
}

#pragma clang diagnostic pop