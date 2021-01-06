#include <mpi.h>
#include <stdio.h>

float fx(float x) {
    return x*x;
}

int main(int argc, char **argv) {
    int i = 1, p, n, t1 = 50, t2 = 60, t3 = 70;
    float h, res, a = 1, b = 5;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &p);
    MPI_Comm_size(MPI_COMM_WORLD, &n);
    MPI_Status status;
    if (p == n -1) {
        h = (float)(b-a)/n;
        res = (fx(a)+fx(b))/2.0;
        MPI_Send(&h, 1, MPI_FLOAT, p-1, t1, MPI_COMM_WORLD);
        MPI_Send(&res, 1, MPI_FLOAT, p-1, t2, MPI_COMM_WORLD);
        MPI_Send(&i, 1, MPI_INT, p-1, t3, MPI_COMM_WORLD);
    } else if( p > 0 && p < n-1) {
        MPI_Recv(&h,1, MPI_FLOAT, p+1, t1, MPI_COMM_WORLD, &status);
        MPI_Recv(&res, 1, MPI_FLOAT, p+1, t2, MPI_COMM_WORLD, &status);
        MPI_Recv(&i, 1, MPI_INT, p+1, t3, MPI_COMM_WORLD, &status);
        res += fx(a+i++*h);
        MPI_Send(&h, 1, MPI_FLOAT, p-1, t1, MPI_COMM_WORLD);
        MPI_Send(&res, 1, MPI_FLOAT, p-1, t2, MPI_COMM_WORLD);
        MPI_Send(&i, 1, MPI_INT, p-1, t3, MPI_COMM_WORLD);
    } else if(p == 0) {
        MPI_Recv(&h, 1, MPI_FLOAT, p+1, t1, MPI_COMM_WORLD, &status);
        MPI_Recv(&res, 1, MPI_FLOAT, p+1, t2, MPI_COMM_WORLD, &status);
        MPI_Recv(&i, 1, MPI_INT, p-1, t3, MPI_COMM_WORLD, &status);
        res += fx(a+i*h)*h;
        printf("Wynik calkowania x*x przy przedziale <%f,%f> i %d trapezow to %f\n", a, b, n, res);
    }
    MPI_Finalize();
    return 0;
}