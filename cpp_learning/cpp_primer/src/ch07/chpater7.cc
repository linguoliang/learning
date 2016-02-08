#include <iostream>
#include <string>

using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::string;

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
  Screen &move(pos r, pos c);

 private:
  pos cursor_ = 0;
  pos height_ = 0, width_ = 0;
  string contents_;
};

inline char Screen::get(pos ht, pos wd) const {
  pos row = r * width_;
  return contents_[row + c];
}

inline Screen &Screen::move(pos r, pos c) {
  pos row = r * width_;
  cursor_ = row + c;
  return *this;
}

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

  const Sales_data t1;
  t1.ibsn();

  C1 c;
  cout << c.a << endl;
  c.f(1);
  cout << c.a << endl;

  const C1 cc = c;
  cout << c.a << endl;
  ++c.a;
  cout << c.a << endl;
  return 0;
}
