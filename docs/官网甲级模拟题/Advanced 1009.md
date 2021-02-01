# 题目

## 1009 Product of Polynomials (25分)

This time, you are supposed to find *A*×*B* where *A* and *B* are two polynomials.

### Input Specification:

Each input file contains one test case. Each case occupies 2 lines, and each line contains the information of a polynomial:

*K* *N*1 *a**N*1 *N*2 *a**N*2 ... *N**K* *a**N**K*

where *K* is the number of nonzero terms in the polynomial, *N**i* and *a**N**i* (*i*=1,2,⋯,*K*) are the exponents and coefficients, respectively. It is given that 1≤*K*≤10, 0≤*N**K*<⋯<*N*2<*N*1≤1000.

### Output Specification:

For each test case you should output the product of *A* and *B* in one line, with the same format as the input. Notice that there must be **NO** extra space at the end of each line. Please be accurate up to 1 decimal place.

### Sample Input:

```in
2 1 2.4 0 3.2
2 2 1.5 1 0.5
```

### Sample Output:

```out
3 3 3.6 2 6.0 1 1.6
```

# 理解与算法

多项式乘法，思路也不难，遍历两个多项式，相乘即可，`M*N`的复杂度，需要考虑的是存储方式。

题目里给出的范围是`1-1000`，所以数组大小设置为2001就足够了，但是，如果指数范围非常大，大到几万，几十万，就不太好用数组来实现，可以考虑用map来实现。

## 代码与实现

```cpp
//
// Created by tanknee on 2021/1/24.
//

#include <iostream>
#include <map>

using namespace std;

int main() {
    int count, exponents;
    double coefficients, m1[1001] = {0.0}, result[2001] = {0.0};
    cin >> count;
    for (int i = 0; i < count; ++i) {
        cin >> exponents >> coefficients;
        m1[exponents] = coefficients;
    }
    cin >> count;
    for (int i = 0; i < count; ++i) {
        cin >> exponents >> coefficients;
        for (int j = 0; j < 1001; ++j) {
            if (m1[j] != 0.0)
                result[j + exponents] += m1[j] * coefficients;
        }
    }
    count = 0;
    for (int i = 2000; i >= 0; i--) {
        if (result[i] != 0.0)
            count++;
    }
    printf("%d", count);
    for (int i = 2000; i >= 0; i--) {
        if (result[i] != 0.0)
            printf(" %d %.1f", i, result[i]);
    }
    return 0;
}
```

