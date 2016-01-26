#include <iostream>

using std::hex;
using std::cin;
using std::cout;
using std::endl;

class Base {
 public:
  virtual void f() { cout << "Base::f" << endl; }

  virtual void g() { cout << "Base::g" << endl; }

  virtual void h() { cout << "Base::h" << endl; }
};

class Derived : public Base {
 public:
  void f() { cout << "Derived::f" << endl; }
  virtual void f1() { cout << "Derived::f1" << endl; }

  virtual void g1() { cout << "Derived::g1" << endl; }

  virtual void h1() { cout << "Derived::h1" << endl; }
};

int main() {
  // Base b;

  // cout << sizeof(int) << " " << sizeof(int*) << endl;
  // cout << "address of vfptr:" << &b << endl;
  // cout << "address of vftable:" << *(long*)(&b) << endl;
  // cout << "address of the first function in vftable:" << (int*)(*(long*)(&b))
  // << endl;

  // void (*pf)(void) = (void (*)(void)) * (int*)(*(int*)(&b));
  // pf = (void (*)(void)) * (int*)(*(int*)(&b));
  // pf();
  // return 0;

  int a[10];

  decltype(a) b;

  return 0;
}
