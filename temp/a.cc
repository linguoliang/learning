#include <vector>

using namespace std;

template <typename T>
class A {
 public:
  A();
  void test(T a);
  void test(typename vector<T>::size_type a);
};

template <typename T>
A<T>::A() {}

template <typename T>
void A<T>::test(T a) {}

template <typename T>
void A<T>::test(typename vector<T>::size_type a) {}

int main() { return 0; }
