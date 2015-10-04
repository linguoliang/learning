//
// Created by chaomai on 6/1/15.
//

#ifndef CHPATER5_H
#define CHPATER5_H

#include <string>
#include <atomic>
#include <iostream>
#include <thread>
#include <mutex>
#include <cassert>
#include <assert.h>

#include "utils.h"

void chpater5();

class spinlock_mutex {
  std::atomic_flag flag;

 public:
  spinlock_mutex() : flag(ATOMIC_FLAG_INIT) {}

  void lock() {
    while (flag.test_and_set(std::memory_order_acquire))
      ;
  }

  void unlock() { flag.clear(std::memory_order_release); }
};

#endif
