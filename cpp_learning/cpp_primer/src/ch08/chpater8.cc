#include <bitset>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

void printBit() {
  cout << "badbit: " << bitset<4>(cin.badbit) << endl
       << "failbit: " << bitset<4>(cin.failbit) << endl
       << "eofbit: " << bitset<4>(cin.eofbit) << endl
       << "goodbit: " << bitset<4>(cin.goodbit) << endl;
}

void printState(istream& is) {
  cout << boolalpha << "badbit: "
       << " " << is.bad() << endl
       << "failbit: "
       << " " << is.fail() << endl
       << "eofbit: "
       << " " << is.eof() << endl
       << "goodbit: "
       << " " << is.good() << endl;
  cout << cin.rdstate() << " " << bitset<4>(cin.rdstate()) << endl;
  cout << "================================" << endl;
}

void t() {
  printState(cin);
  cin.clear(cin.badbit);
  printState(cin);
  // 设置其他位时，如果不需要当前的state，不需要单独clear
  // cin.clear();
  cin.clear(cin.failbit | cin.eofbit);
  printState(cin);

  // 如需在原有基础上再设置其他位，与rdstate进行|即可
  cin.clear(cin.rdstate() | cin.badbit);
  printState(cin);
}

void t1() {
  printState(cin);
  cin.setstate(cin.badbit);
  printState(cin);
  // 设置其他位时，如果不需要当前的state，需要单独clear
  cin.clear();
  cin.setstate(cin.failbit | cin.eofbit);
  printState(cin);
  // 如需在原有基础上再设置其他位，直接set即可
  cin.setstate(cin.badbit);
  printState(cin);
}

void t2() {
  ostream* os = cin.tie();
  (*os) << "tie version 1" << endl;

  ostream* old_os = cin.tie(nullptr);
  ostream* null_os = cin.tie();
  (*old_os) << "tie version 2" << endl;
  cout << boolalpha << (old_os == &cout) << "\n" << (null_os == nullptr)
       << "\n";

  char ch;
  cin >> ch;
  cout << ch << endl;
}

void t3() {
  struct P {
    string name;
    vector<string> phones;
  };
  vector<P> ps;
  string line;
  istringstream iss;
  while (getline(cin, line)) {
    P info;
    iss.clear();
    iss.str(line);
    iss >> info.name;
    string word;
    while (iss >> word) {
      info.phones.push_back(word);
    }
  }
}

int main(int argc, char* argv[]) {
  // printBit();
  // t();
  // t1();
  // t2();
  t3();
  return 0;
}
