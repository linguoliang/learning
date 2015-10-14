#include "ch1.h"

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <vector>

#include "philosopher1.h"

using std::chrono::milliseconds;
using std::condition_variable;
using std::cout;
using std::defer_lock;
using std::endl;
using std::lock;
using std::mutex;
using std::this_thread::yield;
using std::this_thread::sleep_for;
using std::thread;
using std::unique_lock;
using std::vector;

void philosopher1();
void philosopher2();
void philosopher3();

void ch1() { philosopher3(); }

void philosopher1() {
  vector<State> philosophers(5);
  vector<condition_variable> cvs(5);
  mutex table_lock;

  vector<Philosopher1> phs;

  for (int i = 0; i != 5; ++i) {
    // move the object here
    phs.push_back(Philosopher1(i, 30, philosophers, cvs, table_lock));
  }

  for (auto& ph : phs) {
    ph.run();
  }
}

void philosopher2() {
  vector<State> philosophers(5, kThinking);
  vector<condition_variable> cvs(5);
  mutex table_lock;

  auto get_chopsticks = [&](size_t id) {
    unique_lock<mutex> lg(table_lock);
    cvs[id].wait(lg, [&]() {
      if (philosophers[id] == kThinking &&
          philosophers[(id - 1) % 5] != kEating &&
          philosophers[(id + 1) % 5] != kEating) {
        return true;
      } else {
        return false;
      }
    });
    philosophers[id] = kEating;
  };

  auto put_chopsticks = [&](size_t id) {
    unique_lock<mutex> lg(table_lock);
    philosophers[id] = kThinking;
    cvs[(id - 1) % 5].notify_one();
    cvs[(id + 1) % 5].notify_one();
  };

  auto eat = [&](size_t id) {
    for (size_t i = 0; i != 10; ++i) {
      get_chopsticks(id);
      cout << i << " philosopher " << id << " is eating." << endl;
      yield();
      put_chopsticks(id);
      cout << i << " philosopher " << id << " is thingking." << endl;
    }
  };

  vector<thread> phs;
  for (int i = 0; i != 5; ++i) {
    phs.push_back(thread(eat, i));
  }

  for (auto& p : phs) {
    p.join();
  }
}

void philosopher3() {
  vector<mutex*> chopsticks;

  for (int i = 0; i != 5; ++i) {
    chopsticks.push_back(new mutex());
  }

  auto eat = [&](size_t id) {
    unique_lock<mutex> left(*chopsticks[id], defer_lock);
    unique_lock<mutex> right(*chopsticks[(id + 1) % 5], defer_lock);

    auto get_chopsticks = [&]() { lock(left, right); };

    auto put_chopsticks = [&]() {
      left.unlock();
      right.unlock();
    };

    for (int i = 0; i != 10; ++i) {
      cout << i << " philosopher " << id << " is thingking." << endl;

      sleep_for(milliseconds(10));

      get_chopsticks();

      cout << i << " philosopher " << id << " is eating." << endl;

      sleep_for(milliseconds(5));

      put_chopsticks();
    }
  };

  vector<thread> phs;
  for (int i = 0; i != 5; ++i) {
    phs.push_back(thread(eat, i));
  }

  for (auto& p : phs) {
    p.join();
  }
}
