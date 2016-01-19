[concurrency 并发]

# CKDTree

Concurrent KDTree with Snapshots, implemented in Java. This article is about some details in implementation.

# Basic Idea

The methods used in this structure is based on ideas in CTrie (snapshot) and Non-blocking Binary Search Trees (search, insert and delete).

* RDCSS
* GCAS
* Mark and Flag
* Leaf-oriented tree

# Details in Implementation

## Data Structure

下面是实现的时候遇到的问题和自己对一些细节的思考，有的已经在两篇论文里面有所记录，但是自己没注意，又踩坑了，还有的是这个结构的设计隐含的问题。

### Dummy Nodes

由于BST中的insert操作是需要mark parent的，因此，对于一棵空的tree（有一个root），parent并不存在，insert无法适用于这样的情况。delete也有类似的问题。

为了避免结点数目很少的时候需要考虑很多复杂的情况，BST里提到了使用两个key为$\infty_1$，$\infty_2$（其中$\infty_1 < \infty_2$）的Dummy nodes，$\infty_1 < \infty_2$这样的关系是为了保证Binary Search Trees的性质。

由于Java中，无法使用`Double.POSITIVE_INFINITY`来得到两个key，使得$\infty_1 < \infty_2$，所以就干脆不管他们的关系，root的左右child都使用`Double.POSITIVE_INFINITY`作为key。

![Alt text](./1447836297561.png)

这样一来，
1. 只有在insert第一个key或者delete最后一个key的时候需要操作leaf dummy node。
2. 除（1）以外，所有update都发生在上图三角形的sub tree里面。

### Right Child of Root

既然没有key会进入root的right child，那么为什么不把root的right child设置为`null`？

不行，这个也是在写后续代码的时候发现的。进行`helpMark1`和`helpMark2`的时候，需要判断`GCAS`处理grand parent哪边的child，

```java
if (info.p == info.gp.GCAS_READ_LEFT_CHILD(this)) {
  direction = Direction.LEFT;
} else {
  direction = Direction.RIGHT;
}
```

如果要delete的leaf是children of the left child of root，也就是说此时tree里面只有一个key。存在这么一种可能性，同时有多个thread来进行delete，其中一个thread已经成功进行了delete，其他某些的thread还没有执行上述代码。当开始执行以后，就会发现`p`不等于`gp`（即root）的left child，此时如果root的right为`null`，那么就会出错。

`helpMark1`和`helpMark2`都包含上述操作，只是仅仅`helpMark1`才会触发问题。

## Search

### `startGen` in `searchKey`

这个结构使用了Ctrie里GCAS的idea，在search的时候来update从root到leaf的path。search使用的version number是在开始进行search前从root里read的。为什么不到每个node的时候就read一次version number？

因为如果在search到某个内部的结点的时候，执行了snapshot操作，那么root的version number就变了。此时search中read root的version number，就会造成path的错误更新，上半部分是老的version number，下面有一条新的version number的分支。

### Retry after `GCAS` in `searchKey`

`searchKey`中，如果发现要前往的branch是internal node，并且version低于`startGen`，那么就需要创建那个internal node新版本的copy，然后把cur node的branch设置为那个新版的node。

接下来，首先想到的是在cur node处重试（即下面代码里的`continue;`），但是如果`continue`了，那么`gp`，`gpupdate`和`depth`就会被“提前”更新（cur没有往下走，它们却被更新了），尤其是`depth`，可能被重复的加上了`p`的`skippedDepth`。

```java
while (cur instanceof InternalNode) {
  gp = p;
  gpupdate = pupdate;
  ...
  depth += p.skippedDepth;

  if (keyCompare(key, cur.key, depth++) < 0) {
    ...
    if (left instanceof InternalNode) {
      if (left.gen != startGen) {
        ...
        return SearchRes.RESTART;
        // continue;
    ...
```

效率低些，但是更为稳妥的办法就是完全重新开始，`return SearchRes.RESTART;`。

## Delete

### Type Test in `helpMarked1`

当要delete的leaf，它的sibling是leaf时，`helpMarked1`来处理这种的情况。

在single thread的情况下，`helpDelete`在判断sibling的类型以后，如果是leaf，那么`helpMarked1`就会执行。

在multithread的情况下，某个thread看到update信息以后就直接执行`helpMarked1`，但是此时sibling的类型是不知道的。因为从update信息被发布，到`helpMarked1`被执行，sibling可能早就被其他thread改变了，如果变为internal node，

```java
Leaf<V> ns = new Leaf<>(sibling.key, ((Leaf<V>) sibling).value);
```

那么上述代码就会报错。


### Read Info after Mark

这里在实现的时候遇到了两个问题。

BST提到marked的结点是不可更改的，实现的时候没有在意，测试的时候就遇到了麻烦。

`helpDelete`（1）首先mark parent，（2）read leaf的sibling，（3）根据sibling的类型来进行后续的操作。

（1）和（2）的顺序是不能改的，这也是mark的意义所在。mark以后，`helpMarked1`和`helpMarked2`中还会再次读取sibling，并用于构造新的node，然后`GCAS` grand parent的child。如果不能保证`helpDelete`中leaf的sibling在后续的操作中不变，那么构造出的新node很可能就是错的。

### Help When Mark Failed

在看论文的证明的时候，注意到了这么几句话，

>  A process does a backtrack CAS belonging to f only after performing an unsuccessful mark CAS belonging to f *and observing that every prior mark CAS belonging to f also failed* (line 92). Hence, if some mark CAS belonging to f. ...  Thus, once the mark CAS occurs, the deletion will *not have to retry*.

上面斜体的地方是先前没有注意到的，

```java
if (info.p.CAS_UPDATE(info.pupdate, m1u)) {
  ...
} else {
  // help
  // backtrack cas
  return false;
}
```

对于同一个update信息，多个thread执行这段代码的时候，如果`p`的`update`被其他thread更新了，当前thread的backtrack cas也会执行。虽然能够保证最终完成delete，但是`helpDelete`返回的是**false**。下次重试delete的时候，会找不到要delete的k-v，并返回false。

总体来看，是正确完成了delete，但是详细的看`if`中的条件，上述情况是不符合语义的（*既然`p`的`update`，已经有正确的信息了，那执行if里的东西就好，为什么还要backtrack？*），同时也增加了额外的开销。

在`helpMarked1`也有类似的情况。

## Snapshot

### Snapshot

这里的问题是，在原始的方法里面，如果cas update成功了，那么就一定保证某个thread能够完成help，也就是完成更新。

但是如果使用gcas，在发生snapshot的时候，gcas会使得所有thread的help都无法完成，如果没有相应的处理，那么就会导致更新丢失。

### RDCSS

在进行snapshot的时候，如果仅仅是cas root，那么有可能会发生下面的情况，

![Alt text](./1449652247936.png)

因此需要保证snapshot时，root的left child不变。

### `size` in Snapshots

## Iterator

# References

1. Concurrent Tries with Efficient Non-Blocking Snapshots, Aleksandar Prokopec, Nathan G. Bronson, Phil Bagwell, Martin Odersky
2. Non-blocking Binary Search Trees, Faith Ellen, Panagiota Fatourou, Eric Ruppert, Franck van Breugel
3. A Practical Multi-Word Compare-and-Swap Operation, Timothy L. Harris, Keir Fraser, Ian A. Pratt

# CKDTree 2

这篇记录了另一种简单的方法来实现snapshot，当然简单是有代价的，那就是在snapshot的时候不允许并发的update（inset，delete）。

# Basic Idea

这里使用的方法是Trevor Brown的non-blocking binary search tree的[实现](http://www.cs.utoronto.ca/~tabrown/ksts/StaticDictionary5.java)里面提到的，并没有在论文里说明。

基本思想非常简单，

1. 读取并保存所有node；
2. 接着检查已保存的node与当前tree里的node是否都一样，发现不一样的，重新snapshot；
3. 基于已保存的node，构建一棵新的tree，返回snapshot。

这里的snapshot和上一篇中的就有很大不同。上一篇的snapshot基本上可以算作是在调用`snapshot()`的时候，tree的状态（特殊情况下需要retry）；而这里的必须保证，从第1步完成读取的时刻起，到第2步检查结束，都没有update发生，才能返回snapshot。

要注意的是，在第1和2步中，需要保存和检查所有的node（internal node和leaf）。这不同于使用GCAS的snapshot，只update internal node，在某些时刻，某些leaf实际上是共享的。

# `size` in Snapshot

这个方法里的`size并不像上一个方法，需要考虑很多问题。只需要在上述第3步完成以后，count所有leaf的数目即可。

# References

1. http://www.cs.utoronto.ca/~tabrown/ksts/StaticDictionary5.java, Trevor Brown

# CKDTree 3

这篇是实现snapshot的第3个方法，也是打算写的最后一个方法。使用的方法同样来自的Range Queries in Non-blocking k-ary Search Trees。

# Basic Idea

使用的方法同样来自Trevor Brown。在他的论文，Range Queries in Non-blocking k-ary Search Trees中，阐述了如何实现range query。

由于进行range query时，需要tree局部的一个constant view，因此snapshot是一个合适的工具。

在update操作中，这里方法比先前的方法多了一个操作：每个leaf都带有一个`dirty` field。每次进行update时，就把old leaf的`dirty`设为dirty（实现的时候，是把update info放到`dirty`）。

进行snapshot的时候，

1. 把所有leaf都放到一个list，`snap`里面，
2. 检测`snap`中每个leaf的`dirty`。如果发现`dirty`已被设置为update info，那么就help update info，并重新开始snapshot。

# References

1. Range Queries in Non-blocking k-ary Search Trees, Trevor Brown, Hillel Avni