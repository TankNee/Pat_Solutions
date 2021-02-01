# 题目

## Hashing (25)

### **题目描述**

The task of this problem is simple: insert a sequence of distinct positive integers into a hash table, and output the positions of the input numbers.  The hash function is defined to be "H(key) = key % TSize" where TSize is the maximum size of the hash table.  Quadratic probing (with positive increments only) is used to solve the collisions.
Note that the table size is better to be prime.  If the maximum size given by the user is not prime, you must re-define the table size to be the smallest prime number which is larger than the size given by the user.

### **输入描述:**

Each input file contains one test case.  For each case, the first line contains two positive numbers: MSize (<=104) and N (<=MSize) which are the user-defined table size and the number of input numbers, respectively.  Then N distinct positive integers are given in the next line.  All the numbers in a line are separated by a space.

### **输出描述:**

For each test case, print the corresponding positions (index starts from 0) of the input numbers in one line.  All the numbers in a line are separated by a space, and there must be no extra space at the end of the line.  In case it is impossible to insert the number, print "-" instead.

### **输入例子:**

```
4 4
10 6 4 15
```

### **输出例子:**

```
0 1 4 -
```

# 理解与算法

用平方探测法实现哈希表，算法是听过的，但怎么实现就一时想不起来。理解一个思想，hash表的关键在于hash函数的实现，hash函数就是给一个数找到它在hash表上的位置，二次探测法是解决位置冲突问题的方法，公式如下：
$$
Position = (N + Step^2)\% TableSize
$$
其中的步长Step从0开始迭代，直到找到位置放数N，如果没有找到合适的位置，就输出"-"。可以看到，当步长为0的时候这个公式就变成了Hash函数，所以我们直接用这个公式迭代也没啥问题。

在开始寻找位置之前，最好要确保Hash表的长度或者说是大小是素数。

> 假如关键字是随机分布的，那么无所谓一定要模质数。但在实际中往往关键字有某种规律，例如大量的等差数列，那么公差和模数不互质的时候发生碰撞的概率会变大，而用质数就可以很大程度上回避这个问题。
>
> ---[十一太保念技校](https://www.zhihu.com/people/li-guo-hua-93)

## 代码与实现

```c
//
// Created by tanknee on 2021/1/30.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool is_prime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    int sqr = sqrt(num), i = 2;
    while (i <= sqr) {
        if (num % i == 0) return false;
        i++;
    }
    return true;
}

int main() {
    int t_size, num, tmp;
    cin >> t_size >> num;
    while (!is_prime(t_size))
        t_size++;
    bool hash_table[t_size];
    fill(hash_table, hash_table + t_size, false);
    for (int i = 0; i < num; ++i) {
        cin >> tmp;
        int j;
        for (j = 0; j < t_size; ++j) {
            int pos = (tmp + j * j) % t_size;
            if (!hash_table[pos]) {
                hash_table[pos] = true;
                cout << pos;
                break;
            }
        }
        if (j == t_size) cout << "-";
        if (i != num - 1) cout << " ";
    }
    return 0;
}
```