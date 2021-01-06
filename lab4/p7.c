#include <stdio.h>
#include <sys/types.h>
int main() {
    int i = 0, j = 0, ret;
    ret = fork();
    if (ret == 0) {
        for (i = 0; i < 500000; i++) {
            printf("Proces potomny: %d\n", i);
            printf("Proces potomny zakonczony\n");
        }
    } else {
        wait(0);
        printf("Proces macierzysty wznawia prace.\n");
        for (j = 0; j < 500000; j++) {
            printf("Proces macierzysty: %d\n", j);
        }
    }
    return 0;
}