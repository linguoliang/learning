#ifndef PHILOSOPHER1_H_
#define PHILOSOPHER1_H_

#include <condition_variable>
#include <mutex>
#include <thread>
#include <vector>

enum State { kEating, kThinking };

class Philosopher1 {
 public:
  explicit Philosopher1(int id, int max_iter, std::vector<State> &philosophers,
                        std::vector<std::condition_variable> &cvs,
                        std::mutex &table_lock);
  ~Philosopher1();
  Philosopher1(const Philosopher1 &) = delete;
  Philosopher1(Philosopher1 &&) = default;
  Philosopher1 &operator=(const Philosopher1 &) = delete;

  void run();

 private:
  std::vector<State>::size_type id_;
  size_t max_iter_;
  std::vector<State> &philosophers_;
  std::vector<std::condition_variable> &cvs_;
  std::mutex &table_lock_;
  std::thread thread_;

  bool IsGoodToEat_();
  void GetChopsticks_();
  void PutChopsticks_();
  void Eat_();
};

#endif
