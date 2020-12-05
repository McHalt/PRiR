public class M_Simpsona  extends Thread{
    private double a,b;
    private double wynik;

    public M_Simpsona(double a, double b) {
        this.a = a;
        this.b = b;
    }
    public void run() {
        wynik = Calkowanie.fx(a) + Calkowanie.fx(b);
    }
    public double getWynik() {
        return wynik;
    }
}
