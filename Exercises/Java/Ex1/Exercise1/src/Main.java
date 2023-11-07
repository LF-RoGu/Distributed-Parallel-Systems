import Garden.Counters;
import Garden.Turnstile;

public class Main
{
    public static void main(String[] args)
    {
        Counters classCounter = new Counters();
        Turnstile classTurnstile = new Turnstile(classCounter);

        Thread west = new Thread(new Turnstile(classCounter));
        Thread east = new Thread(new Turnstile(classCounter));

        west.start();
        east.start();
        try
        {
            west.join();
            east.join();
        }
        catch (InterruptedException e)
        {
            e.printStackTrace();
        }
    }
}