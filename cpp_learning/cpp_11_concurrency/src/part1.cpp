#include "part1.h"

using namespace std;

void hello()
{
    cout << "Hello from thread " << this_thread::get_id() << endl;
}

void part1()
{
    vector<thread> threads;

    for(int i = 0; i < 5; ++i)
    {
        threads.push_back(std::thread(hello));
    }

    for(auto& thread : threads)
    {
        thread.join();
    }
}
