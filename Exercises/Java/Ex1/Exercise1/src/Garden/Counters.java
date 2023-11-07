package Garden;

public class Counters
{
    private int int_counter;
    private static final Object set_mutex = new Object();
    private static final Object get_mutex = new Object();

    public void init_counter()
    {
        this.int_counter = 0;
    }
    public void gen_counter()
    {
        synchronized (set_mutex)
        {
            this.int_counter++;
        }
    }

    public int get_counter()
    {
        synchronized (get_mutex)
        {
            return this.int_counter;
        }
    }
}
