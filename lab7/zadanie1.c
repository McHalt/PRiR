#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <mpi.h>

/*
 * Symulator sklepu w dobie COVID-19
 */

#define SKLEP 1
#define ULICA 2
#define ZAWAL 3
#define SZPITAL 4
#define KOSTNICA 5
int liczbaProcesow;
int nrProcesu;
int liczbaKlientow;
int liczbaMiejsc = 4;
int liczbaZajetychMiejsc = 0;
int t = 1;
int a = 1, b = 0;
int wyslij[2];
int odbierz[2];
MPI_Status mpi_status;

void Wyslij(int nrKlienta, int stan) {
    wyslij[0] = nrKlienta;
    wyslij[1] = stan;
    MPI_Send(&wyslij, 2, MPI_INT, 0, t, MPI_COMM_WORLD);
    sleep(1);
}

void Sklep(int liczbaProcesow) {
    int nrKlienta, status;
    liczbaKlientow = liczbaProcesow - 1;
    printf("Witamy w sklepie!\n");
    printf("Ze wzgledu na sytuacje pandemiczna, w sklepie moze przebywac maksymalnie %d osob\n", liczbaMiejsc);
    sleep(2);
    while (liczbaMiejsc <= liczbaKlientow) {
        MPI_Recv(&odbierz, 2, MPI_INT, MPI_ANY_SOURCE, t, MPI_COMM_WORLD, &mpi_status);
        nrKlienta = odbierz[0];
        status = odbierz[1];
        switch (status) {
            case 1:
                printf("Klient %d jest w sklepie\n", nrKlienta);
                break;
            case 2:
                printf("Klient %d jest na ulicy\n", nrKlienta);
                liczbaZajetychMiejsc--;
                break;
            case 3:
                printf("Klient %d jest ratowany\n", nrKlienta);
                break;
            case 4:
                liczbaZajetychMiejsc--;
                break;
            case 5:
                liczbaKlientow--;
                liczbaZajetychMiejsc--;
                printf("Ilosc klientow %d\n", liczbaKlientow);
                break;
        }
    }
    printf("Program zakonczyl dzialanie");
}

void Klient() {
    int stan, r, i;
    stan = ULICA;
    while (1) {
        switch (stan) {
            case SKLEP:
                r = rand() % 20;
                if (r == rand() % 20) {
                    printf("Klient nr %d dostal zawalu i jest ratowany\n", nrProcesu);
                    stan = ZAWAL;
                } else if (r > 10) {
                    printf("Klient nr %d wychodzi ze sklepu\n", nrProcesu);
                    stan = ULICA;
                }
                break;
            case ULICA:
                if (rand() % 2 == 1 && liczbaMiejsc > liczbaZajetychMiejsc) {
                    printf("Klient nr %d wchodzi do sklepu\n", nrProcesu);
                    stan = SKLEP;
                }
                break;
            case ZAWAL:
                r = rand() % 3;
                if (r == 0) {
                    printf("Klient nr %d zmarl\n", nrProcesu);
                    stan = KOSTNICA;
                    liczbaKlientow--;
                } else if (r == 1) {
                    printf("Klient nr %d jest transportowany do szpitala\n", nrProcesu);
                    stan = SZPITAL;
                } else {
                    printf("Klient nr %d jest nadal ratowany\n", nrProcesu);
                }
                break;
            case SZPITAL:
                if (rand() % 20 == rand() % 20) {
                    printf("Klient nr %d wydobrzal i wychodzi ze szpitala\n", nrProcesu);
                    stan = ULICA;
                }
                break;
            case KOSTNICA:
                return;
        }
        Wyslij(nrProcesu, stan);
    }
}

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &nrProcesu);
    MPI_Comm_size(MPI_COMM_WORLD, &liczbaProcesow);
    srand(time(NULL));
    nrProcesu == 0 ? Sklep(liczbaProcesow) : Klient();
    MPI_Finalize();
    return 0;
}