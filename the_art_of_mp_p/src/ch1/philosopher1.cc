#include "philosopher1.h"

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

using std::condition_variable;
using std::cout;
using std::endl;
using std::mutex;
using std::stringstream;
using std::this_thread::yield;
using std::thread;
using std::unique_lock;
using std::vector;

Philosopher1::Philosopher1(int id, int max_iter, vector<State>& philosophers,
                           vector<condition_variable>& cvs, mutex& table_lock)
    : id_(static_cast<vector<State>::size_type>(id)),
      max_iter_(static_cast<size_t>(max_iter)),
      philosophers_(philosophers),
      cvs_(cvs),
      table_lock_(table_lock) {}

Philosopher1::~Philosopher1() {
  if (thread_.joinable()) {
    thread_.join();
  }
}

void Philosopher1::run() {
  thread_ = thread(&Philosopher1::Eat_, this);
  thread_.join();
}

bool Philosopher1::IsGoodToEat_() {
  if (philosophers_[id_] == kThinking &&
      philosophers_[(id_ - 1) % 5] != kEating &&
      philosophers_[(id_ + 1) % 5] != kEating) {
    return true;
  } else {
    return false;
  }
}

void Philosopher1::GetChopsticks_() {
  unique_lock<mutex> lg(table_lock_);
  // cvs_[id_].wait(lg, &Philosopher1::IsGoodToEat_);
  cvs_[id_].wait(lg, [this]() { return IsGoodToEat_(); });
  philosophers_[id_] = kEating;
}

void Philosopher1::PutChopsticks_() {
  unique_lock<mutex> lg(table_lock_);
  philosophers_[id_] = kThinking;
  cvs_[(id_ - 1) % 5].notify_one();
  cvs_[(id_ + 1) % 5].notify_one();
}

void Philosopher1::Eat_() {
  cout << "test in new thread" << endl;
  // for (size_t i = 0; i < max_iter_; ++i) {
  // GetChopsticks_();
  // cout << "philosopher " << id_ << "is eating." << endl;
  // yield();
  // PutChopsticks_();
  // cout << "philosopher " << id_ << "is thingking." << endl;
  // }
}
