#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

using std::boolalpha;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::is_literal_type;
using std::ostream;
using std::string;
using std::vector;

struct Sales_data {
  // won't work for `const Sales_data data`.
  // Sales_data() = default;
  Sales_data() {}

  string book_no_;
  unsigned units_sold_ = 0;
  double revenue_;

  inline string ibsn() const { return book_no_; }

  void combine(const Sales_data &data) {
    units_sold_ += data.units_sold_;
    revenue_ += data.revenue_;
  }
};

istream &read(istream &, Sales_data &data);
ostream &print(ostream &, const Sales_data &data);

class Person {
  friend istream &read(istream &, Person &p);
  friend ostream &print(ostream &, const Person &p);
  friend class P1;

 public:
  Person() = default;
  string getName() const { return name_; }
  string getAdress() const { return adress_; }

 private:
  string name_;
  string adress_;
};

class P1 {
 public:
  P1() = default;

 private:
  string a = p.name_;
  Person p;
};

class C1 {
 public:
  C1() = default;
  mutable int a = 0;
  void f(int i) const { a += i; }
};

istream &read(istream &, Person &p);
ostream &print(ostream &, const Person &p);

istream &read(istream &in, Sales_data &data) {
  return in >> data.book_no_ >> data.units_sold_ >> data.revenue_;
}

ostream &print(ostream &os, const Sales_data &data) {
  return os << data.book_no_ << " " << data.units_sold_ << " " << data.revenue_;
}

istream &read(istream &, Person &p) {
  cin >> p.name_ >> p.adress_;
  return cin;
}

ostream &print(ostream &, const Person &p) {
  cout << p.name_ << " " << p.adress_;
  return cout;
}

class Screen {
 public:
  typedef string::size_type pos;
  Screen() = default;
  Screen(pos ht, pos wd, pos num)
      : height_(ht), width_(wd), contents_(num, ' ') {}
  Screen(pos ht, pos wd, char c)
      : height_(ht), width_(wd), contents_(ht * wd, c) {}
  char get() const { return contents_[cursor_]; }
  char get(pos ht, pos wd) const;
  Screen &set(char c) {
    contents_[cursor_] = c;
    return *this;
  }
  Screen &set(pos r, pos c, char ch) {
    contents_[r * width_ + c] = ch;
    return *this;
  }
  Screen &move(pos r, pos c);
  Screen &display(ostream &os) {
    do_display(os);
    return *this;
  }
  const Screen &display(ostream &os) const {
    do_display(os);
    return *this;
  }

 private:
  void do_display(ostream &os) const { os << contents_; }

  pos cursor_ = 0;
  pos height_ = 0, width_ = 0;
  string contents_;
};

inline char Screen::get(pos r, pos c) const {
  pos row = r * width_;
  return contents_[row + c];
}

inline Screen &Screen::move(pos r, pos c) {
  pos row = r * width_;
  cursor_ = row + c;
  return *this;
}

// declaration is necessary here.
class Y;

class X {
 public:
  X() = default;
  Y *py;
};

class Y {
 public:
  Y() = default;
  X x;
};

typedef double Money;
string bal;
class Acc {
 public:
  Money balance() { return bal; }

 private:
  Money bal;
};

class NoDefault {
 public:
  NoDefault(int a) : a_(a) {}

 private:
  int a_;
};

class C {
 public:
  // 以下两种方式均可
  C() : nodef(NoDefault(1)) {}
  // C() : nodef(1) {}

 private:
  NoDefault nodef;
};

class D {
 public:
  D() = default;
  D(const string &a) : a_(a) {}

  string a_;
  int b_ = 1;
};

void printD(const D &d) { cout << d.a_ << " " << d.b_ << endl; }

class Debug {
 public:
  constexpr Debug(bool r = true) : rt(r), io(r), other(r) {}
  Debug(bool r, bool i, bool o) : rt(r), io(i), other(o) {}
  constexpr bool any() { return rt || io || other; }

 private:
  bool rt;
  bool io;
  bool other;
};

class D2 {
 public:
  constexpr D2() : d(false), da(0) {}
  // 错误，未使用d的constexpr构造函数
  // constexpr D2() : d(false, false, true), da(0) {}

 private:
  Debug d;
  int da;
};

class Aggre {
 public:
  int i;
  char c;
  double d;
};

// 不是常量表达式
// int sc = 20;

// 两种都ok
// const int sc = 20;
constexpr int sc = 20;

class S {
 public:
  S() = default;
  // 若无constexpr，则必须在类外面定义并初始化
  // static int a = 0;
  static int a;
  static constexpr int b = 10;

  // static constexpr int c = sc;
  static constexpr int c = sc;
  static const int d = 10;

  static vector<double> vec;
};

int S::a = 1;
// 下面func调用使用了S::c，故必须有此定义
constexpr int S::c;
vector<double> S::vec(c);

void func(const int &ci) {}

int main(int argc, char *argv[]) {
  // Sales_data total;
  // if (read(cin, total)) {
  // Sales_data trans;
  // while (read(cin, trans)) {
  // if (total.ibsn() == trans.ibsn()) {
  // total.combine(trans);
  // } else {
  // print(cout, total);
  // total = trans;
  // }
  // }
  // print(cout, total) << endl;
  // } else {
  // cerr << "No data" << endl;
  // }

  // const Sales_data t1;
  // t1.ibsn();

  // P1 p1;

  // C1 c;
  // cout << c.a << endl;
  // c.f(1);
  // cout << c.a << endl;

  // const C1 cc = c;
  // cout << c.a << endl;
  // ++c.a;
  // cout << c.a << endl;

  // Screen ms(5, 5, 'X');
  // ms.move(4, 0).set('#').display(cout);
  // cout << "\n";
  // ms.display(cout);
  // cout << "\n";

  // C c;

  // string d("d");
  // printD(d);

  Aggre aggre = {1};
  cout << aggre.i << " " << aggre.c << " " << aggre.d;

  // D2 d2;
  // cout << boolalpha << is_literal_type<D2>::value;

  // func(S::c);

  return 0;
}
