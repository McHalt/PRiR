#include <stdio.h>
#include <sys/types.h>
int main() {
    int ret;
    ret = fork();
    if (ret == 0) {
        //proces potomny
        printf("ID procesu potomnego %d\n", getpid());
        printf("ID procesu macierzystego: %d\n", getppid());
    } else {
        //proces macierzysty
        printf("ID procesu macierzystego %d\n", getpid());
        printf("ID procesu macierzystego macierzystego: %d\n", getppid());
    }
    sleep(2);
    return 0;
}