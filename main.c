#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <locale.h>
#include "block.h"
#include "config.h"


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
    int j = 0;
    struct timeval te;
    while (1) {
        gettimeofday(&te, NULL);
        j += 1;
        long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;

        int size = (sizeof(blocks) / sizeof(blocks[0]));
        for (int i = 0; i < size; i++) {
            blocks[i] = update_block(blocks[i], milliseconds, 0);
        }

        if (size == 1) {
            printf(",[{\"full_text\":\"%s\"}]", blocks[0].current_output);
        } else {

        }

        printf("\n");
        fflush(stdout);
        sleep(1);
        if (j > 10000) {
            break;
        }
    }

    return 0;
}