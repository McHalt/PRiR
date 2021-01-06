#include <stdio.h>
#include <sys/types.h>
int main() {
    printf("Proces ID: %d\n", getpid());
    printf("Proces macierzysty ID: %d\n", getppid());
    sleep(10);
    printf("Ubudzilem sie.\n");
    return 0;
}