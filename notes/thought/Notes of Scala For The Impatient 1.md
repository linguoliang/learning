@(@action inbox)[programming language 编程语言, scala]

# Notes of Scala For The Impatient 1

# 基础

## 声明值和变量

`val`：声明常量。
`var`：声明变量。

不需要指定值或变量的类型，类型可以从表达式中推导出来。

如果需要指定类型，则使用类似`val greeting: String = null`的语句。

Scala中，变量或函数的类型总是写在变量或函数的后面。

当同一行中有多个语句的时候，`;`才需要。

## 常用类型

Scala有7种数值类型：`Byte`，`Char`，`Short`，`Int`，`Long`，`Float`和`Double`。

这些类型都是classes，在Scala中基本类型和类类型之间并没有区别。

`RichByte`，`RichChar`，`RichShort`等是上述数值类型的“扩展”，支持更多的的操作。`1.to(10)`，`1`首先会转换为`RichInt`，然后对转换的得到的值用`to`。

`BigInt`和`BigDecimal`支持任意（有限）位数的数字，基于`java.math.BigInteger`和`java.math.BigDecimal`，但比它们更方便。

在Scala中，*使用methods*，而不是casts，来在不同数值类型之间*做转换*。

## 操作符

操作符实际上都是方法。

```scala
a + b

a.+(b)
```

## 函数和方法

Scala没有静态方法。

不带参数的Scala方法通常不使用圆括号。