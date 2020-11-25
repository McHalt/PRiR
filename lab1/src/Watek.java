public class Watek extends Thread{
    String wyraz;

    public Watek(String str, int numer)
    {
        wyraz = str;
    }

    public void run()
    {
        for(int k = 0; k < 1000000; k++)
        {
            System.out.println(k + " " + wyraz);
                /*
                try
                {
                    sleep((int) (Math.random()*1000);
                }
                catch(interruptedException e)
                {
                    e.printStackTrace();
                }
                System.out.println(wyraz + " koniec");
                 */
        }
    }
}
