# C++ 初始化

# 列表初始化（list initialization）

注：对于内置类型的变量，如果使用列表初始化且初始化存在丢失信息的风险，则编译器将报错。
```cpp
double d = 3.14;
int i{d}; // 错误
```

# 默认初始化（default initialization）

如果定义变量时没有指定初值，则变量被默认初始化，具体值由变量类型决定。对象被默认初始化时自动执行默认构造函数。

## 何时发生

* 当在块作用域中不使用任何初始值定义一个非静态变量或者数组时；
    ```cpp
    int main() {
      int a;
      double b[10];
    }
    ```
* 当一个类本身含有类类型的成员且使用合成的默认构造函数时；
    ```cpp
    class A {
     public:
      int a;
    };
    class B {
     public:
      A a;
    };
    ```
* 当类类型的成员没有在构造函数初始值列表中显示地初始化时。 
    ```cpp
    class A {
     public:
      A(int a) : a_(a) {}
     private:
      int a_;
      int b_;
    };
    ```

# 值初始化

对于内置类型，则元素初始值自动设为0；如果是类类型，则由类来默认初始化。

## 何时发生

* 在数组初始化时，提供的初始值的数量少于数组的大小；
    ```cpp
    int arr[5] = {1, 2, 3}; // a[] = {1, 2, 3, 0, 0}
    ```
* 不使用初始值定义一个局部静态变量时；
    ```cpp
    int func() {
      static int s; // s值为0
      return 0;
    }
    ```
* 使用`T()`来显示地请求值初始化时;
* 使用列表初始化来初始化聚合类，列表中元素数量少于类的成员数量时，后续成员被值初始化。
```cpp
class Aggre {
 public:
  int i;
  double d;
  char c;
}

Aggre aggre = {1} // d和c都是0
```

# References

1. [C++值初始化，默认初始化，以及其他初始化类型的区别](https://www.zhihu.com/question/36735960)