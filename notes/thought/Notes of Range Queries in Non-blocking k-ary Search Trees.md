@(thought)[concurrency 并发]

# Notes of Range Queries in Non-blocking k-ary Search Trees

这篇是k-ary的第二篇，为k-ary加入了range query，列举了range query的各种实现方法：STM，lock，Persistent data structures和snapshots，并说明各种方法的优劣，提出了range query的新方法。

# Approaches to Range Queries

* STM
* Lock
* Persistent data structures
* Snapshot
	* Ctrie
	* Snap

# Range Query in k-ary Search Trees

## `dirty` field

The `dirty` field is set to dirty when the leaf is affected by some update operations (`helpInsert` and `helpMark`).

## `Validate`

The `Validate` check all leaves stored in `snap`. If any `dirty` field is true, than `Validate` returns false.

## Range Query

The abridged `RangeQuery` follows few steps,

1. Use DFS to populate `snap` with all leaves that may contain a key in range.
2. Invoke `Validate` to check all the leaves stored in `snap`. If `Validate` returns false, than retry.
3. Extract all keys in range from `snap` and return.

# Differences between snaphots in BST and range query in k-ary search trees

|-|snapshots in BST|range query in k-ary search trees|
|-|:-:|:-:|
|Efficiency|low (iterate all nodes while checking)|high|
|Scope|global|partial|

*Just personal opinion, may contain errors.*

# Some Doubts

## Theorem 3 in Proof

In the paper,

> Theorem 3. All operations are non-blocking.

After discussing this with Keren, both of us feel it should be a bug.

But actually it's correct.

> My question:
> If the update operations are always exist (insertion and deletion are frequently invoked), than `RangeQuery` cannot return. So the `RangeQuery` is actually blocked by these update operations.
> 
> Answer from Brown:
> However, your intuition about range queries blocking is not quite correct. What you are referring to is **starvation**. **Starvation can happen in any algorithm that is not wait-free.** In order to be non-blocking, the algorithm simply needs to guarantee that, if operations are performed infinitely often, then operations will succeed infinitely often. (I.e., the system, as a whole, makes progress, even if some thread(s) starve.) Equivalently, a non-blocking progress guarantee simply states that it is impossible for /all/ threads to block forever. In your example, the fact that a range query is blocked by updates is not a problem, because the updates make progress.

# References

1. Non-blocking k-ary Search Trees, Trevor Brown, Joanna Helga
2. Range Queries in Non-blocking k-ary Search Trees, Trevor Brown, Hillel Avni