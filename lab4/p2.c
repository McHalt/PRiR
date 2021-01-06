main() {
    if(fork() != 0) {
        printf("Jestem rodzicem, moj pid = %d \n", getpid());
    } else {
        printf("Ja potomek, moj pid = %d \n", getpid());
        printf("pid mojego rodzica = %d \n", getppid());
    }
}