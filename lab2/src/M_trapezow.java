public class M_trapezow extends Thread{
    private double a, b;
    private double wynik;

    public M_trapezow(double a, double b) {
        this.a = a;
        this.b = b;
    }

    public void run() {
        this.wynik = (Calkowanie.fx(a) + Calkowanie.fx(b))/2;
    }

    public double getWynik() {
        return wynik;
    }
}