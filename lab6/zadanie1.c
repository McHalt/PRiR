#include <mpi.h>
#include <math.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int p, n, t = 50;
    double pi = 4, sum = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &p);
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Status status;
    if (p == 0) {
        MPI_Send(&sum, 1, MPI_DOUBLE, p + 1, t, MPI_COMM_WORLD);
    } else if (p > 0 && p <= n - 1) {
        MPI_Recv(&sum, 1, MPI_DOUBLE, p - 1, t, MPI_COMM_WORLD, &status);
        sum += pow(-1, p - 1) / (2 * p - 1);
        printf("Numer procesu: %d; suma: %f\n", p, sum);
        if (p == n - 1) {
            sum += pow(-1, p - 1) / (2 * p - 1);
            pi *= sum;
            printf("Liczba pi to ~%f\n", pi);
        } else {
            MPI_Send(&sum, 1, MPI_DOUBLE, p + 1, t, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
    return 0;
}