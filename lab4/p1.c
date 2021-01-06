main() {
    int wynik = 0;
    if(execl("/bin/date", "date", 0) == 1) {
        perror("/bin/date");
        wynik = 1;
    } else {
        printf("Ta linia nigdty nie zostanie wyswietlona! \n");
    }
    exit(wynik);
}