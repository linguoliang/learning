#include <array>
#include <deque>
#include <forward_list>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

void t1() { list<deque<int>> ldeq; }

// 不能是这样的const，因为无法进行++操作
// bool find(const vector<int>::const_iterator begin, ...
bool find1(vector<int>::const_iterator begin, vector<int>::const_iterator end,
           int val) {
  while (begin != end) {
    if (*begin == val) {
      return true;
    }
    ++begin;
  }
  return false;
}

// simpler, but only c++14
// auto find2(vector<int>::const_iterator begin, vector<int>::const_iterator
// end, int val) {
vector<int>::const_iterator find2(vector<int>::const_iterator begin,
                                  vector<int>::const_iterator end, int val) {
  while (begin != end) {
    if (*begin == val) {
      return begin;
    }
    ++begin;
  }
  return end;
}

void t2() {
  vector<int> va{1, 2, 3, 4, 5, 6, 7};
  cout << boolalpha << find1(va.cbegin(), va.cend(), 6) << endl
       << (find2(va.begin(), va.end(), 5) == va.end() ? false : true) << endl
       << (find2(va.begin(), va.end(), 50) == va.end() ? false : true) << endl;
}

void t3() {
  vector<int>::size_type index;
  vector<int>::value_type ia;

  const list<int> ss{1, 2, 3, 4, 5};
  list<int>::const_iterator it = ss.begin();

  vector<int> v1;
  const vector<int> v2;
  // 以下代码错误，it1与it2类型不同，无法位于同一条语句
  // auto it1 = v2.begin(), it2 = v1.begin();
  // auto it3 = v1.cbegin(), it4 = v2.cbegin();
  auto it1 = v1.begin();
  auto it2 = v2.begin(), it3 = v1.cbegin(), it4 = v2.cbegin();

  int a1 = 0;
  const int a2 = 0;
  // 问题类似上面的
  // 此时底层const保留
  // auto *pa1 = &a1, *pa2 = &a2;
  // const auto *pa1 = &a1, *pa2 = &a2;
  const auto *const pa1 = &a1, *pa2 = &a2;
}

void t4() {
  class A {
   public:
    // A() = default;
    A(int a, int b) : a_(a), b_(b) {}
    int a_ = 0;
    int b_ = 0;
  };

  // 必须提供A的默认构造函数
  // vector<A> as(10);

  vector<A> as(10, {1, 2});
  // vector<A> as(10, A(1, 2));

  A a{1, 3};
}

int main(int argc, char *argv[]) {
  // t1();
  // t2();
  // t3();
  t4();
  return 0;
}
