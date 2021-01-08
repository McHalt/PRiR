#include <stdio.h>
#include <mpi.h>

#define t 1
#define N 1000
#define CUTOFF 300

/*
 * Fraktal Mandelbrota
 */
int main(int argc, char *argv[]) {
    int p, liczbaProcesow;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &p);
    MPI_Comm_size(MPI_COMM_WORLD, &liczbaProcesow);
    MPI_Status status;

    int arr[N][N];
    if ((p > 0) && (p <= liczbaProcesow - 1)) {
        if (p != liczbaProcesow - 1) {
            MPI_Recv(&arr, N * N, MPI_INT, p + 1, t, MPI_COMM_WORLD, &status);
        }
        int begin = (N / liczbaProcesow) * p;
        int end = (N / liczbaProcesow) * (p + 1);
        for (int i = begin; i < end; i++) {
            for (int j = 0; j < N; j++) {
                double cr = (4.0 * i - 2 * N) / N;
                double ci = (4.0 * j - 2 * N) / N;
                double zr = cr, zi = ci;

                int k = 0;
                while (k < CUTOFF && zr * zr + zi * zi < 4.0) {
                    double temp0 = cr + zr * zr - zi * zi;
                    double temp1 = ci + 2 * zr * zi;
                    zr = temp0;
                    zi = temp1;
                    k++;
                }
                arr[i][j] = k;
            }
        }
        MPI_Send(&arr, N * N, MPI_INT, p - 1, t, MPI_COMM_WORLD);
    } else if (p == 0) {
        MPI_Recv(&arr, N * N, MPI_INT, p + 1, t, MPI_COMM_WORLD, &status);
        FILE *pgmimg;
        pgmimg = fopen("fraktal.ppm", "wb");
        fprintf(pgmimg, "P3\n");
        fprintf(pgmimg, "%d %d\n", N, N);
        fprintf(pgmimg, "255\n");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                fprintf(pgmimg, "0 %d 0 ", (arr[i][j] / CUTOFF) * 255);
            }
            fprintf(pgmimg, "\n");
        }
        fclose(pgmimg);
    }
    MPI_Finalize();
    return 0;
}