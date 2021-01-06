#include <stdio.h>
#include <sys/types.h>
int main() {
    int i = 0, j = 0, pid;
    pid = fork();
    if (pid == 0) {
        for (i = 0; i < 500; i++) {
            printf("Proces potomny %d\n", i);
        }
    } else {
        for (j = 0; j < 500; j++) {
            printf("Proces macierzysty: %d\n", j);
        }
    }
    return 0;
}