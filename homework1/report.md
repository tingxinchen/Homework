# 41343128

作業一:問題1

## 解題說明

 問題1要求計算阿克曼函數，需要遞迴和非遞迴兩種做法。

### 解題策略
Ackermann 函數 \( A(m, n) \) 的數學定義如下：

$$
A(m, n) = 
\begin{cases} 
n + 1 & \text{if } m = 0 \\
A(m - 1, 1) & \text{if } n = 0 \\
A(m - 1, A(m, n - 1)) & \text{otherwise}
\end{cases}
$$
