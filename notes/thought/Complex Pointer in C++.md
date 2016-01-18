@(thought)[c/c++, programming language 编程语言]

# `char *(*(**foo[][8])())[]`...

# declaration

one **basic type** + zero or more **derived types**

## basic type

`char`, `signed char`, `unsigned char`, `short`, `unsigned short`, `int`, `unsigned int`, `long`, `unsigned long`, `float`, `double`, `void`, `struct tag   `, `union tag`, `enum tag`, `long long`, `unsigned long long`, `long double`

## derived types

`*`: pointer to ...   - always on the left side
`[]`: array of ...   - always on the left side
`()`: function returning ...   - always on the left side

# operator precedence

The `[]` and `()` have higher precedence than `*`.

## the rule to read declaration

There is a ["right-left" rule](http://ieng9.ucsd.edu/~cs30x/rt_lt.rule.html). I think the rule is based on the precedence.

[C pointer to array/array of pointers disambiguation](http://stackoverflow.com/questions/859634/c-pointer-to-array-array-of-pointers-disambiguation) also mentioned *"go right when you can, go left when you must"*.

## find error in declaration

Since we can read complex declaration by applying the rule mentioned before, we also can find error in declaration with the knowledge of what is legal in C.

Some illegal declarations,

```c
// array of functions?
// error: 'a' declared as array of functions of type 'int ()'
int a[]();

// a function returning function?
// error: function cannot return function type 'int ()'
int b()();

// array of functions?
// a function returning array of int?
// error: function cannot return array type 'int []'
// error: 'c' declared as array of functions of type 'int ()'
int c[]()[];

// array of functions?
// error: 'd' declared as array of functions of type 'int ()'
int (*d)[]();
```

# `char *(*(**foo[][8])())[]`

foo is array of array of 8 pointer to pointer to function returning pointer to array of pointer to char.

# summary

1. The key is the ["right-left" rule](http://ieng9.ucsd.edu/~cs30x/rt_lt.rule.html).
2. Be aware of what is legal in C.
3. 数组指针，指针数组。。。Well, the Chinese description is really ambiguous.

# references

1. [Reading C type declarations](http://unixwiz.net/techtips/reading-cdecl.html)
2. [The "right-left" rule](http://ieng9.ucsd.edu/~cs30x/rt_lt.rule.html)
3. [C pointer to array/array of pointers disambiguation](http://stackoverflow.com/questions/859634/c-pointer-to-array-array-of-pointers-disambiguation)