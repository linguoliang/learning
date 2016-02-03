# Transformations

|Function Name|Purpose|Definition|
|:|:|:|
||||

## `aggregate`

## `combineByKey`

## Joins

# Data Partitioning

# Shuffle

Spark needs to perform an all-to-all operation. It must read from all partitions to find all the values for all keys, and then bring together values across partitions to compute the final result for each key - this is called the **shuffle**.

# Closures

The closure is those **variables and methods which must be visible for the executor** to perform its computations on the RDD (in this case foreach()). This closure is serialized and sent to each executor. Prior to execution, Spark computes the closure.

# Shared Variables

## Broadcast Variables

Broadcast variables allow the programmer to keep a read-only  variable cached on each machine rather than shipping a copy of it with tasks.

The variable will be sent to each node only once, and **should be treated as read-only** (updates will not be propagated to other nodes).

## Accumulators

For accumulator updates performed inside actions only, Spark guarantees that each task’s update to the accumulator will **only be applied once**, i.e. restarted tasks will not update the value. In transformations, users should be aware of that each task’s update **may be applied more than once** if tasks or job stages are re-executed.