[concurrency 并发]

# The Art of Multiprocessor Programming 1

# Chapter 1 Introduction

## The Amdahl's Law

$$
S=\frac{1}{1-p+\frac{p}{n}}
$$

S：The *speedup* S of a job is the ratio between 一个处理器完成job的时间除以n个并发处理器完成job的时间。
p：job中，可以并行执行部分的比例。

假设一个处理器完成job的时间是1。有n个并发处理器，那么可并行执行的部分所用时间就是$p/n$，顺序执行部分所用时间是$1-p$，总的并行执行时间就是，

$$
1-p+\frac{p}{n}
$$

这个法则决定了，一个处理器完成一个job的时间，在增加n个处理器以后，时间并不是简单的变为原来的$1/n$。举个例子，10个房间，其中9个房间一样大，有个房间的大小是其他房间的2倍，有10个工人来刷漆。其中可并行的部分是$10/11$，带入公式以后，

$$
S=\frac{1}{1-\frac{10}{11}+\frac{\frac{10}{11}}{10}}=5.5
$$

可以增加到10个工人后，所用的时间其实只是1个工人的一半。

这点说明了，在系统中可能90%的代码都实现了并行，但是就是因为10%的必须要顺序执行，最后提升的效果就远不如预期。

The Amdahl's Law有这么一个重要启示，应该尽量**减少顺序执行的代码的粒度**。

# Chapter 2 Mutual Exclusion

## Critical Sections

# Chapter 4 Foundations of Shared Memory

# References
1. The Art of Multiprocessor Programming, Maurice Herlihy, Nir Shavit