#pragma once

#include "obj.h"

#include <iostream>

using std::cout;
using std::endl;

void Test1();
void Test2();

class Parent
{
public:
  int iparent;
  Parent() :iparent(10) {}
  virtual void f() { cout << "Parent::f()" << endl; }
  virtual void g() { cout << "Parent::g()" << endl; }
  virtual void h() { cout << "Parent::h()" << endl; }
};

class Child : public Parent {
public:
  int ichild;
  Child() :ichild(100) {}
  virtual void f() { cout << "Child::f()" << endl; }
  virtual void g_child() { cout << "Child::g_child()" << endl; }
  virtual void h_child() { cout << "Child::h_child()" << endl; }
};

class GrandChild : public Child {
public:
  int igrandchild;
  GrandChild() :igrandchild(1000) {}
  virtual void f() { cout << "GrandChild::f()" << endl; }
  virtual void g_child() { cout << "GrandChild::g_child()" << endl; }
  virtual void h_grandchild() { cout << "GrandChild::h_grandchild()" << endl; }
};

class Base1 {
public:
  int ibase1;
  Base1() :ibase1(10) {}
  virtual void f() { cout << "Base1::f()" << endl; }
  virtual void g() { cout << "Base1::g()" << endl; }
  virtual void h() { cout << "Base1::h()" << endl; }

};

class Base2 {
public:
  int ibase2;
  Base2() :ibase2(20) {}
  virtual void f() { cout << "Base2::f()" << endl; }
  virtual void g() { cout << "Base2::g()" << endl; }
  virtual void h() { cout << "Base2::h()" << endl; }
};

class Base3 {
public:
  int ibase3;
  Base3() :ibase3(30) {}
  virtual void f() { cout << "Base3::f()" << endl; }
  virtual void g() { cout << "Base3::g()" << endl; }
  virtual void h() { cout << "Base3::h()" << endl; }
};

class Derive : public Base1, public Base2, public Base3 {
public:
  int iderive;
  Derive() :iderive(100) {}
  virtual void f() { cout << "Derive::f()" << endl; }
  virtual void g1() { cout << "Derive::g1()" << endl; }
};

void Obj() {
  Test1();
  Test2();
}

void Test1() {
  cout << endl << "Test1" << endl;

  GrandChild gc;

  for (int i = 0; i < 6; ++i) {
    void(*pf)(void) = (void(*)(void))(((int*)*(int*)&gc)[i]);
    pf();
  }
}

void Test2() {
  cout << endl << "Test2" << endl;

  Derive d;
  ((void(*)(void))(((int*)(*(int*)&d))[0]))();
  ((void(*)(void))(((int*)(*(int*)&d))[1]))();
  ((void(*)(void))(((int*)(*(int*)&d))[2]))();
  ((void(*)(void))(((int*)(*(int*)&d))[3]))();

  int s = sizeof(Base1) / 4;
  ((void(*)(void))((int*)(((int*)&d)[s]))[0])();
  ((void(*)(void))((int*)(((int*)&d)[s]))[1])();
  ((void(*)(void))((int*)(((int*)&d)[s]))[2])();

  s += sizeof(Base2) / 4;
  ((void(*)(void))((int*)(((int*)&d)[s]))[0])();
  ((void(*)(void))((int*)(((int*)&d)[s]))[1])();
  ((void(*)(void))((int*)(((int*)&d)[s]))[2])();
}