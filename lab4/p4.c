#include <stdio.h>
#include <sys/types.h>
int main() {
    pid_t pid;
    printf("Przed fork\n");
    pid = fork();
    printf("Za fork\n");
    switch(pid) {
        case -1:
            printf("Blad funkcji fork()!\n");
            break;
        case 0:
            printf("Jestem procesem potomnym\n");
            getchar();
            break;
        default:
            printf("Jestem procesem macierzystym. PID potomka: %d\n", pid);
            wait(0);
            printf("Rodzic: po wait()\n");
    }
    return 0;
}