public class M_prostokatow  extends Thread{
    private double a;
    private double wynik;

    public M_prostokatow(double a) {
        this.a = a;
    }
    public void run() {
        this.wynik = Calkowanie.fx(a);
    }
    public double getWynik() {
        return wynik;
    }
}