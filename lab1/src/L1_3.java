public class L1_3 {
    public static void main(String[] args)
    {
        ThreadM tm = new ThreadM();
        tm.start();
        ThreadN tn = new ThreadN();
        tn.start();
        try
        {
            tm.join();
            tn.join();
            System.out.println("Watki zakonczone");
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
    }
}
