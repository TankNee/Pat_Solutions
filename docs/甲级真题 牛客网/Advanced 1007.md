# 题目

## Consecutive Factors (20)

### **题目描述**
Among all the factors of a positive integer N, there may exist several consecutive numbers.  For example, 630 can be factored as 3*5*6*7, where 5, 6, and 7 are the three consecutive numbers.  Now given any positive N, you are supposed to find the maximum number of consecutive factors, and list the smallest sequence of the consecutive factors.
### **输入描述:**
Each input file contains one test case, which gives the integer N (131).
### **输出描述:**
For each test case, print in the first line the maximum number of consecutive factors.  Then in the second line, print the smallest sequence of the consecutive factors in the format "factor[1]*factor[2]*...*factor[k]", where the factors are listed in increasing order, and 1 is NOT included.
### **输入例子:**
```
630
```
### **输出例子:**

```
3
5*6*7
```

# 理解与算法

这道题，不是很复杂，就是找出一个正整数的因数中连续的那几个，找出最长的连续因数，如果长度相同则选取首项最小的因数序列！但是由于输入的数可能非常大，不能以常理度之，建议使用`long long int`来存取中间变量。

而且我们这里其实不需要求出所有的因子，不过还是有必要求出一个循环上限，提高我们的速率！我这里用的是输入的数开方$\sqrt{N}$，然后用循环就能很方便的实现，不需要用递归，否则可能会超时！

## 代码与实现

```cpp
//
// Created by tanknee on 2021/1/27.
//

#include <iostream>
#include <cmath>

using namespace std;


int main() {
    long long num, tmp, min, max_length = 0, sqr;
    cin >> num;
    min = num;
    sqr = (long long) sqrt(num * 1.0);
    for (long long i = 2; i <= sqr; ++i) {
        tmp = num;
        long long j = i;
        while (tmp % j == 0) {
            tmp /= j;
            j++;
        }
        tmp = j - 1;
        if (tmp - i + 1 > max_length) {
            max_length = tmp - i + 1;
            min = i;
        }
    }
    max_length = max_length == 0 ? 1 : max_length;
    cout << max_length << endl;
    cout << min;
    for (long long i = min + 1; i < min + max_length; ++i) {
        cout << "*" << i;
    }
    return 0;
}
```

