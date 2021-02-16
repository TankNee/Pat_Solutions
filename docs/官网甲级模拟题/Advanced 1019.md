# 题目

## 1019 General Palindromic Number (20 分)

A number that will be the same when it is written forwards or backwards is known as a **Palindromic Number**. For example, 1234321 is a palindromic number. All single digit numbers are palindromic numbers.

Although palindromic numbers are most often considered in the decimal system, the concept of palindromicity can be applied to the natural numbers in any numeral system. Consider a number *N*>0 in base *b*≥2, where it is written in standard notation with *k*+1 digits *a**i* as ∑*i*=0*k*(*a**i**b**i*). Here, as usual, 0≤*a**i*<*b* for all *i* and *a**k* is non-zero. Then *N* is palindromic if and only if *a**i*=*a**k*−*i* for all *i*. Zero is written 0 in any base and is also palindromic by definition.

Given any positive decimal integer *N* and a base *b*, you are supposed to tell if *N* is a palindromic number in base *b*.

### Input Specification:

Each input file contains one test case. Each case consists of two positive numbers *N* and *b*, where 0<*N*≤109 is the decimal number and 2≤*b*≤109 is the base. The numbers are separated by a space.

### Output Specification:

For each test case, first print in one line `Yes` if *N* is a palindromic number in base *b*, or `No` if not. Then in the next line, print *N* as the number in base *b* in the form "*a**k* *a**k*−1 ... *a*0". Notice that there must be no extra space at the end of output.

### Sample Input 1:

```in
27 2
```

### Sample Output 1:

```out
Yes
1 1 0 1 1
```

### Sample Input 2:

```in
121 5
```

### Sample Output 2:

```out
No
4 4 1
```

# 理解与算法

在某个指定进制下的回文数，题目要求判断一个数字是否是回文数，并且不管它是不是，都要打印它在指定进制下的数字表示！

题目不难，只要想明白怎样将一个十进制的数转换为任意进制的其他数字就好。

给出一个常用的转换方法：

```cpp
do {
    nums.push_back(tmp % b);
    tmp /= b;
} while (tmp != 0);
```

不过这样子转换出来的数字是逆序的，最后打印的时候要倒着打印。回文数的判断没什么好说的，直接搞两个指针，从两边向中间走就完事了。

## 代码与实现

```cpp
//
// Created by tanknee on 2021/2/14.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    vector<int> nums;
    long long N, b;
    cin >> N >> b;
//    int index = 0;
    long long tmp = N;
    do {
        nums.push_back(tmp % b);
        tmp /= b;
    } while (tmp != 0);
    for (int i = 0; i < nums.size() / 2 + 1; ++i) {
        if (nums[i] != nums[nums.size() - 1 - i]) {
            cout << "No" << endl;
            break;
        }
        if (i == nums.size() / 2) {
            cout << "Yes" << endl;
            break;
        }
    }
    for (int i = nums.size() - 1; i >= 0; --i) {
        cout << nums[i];
        if (i != 0) cout << " ";
    }
    return 0;
}
```

