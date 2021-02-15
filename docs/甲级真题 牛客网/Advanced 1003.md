

# 题目

## 1003 Highest Price in Supply Chain (25)

### **题目描述**

A supply chain is a network of retailers（零售商）, distributors（经销商）, and suppliers（供应商）-- everyone involved in moving a product from supplier to customer.
Starting from one root supplier, everyone on the chain buys products from one's supplier in a price P and sell or distribute them in a price that is r% higher than P.  
It is assumed that each member in the supply chain has exactly one supplier except the root supplier, and there is no supply cycle.
Now given a supply chain, you are supposed to tell the highest price we can expect from some retailers.


### **输入描述:**

Each input file contains one test case.  For each case, The first line contains three positive numbers: N (<=105), the total number of the members in the supply chain (and hence they are numbered from 0 to N-1); P, the price given by the root supplier; and r, the percentage rate of price increment for each distributor or retailer.  Then the next line contains N numbers, each number Si is the index of the supplier for the i-th member.  Sroot for the root supplier is defined to be -1.  All the numbers in a line are separated by a space.

### **输出描述:**

For each test case, print in one line the highest price we can expect from some retailers, accurate up to 2 decimal places, and the number of retailers that sell at the highest price.  There must be one space between the two numbers.  It is guaranteed that the price will not exceed 1010.

### **输入例子:**

```
9 1.80 1.00
1 5 4 4 -1 4 5 3 6
```

### **输出例子:**

```
1.85 2
```

# 理解与算法

先说几个遇到的问题

- relocation truncated to fit: R_X86_64_PC32 against symbol `num' defined in 

因为我定义了一个超大的全局变量`int num[100001][100001]`，触发了g++对静态数组大小的限制，导致编译失败，报错信息十分反人类，在此记下，引以为戒。

- 超出内存限制

因为遇到了了上面那个超大的数组的问题，所以我又改用向量vector来实现，但是向量也需要长度定义，所以我放在main函数里面定义，然后将其作为一个参数传递给dfs方法，最后发现还是炸了，然后我选择在全局定义向量...然后就神奇的可以了..

## 代码与实现

```cpp
//
// Created by tanknee on 2021/1/26.
//

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int cnt = 0, num, max_depth = 0;
vector<vector<int>> edge(100000, vector<int>());

void dfs(int index, int depth) {
    if (edge[index].empty()) {
        if (depth > max_depth) {
            cnt = 1;
            max_depth = depth;
        } else if (depth == max_depth) {
            cnt++;
        }
    }
    for (int i = 0; i < edge[index].size(); ++i) {
        dfs(edge[index][i], depth + 1);
    }
}

int main() {
    double price, inc;
    cin >> num >> price >> inc;
    for (int i = 1; i < num + 1; ++i) {
        int tmp;
        cin >> tmp;
        edge[tmp + 1].push_back(i);
    }
    dfs(0, 0);
    price = price * pow((1 + inc / 100.0), max_depth - 1);
    printf("%.2f %d", price, cnt);
    return 0;
}
```

