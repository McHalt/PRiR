package lab3;

import java.util.Random;

/*
 * Symulator sklepu w dobie COVID-19
 */
public class Main {
    static int liczbaMiejscWSklepie = 10;
    static int liczbaKlientow = 12;

    public static void main(String[] args) {
        Sklep sklep = new Sklep(liczbaMiejscWSklepie, liczbaKlientow);
        int i = 0;
        while (i++ <= liczbaKlientow) {
            new Klient(i, sklep).start();
        }
    }
}

class Sklep {
    static int SKLEP = 1;
    static int ULICA = 2;

    private int liczbaMiejscWSklepie;
    private int iloscMiejscZajetych;
    private int liczbaKlientow;

    public Sklep(int liczbaMiejscWSklepie, int liczbaKlientow) {
        this.liczbaMiejscWSklepie = liczbaMiejscWSklepie;
        this.liczbaKlientow = liczbaKlientow;
        iloscMiejscZajetych = 0;
    }

    public synchronized int wejdz(int nr) {
        try {
            Thread.sleep(1000);
        }
        catch(InterruptedException e) {}
        iloscMiejscZajetych++;
        if (iloscMiejscZajetych < liczbaMiejscWSklepie) {
            System.out.println("Klient nr " + nr + " wchodzi do sklepu");
            return SKLEP;
        }
        return ULICA;
    }

    public synchronized int wyjdz(int nr) {
        iloscMiejscZajetych--;
        System.out.println("Klient o numerze " + nr + " wychodzi ze sklepu");
        return ULICA;
    }
}

class Klient extends Thread {
    static int SKLEP = 1;
    static int ULICA = 2;

    private int nr;
    private int stan;
    private Sklep sklep;
    Random rand;

    public Klient(int nr, Sklep sklep) {
        this.nr = nr;
        this.sklep = sklep;
        this.stan = ULICA;
        this.rand = new Random();
    }

    @Override
    public void run() {
        Random r = new Random();
        while (true) {
            if (stan == SKLEP) {
                if (rand.nextInt(2) == 1) {
                    stan = sklep.wyjdz(nr);
                }
            } else if (stan == ULICA) {
                if (rand.nextInt(2) == 1) {
                    stan = sklep.wejdz(nr);
                }
            }
            try {
                sleep(Math.abs(r.nextInt()%900+100));
            } catch (InterruptedException ignored) {}
        }
    }
}