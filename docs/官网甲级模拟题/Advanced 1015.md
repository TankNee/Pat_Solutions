# 题目

1015 Reversible Primes (20 分)

A **reversible prime** in any number system is a prime whose "reverse" in that number system is also a prime. For example in the decimal system 73 is a reversible prime because its reverse 37 is also a prime.

Now given any two positive integers *N* (<105) and *D* (1<*D*≤10), you are supposed to tell if *N* is a reversible prime with radix *D*.

### Input Specification:

The input file consists of several test cases. Each case occupies a line which contains two integers *N* and *D*. The input is finished by a negative *N*.

### Output Specification:

For each test case, print in one line `Yes` if *N* is a reversible prime with radix *D*, or `No` if not.

### Sample Input:

```in
73 10
23 2
23 10
-2
```

### Sample Output:

```out
Yes
Yes
No
```

# 理解与算法

这道题难在理解反转的方式，一开始我的理解是都转为10进制的数然后反转，然后只能通过一个测试，上网找了一下发现是按照指定的位进行反转。

例如23是素数，而他的二进制是：
$$
(23)_2=10111
$$
那么它在二进制内的反转就是：
$$
11101=(29)
$$
也是素数，所以能够满足题目的要求！

还有要注意的是如果一个数在十进制下是素数，那么在其他进制下也一定是素数。

这里给出一个求某个数的反转数的十进制的方法：

```cpp
int len = 0, arr[100];
do {
    arr[len++] = N % D;
    N = N / D;
} while (N != 0);
for (int i = 0; i < len; i++)
    N = N * D + arr[i];
```

大致就是将每一位都拆分出来，再合并计算。

## 代码与实现

```cpp
//
// Created by tanknee on 2021/2/10.
//

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool is_prime(int N) {
    if (N <= 1) return false;
    int sqr = int(sqrt(N * 1.0));
    for (int i = 2; i <= sqr; ++i) {
        if (N % i == 0) return false;
    }
    return true;
}

int main() {
    int N, D;
    while (scanf("%d", &N) != EOF) {
        if (N < 0) break;
        cin >> D;
        if (!is_prime(N)) {
            printf("No\n");
            continue;
        }
        // 反转
        int len = 0, arr[100];
        do {
            arr[len++] = N % D;
            N = N / D;
        } while (N != 0);
        for (int i = 0; i < len; i++)
            N = N * D + arr[i];
        printf("%s", is_prime(N) ? "Yes\n" : "No\n");
    }
    return 0;
}
```