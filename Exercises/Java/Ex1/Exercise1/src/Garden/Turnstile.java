package Garden;

public class Turnstile implements Runnable
{
    private Counters classCounters;
    boolean bool_turnstileRuning = true;

    public Turnstile(Counters classCounters)
    {
        /* Create class counter for each Garden.Turnstile */
        this.classCounters = new Counters();
        this.classCounters.init_counter();
    }

    public void accessGates()
    {
        classCounters.gen_counter();
        System.out.println("Access... " + classCounters.get_counter());
    }

    @Override
    public void run()
    {
        while(this.bool_turnstileRuning)
        {
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
            if(this.classCounters.get_counter() < 10)
            {
                accessGates();
            }
            else
            {
                this.bool_turnstileRuning = false;
            }
        }
    }
}
