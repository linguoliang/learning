[programming language 编程语言, scala]

# Notes of Scala For The Impatient 2

# 控制结构和函数

# if/else

if/else表达式有值，这个值是跟在if或else之后的表达式的值。类型是两个分支的公共超类型。

如果else部分缺失，`if (x > 0) 1`，则等同于`if (x > 0) 1 else ()`。其中`()`是Unit类，用于handle前面的if语句没有输出的情况，可以看作void。

# 语句终止

行尾不需要分号。

如果要在单行内写下多个语句，就需要用分号吧他们隔开。

长语句分两行时，第一行应该以一个不能做语句结尾的符号结尾。

# 块表达式和赋值

块语句：`{ //... }`，其中包含多个表达式，最后一个表达式的字就是块的值。

赋值操作返回Unit类型的值。

# 输入和输出

使用print或println，后者会追加一个换行符。

可用C风格的printf函数来格式化输出。

可用readLine函数从控制台读取一行输入，该函数带一个参数作为提示字符串。其他读取输入的方法还有，readInt、readDouble等，但无参数。

# 循环