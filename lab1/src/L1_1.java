public class L1_1 {
    public static void main(String[] args) throws Exception
    {
        Watek w1 = new Watek("a", 1);
        Watek w2 = new Watek("b", 1);
        Watek w3 = new Watek("c", 1);
        Watek w4 = new Watek("d", 1);

        w1.start();
        w2.start();
        w3.start();
        w4.start();

        System.out.println("ostatnia linijka kodu");
    }
}
