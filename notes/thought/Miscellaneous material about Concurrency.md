@(thought)[data structures and algorithms 数据结构和算法]

# Miscellaneous material about Concurrency

# Cuckoo hashing

Cuckoo hashing是Rasmus Pagh, Flemming Friche Rodler在2001年提出的，在hash table中用于解决hash collision的一种方法，是一种开放寻址法的hash table。

Cuckoo hashing维护了两个hash table，$T_1$和$T_2$，使用两个hash function，$h_1$和$h_2$。每个key存储在$T_1$的$h_1(x)$或者$T_2$的$h_2(x)$，但不会同时存储在两个地方。

由于使用了两个hash table，Cuckoo hashing保证了在最坏情况下，lookup和delete也能有$O(1)$的时间，insert的期望时间是$O(1)$。

原始的cuckoo hashing并不支持并发读写，同时对于每个inset和lookup需要多个内存引用。Bin Fan, David G. Andersen, Michael Kaminsky在2013年提出了Concurrent Cuckoo hashing，用optimistic version，使得cuckoo hashing在保证原有空间高效性的情况下，支持多个reader和一个writer的并发访问；同时使用了针对每个key的short summary，提高了hash table操作中cache的局部性；还优化了insert操作，提高了吞吐率。

## Reference

1. Rasmus Pagh, Flemming Friche Rodler. Cuckoo Hashing[J]. Algorithms, 2001, 51(2).
2. Bin Fan, David G. Andersen, Michael Kaminsky. MemC3: Compact and Concurrent MemCache with Dumber Caching and Smarter Hashing[C]. Networked Systems Design and Implementation, 2013: 371-384.
3. Xiaozhou Li, David G. Andersen, Michael Kaminsky, Michael J. Freedman. Algorithmic improvements for fast concurrent Cuckoo hashing[C]. Proceedings of the Ninth European Conference on Computer Systems, 2014, 27.

# Hopscotch hashing

Hopscotch hashing是Maurice Herlihy, Nir Shavit, Moran Tzafrir在2008年提出的，在hash table中用于解决hash collision的一种方法，是一种开放寻址法的hash table，结合了linear探测、链式hash和cuckoo hash的优点。

它使用了一个hash function，$h$和hopscotch方法。hash table的每个项都包含一个hop-information，一个$H$-bit的一个bitmap（$H$是常数，通常是一个word），被hash到table里的每个item，x总会在$h(x)$或者下$H-1$个位置被找到。

它的insert，remove和contains的期望时间都是常数时间。

Hopscotch hashing在设计之初就考虑到了并发，使用了lock和time stamp的方式来保证了并发安全性。

## Reference

1. Maurice Herlihy, Nir Shavit, Moran Tzafrir. Hopscotch Hashing[C]. Proceedings of the 22nd international symposium on Distributed Computing, 2008: 350-364.

# spinlock

spinlock是一种同步机制，它会导致线程进入忙等待，不断检查锁是否可用，并尝试获取锁。

它避免了操作系统进行调度时的开销。

由于spinlock是忙等待，因此在多处理器上使用才有意义。spinlock在锁可能耽搁一小段时间的情况下，很高效。因为这个原因，操作系统的内核中经常使用spinlock。

## Reference

1. Maurice Herlihy, Nir Shavit. The Art of Multiprocessor Programming Revised Reprint [M]. Elsevier, 2012.

# rwlock

Readers-writer lock是一种同步原语。在访问共享对象时，对于仅有reader的情况，是完全不需要同步的，但如果有writer，就需要同步。当一个wirter范围共享数据的时候，其他所有的writer和reader都会被阻塞，直到这个writer结束访问。

在共享数据更新很少，读取很多的情况下，Readers-writer lock会拥有很高的效率。

## Reference

1. Maurice Herlihy, Nir Shavit. The Art of Multiprocessor Programming Revised Reprint [M]. Elsevier, 2012.

# RCU

RCU是一种同步机制，在Linux内核中有广泛的用途，Linux内核2.5.43版本就开始使用RCU，截至2014年，已经使用了超过9000个RCU API。它允许reader和writer并发的访问共享数据，支持一个writer和多个reader之间的并发。通过维护多个版本的数据，RCU保证了reader读取到的数据的一致性，还保证在reader完成读取前，被访问的数据不会被释放。

RCU有3个基本机制，用于insert的Publish-Subscribe机制、用于delete的Wait For Pre-Existing RCU Readers to Complete机制和允许reader容忍并发insert和delete的Maintain Multiple Versions of Recently Updated Objects机制。

## Reference

1. Paul E. McKenney, John D. Slingwine. Read-Copy Update: Using Execution History to Solve Concurrency Problems[C]. Parallel and Distributed Computing and Systems, 1998: 509–518.
2. Paul E. McKenney, Jonathan Walpole. Introducing technology into the Linux kernel: a case study[C]. Special Interest Group on Operating Systems, 2008, 42(5): 4–17.

# CPU with HTM from Intel and IBM

## Intel

Transactional Synchronization Extensions（TSX）是x86架构指令集的扩展，这个扩展加入了Hardware Transactional Memory（HTM）的支持。

在2013年6月，Intel推出了基于Haswell微架构的处理器。Haswell处理器成为了主流处理器中首次引入Transactional Memory的处理器，在这一系列的处理器中，型号低于45xx，R系列和K系列的不支持TSX。

## IBM

### Power8

IBM在2013年8月的Hot Chips会议上推出了Power8。Power8是基于Power架构的超标量体系结构对称多处理器家族。Power8加入了Hardware Transactional Memory的支持。

### Blue Gene

Blue Gene是IBM的一个项目，目标是设计计算速度能够达到PFLOPS级别的，同时低能耗的超级计算机。这个项目产生了3代的超级计算机，Blue Gene/L，Blue Gene/P和Blue Gene/Q。其中Blue Gene/Q支持Transactional Memory。