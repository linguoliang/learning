#include "part3.h"

using namespace std;

struct Complex
{
    // If std::mutex is used in following 3 functions,
    // there will be a deadlock when calling both().
    // Because the lock is already locked when mul() is invoked.
    // By default, a thread cannot acquire the same mutex twice.
    recursive_mutex m;
    int i;

    Complex() : i(0) {}

    void mul(int x)
    {
        lock_guard<recursive_mutex> lock(m);
        i *= x;
    }

    void div(int x)
    {
        lock_guard<recursive_mutex> lock(m);
        i /= x;
    }

    void both(int x, int y)
    {
        lock_guard<recursive_mutex> lock(m);
        mul(x);
        div(y);
    }
};

timed_mutex timed_mutex1;

void work()
{
    chrono::microseconds timeout(100);

    while(true)
    {
        if(timed_mutex1.try_lock_for(timeout))
        {
            cout << this_thread::get_id() << ": do work with the mutex" << endl;

            chrono::microseconds sleepDuration(2500);
            this_thread::sleep_for(sleepDuration);

            timed_mutex1.unlock();

            this_thread::sleep_for(sleepDuration);
        }
        else
        {
            cout << this_thread::get_id() << ": do work without mutex" << endl;

            chrono::milliseconds sleepDuration(100);
            this_thread::sleep_for(sleepDuration);
        }
    }
}

once_flag flag;

void do_something()
{
    call_once(flag, []()
    {
        cout << "Called once" << endl;
    });

    chrono::seconds sleepDuration(3);
    this_thread::sleep_for(sleepDuration);

    cout << "Called each time" << endl;
}

struct BoundedBuffer
{
    int *buffer;
    int capacity;

    int front;
    int rear;
    int count;

    mutex lock;

    condition_variable not_full;
    condition_variable not_empty;

    BoundedBuffer(int capacity) : capacity(capacity), front(0), rear(0), count(0)
    {
        buffer = new int[capacity];
    }

    ~BoundedBuffer()
    {
        delete[] buffer;
    }

    void deposit(int data)
    {
        unique_lock<mutex> l(lock);

        // The second argument is a predicate.
        // The predicate must return false when the waiting must be continued.
        // (it is equivalent to while(!pred()){cv.wait(l);})
        //
        // Here the predicate means that
        // waiting stopped when count != capacity returns false.
        not_full.wait(l, [this]()
        {
            return count != capacity;
        });

        buffer[rear] = data;
        rear = (rear + 1) % capacity;
        ++count;

        not_empty.notify_one();
    }

    int fetch()
    {
        unique_lock<mutex> l(lock);

        not_empty.wait(l, [this]()
        {
            return count != 0;
        });

        int result = buffer[front];
        front = (front + 1) % capacity;
        --count;

        not_full.notify_one();

        return result;
    }
};

void consumer(int id, BoundedBuffer& buffer)
{
    for(int i = 0; i < 50; ++i)
    {
        int value = buffer.fetch();
        cout << "Consumer " << id << " fetched " << value << endl;
        this_thread::sleep_for(chrono::milliseconds(250));
    }
}

void producer(int id, BoundedBuffer& buffer)
{
    for(int i = 0; i < 75; ++i)
    {
        buffer.deposit(i);
        cout << "Produced " << id << " produced " << i << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void part3()
{
    Complex complex;
    complex.both(32, 23);

    //thread t1(work);
    //thread t2(work);

    //t1.join();
    //t2.join();

    //thread t1(do_something);
    //thread t2(do_something);
    //thread t3(do_something);
    //thread t4(do_something);

    //t1.join();
    //t2.join();
    //t3.join();
    //t4.join();

    BoundedBuffer buffer(200);

    thread c1(consumer, 0, ref(buffer));
    thread c2(consumer, 1, ref(buffer));
    thread c3(consumer, 2, ref(buffer));
    thread p1(producer, 0, ref(buffer));
    thread p2(producer, 1, ref(buffer));

    c1.join();
    c2.join();
    c3.join();
    p1.join();
    p2.join();

}
