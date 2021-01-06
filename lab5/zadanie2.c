#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>

double calc(int n) {
    double res = 0;
    for (int i = 1; i < n; i++) {
        res += pow(-1, i - 1) / (2 * i - 1);
    }
    return 4 * res;
}

void forkF(int p) {
    if (p > 0) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("ERROR!!! pid < 0");
        } else if (pid == 0) {
            srand(time(NULL) * getpid());
            int n = 100 + rand() % 4900;
            printf("Dla n = %d wartosc pi jest rowna %f\n", n, calc(n));
        } else {
            forkF(p - 1);
        }
    }
}

int main() {
    forkF(10);
    return 0;
}