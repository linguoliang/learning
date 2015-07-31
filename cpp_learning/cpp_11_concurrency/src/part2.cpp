#include "part2.h"

using namespace std;

struct Counter
{
    mutex mutex1;

    int value;

    Counter() :value(0) {}

    void increment()
    {
        ++value;
    }

    void decrement()
    {
        if(value == 0)
        {
            throw "Value cannot be less than 0";
        }

        --value;
    }
};

struct CouncurrentCounter
{
    mutex mutex1;

    Counter counter;

    int value()
    {
        return counter.value;
    }

    void increment()
    {
        mutex1.lock();
        counter.increment();
        mutex1.unlock();
    }

    // Won't work in some cases because unlock() isn't called
    // when an exception is throwed. Then the program is blocked.
    //void decrement()
    //{
    //    mutex1.lock();
    //    counter.decrement();
    //    mutex1.unlock();
    //}

    void decrement()
    {
        mutex1.lock();

        try
        {
            counter.decrement();
        }
        catch(string e)
        {
            mutex1.unlock();
            throw e;
        }

        mutex1.unlock();
    }
};

// Comparing with decrement() in CouncurrentCounter, decrement() here is much more convenient
// and easy to maintain.
struct ConcurrentSafeCounter
{
    mutex m;

    Counter counter;

    int value()
    {
        return counter.value;
    }

    void increment()
    {
        // When you want to protect a whole block of code
        // (a function in our case, but can be inside a loop or another control structure),
        // it exists a good solution to avoid forgetting to release the lock: std::lock_guard.
        //
        // This class is a simple smart manager for a lock. When the std::lock_guard is created,
        // it automatically calls lock() on the mutex. When the guard gets destructed,
        // it also releases the lock.
        lock_guard<mutex> guard(m);
        counter.increment();
    }

    void decrement()
    {
        lock_guard<mutex> guard(m);
        counter.decrement();
    }
};

void part2()
{
    ConcurrentSafeCounter counter;

    vector<thread> threads;

    for(int i = 0; i < 10; i++)
    {
        threads.push_back(thread([&counter]()
        {
            for(int i = 0; i < 5000; i++)
            {
                counter.increment();
            }
        }));
    }

    for(auto& thread : threads)
    {
        thread.join();
    }

    cout << counter.value() << endl;
}
