#include <stdio.h>
#include <sys/types.h>
#include <time.h>

double fx(double x) {
    return (4 * x) - (6 * x) + 5;
}

double calc(double a, double b, int count) {
    double res = (fx(a) / 2) + (fx(b) / 2);
    for (double i = 1; i < count; i++) {
        res += fx(a + (i / count) * (b - a));
    }
    res *= (b - a) / count;
    return res;
}

int forkF(int p) {
    if (p > 0) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
        } else if (pid == 0) {
            srand(time(NULL) ^ getpid());
            double a = rand() % 100;
            double b = a + rand() % 100;
            int trapezy = rand() % 100;
            printf("Proces %d a = %.1f, b = %.1f, liczba trapezow = %d, wynik = %f\n", p, a, b, trapezy,
                   calc(a, b, trapezy));
        } else {
            forkF(p - 1);
        }
    }
}

int main() {
    forkF(10);
}

