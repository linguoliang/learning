[data structures and algorithms 数据结构和算法]

# Algorithms Summaries

# Dynamic Programming

## Longest Increasing Subsequence

Variations:

1. Maximum Sum Increasing Subsequence
2. Longest Bitonic Subsequence

## Matrix Chain Multiplication

思路很简单，分别计算长度为`[2, chain.size() - 1]`的cost，buttom up即可。

关键是index的处理，输入的维度是矩阵去除重复维度以后的，`[d_1, d_2, d_3, ..., d_n]`，每个矩阵的维度是`(d_i, d_{i + 1}), 0 <= i <= chain.size() - 1`。矩阵的个数为`chain.size() - 1`。

```cpp
// n是矩阵的长度，而不是维度的。
int n = dimensions.size() - 1;

// 长度为1的chain就是个矩阵，cost为0.
for (int i = 0; i < n; ++i) {
  dp[i][i] = 0;
}

for (int cl = 2; cl <= n; ++cl) {
  // 循环处理长度为[2, n]的chain。
  // 到结尾时，j == n - 1，又因i + cl - 1 = n - 1，所以i = n - cl
  for (int i = 0; i <= n - cl; ++i) {
    int j = i + cl - 1;
    // 处理chain[i, j]
    dp[i][j] = INT_MAX;
    for (int k = i; k <= j - 1; ++k) {
      dp[i][j] =
          min(dp[i][k] + dp[k + 1][j] +
                  dimensions[i] * dimensions[k + 1] * dimensions[j + 1], dp[i][j]);
    }
  }
}
```

Variations:

1. Palindrome Partitioning

Similarities:

1. Longest Palindromic Subsequence
在用Tabulation方法来解决时，构造dp表也是考虑substring的长度为[2, seq.size())。

## Knapsack

Variations:

1. Partition Problem

## Word wrap