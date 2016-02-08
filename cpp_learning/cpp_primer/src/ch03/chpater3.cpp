#include <iostream>
#include <string>

using namespace std;

void stdString() {
  string buf;

  // getline(cin, buf);
  // cin >> buf;

  // string tmp;
  // while(cin >> tmp)
  //{
  //    if(!tmp.empty())
  //    {
  //        buf += tmp + ' ';
  //    }
  //}

  // cout << buf;

  // string buf1;
  // string buf2;

  // cin >> buf1;
  // cin >> buf2;

  // if(buf1 == buf2)
  //{
  //    cout << buf1;
  //}
  // else if(buf1 > buf2)
  //{
  //    cout << buf1;
  //}
  // else
  //{
  //    cout << buf2;
  //}

  string str = "maichao";

  for (char &c : str) {
    c = 'X';
  }
}

int main() { stdString(); }
