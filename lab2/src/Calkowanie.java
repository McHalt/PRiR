import java.beans.Expression;
import java.util.Scanner;

public class Calkowanie {
    public static void main(String[] args) throws InterruptedException {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Podaj n: ");
        int n = scanner.nextInt();
        scanner.nextLine();
        System.out.println("Podaj lewy koniec przedzialu calkowania: ");
        double a = scanner.nextDouble();
        System.out.println("Podaj prawy koniec przedzialu calkowania: ");
        double b = scanner.nextDouble();
        double trapezami = 0,prostokatami = 0;
        double h = (b-a)/n;
        M_trapezow[] trapezy = new M_trapezow[n];
        M_prostokatow[] prostokaty = new M_prostokatow[n];
        for(int i = 0; i < n; i++) {
            trapezy[i] = new M_trapezow(a + (i/(double)n)*(b-a), a + ((i+1)/(double)n)*(b-a));
            prostokaty[i] = new M_prostokatow(a + i * h);
            trapezy[i].start();
            prostokaty[i].start();
            trapezy[i].join();
            prostokaty[i].join();
            trapezami += trapezy[i].getWynik() * h;
            prostokatami += prostokaty[i].getWynik()*h;
        }
        prostokatami += fx(a + n * h) * h;
        M_Simpsona[] parabole = new M_Simpsona[n];
        double simpsonem = 0, hS = 0;
        double x0, x1;
        for(int i = 0; i < n; i++) {
            x0 = a+(i*(b-a))/n;
            x1 = a+((i+1)*(b-a))/n;
            simpsonem += 4 * fx((x1 + x0)/2);
            if(i == 0) {
                hS = (x1 - x0)/2;
            }
            parabole[i] = new M_Simpsona(x0, x1);
            parabole[i].start();
            parabole[i].join();
            simpsonem += parabole[i].getWynik();
        }
        simpsonem *= hS/3;
        System.out.println("Trapezami wyszlo: "+ trapezami + ", w przyblizeniu: " + (Math.round(trapezami * 100.0)/100.0));
        System.out.println("Prostokatami wyszlo: "+ prostokatami + ", w przyblizeniu: " + (Math.round(prostokatami * 100.0)/100.0));
        System.out.println("Simpsonem wyszlo: " + simpsonem + ", w przyblizeniu: " + (Math.round(simpsonem * 100.0)/100.0));
    }

    public static double fx(double x) {
        return (3*x*x)+(2*x)+1;
    }
}
