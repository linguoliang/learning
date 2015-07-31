#include "part4.h"

using namespace std;

struct AtomicCounter
{
    // The C++11 Concurrency Library introduces
    // Atomic Types as a template class: std::atomic.
    // You can use any Type you want with that template
    // and the operations on that variable will be
    // atomic and so thread-safe.
    // It has to be taken into account that it is up to
    // the library implementation to choose
    // which syncronization mechanism is used
    // to make the operations on that type atomic.
    // On standard platforms for integral types like int, long, float, ...
    // it will be some lock-free technique.
    // If you want to make a big type (let's saw 2MB storage),
    // you can use std::atomic as well, but mutexes will be used.
    // In this case, there will be no performance advantage.
    // 
    // std::atomic is specialized for all integral types.
    std::atomic<int> value;

    void increment()
    {
        ++value;
    }

    void decrement()
    {
        --value;
    }

    int get()
    {
        return value.load();
    }
};

void part4()
{
    AtomicCounter counter;

    vector<thread> threads;
    for(int i = 0; i < 10; ++i)
    {
        threads.push_back(thread([&counter]()
        {
            for(int i = 0; i < 500; ++i)
            {
                counter.increment();
            }
        }));
    }

    for(auto& thread : threads)
    {
        thread.join();
    }

    cout << counter.get() << endl;
}