# 题目

## The Largest Generation (25)

### **题目描述**

A family hierarchy is usually presented by a pedigree tree where all the nodes on the same level belong to the same generation.  Your task is to find the generation with the largest population.

### **输入描述:**

Each input file contains one test case.  Each case starts with two positive integers N (<100) which is the total number of family members in the tree (and hence assume that all the members are numbered from 01 to N), and M (<N) which is the number of family members who have children.  Then M lines follow, each contains the information of a family member in the following format:
ID K ID[1] ID[2] ... ID[K]
where ID is a two-digit number representing a family member, K (>0) is the number of his/her children, followed by a sequence of two-digit ID's of his/her children. For the sake of simplicity, let us fix the root ID to be 01.  All the numbers in a line are separated by a space.


### **输出描述:**

For each test case, print in one line the largest population number and the level of the corresponding generation.  It is assumed that such a generation is unique, and the root level is defined to be 1.

### **输入例子:**

```
23 13
21 1 23
01 4 03 02 04 05
03 3 06 07 08
06 2 12 13
13 1 21
08 2 15 16
02 2 09 10
11 2 19 20
17 1 22
05 1 11
07 1 14
09 1 17
10 1 18
```

### **输出例子:**

```
9 4
```

# 理解与算法

这道题跟[PAT模拟题的1004](https://pintia.cn/problem-sets/994805342720868352/problems/994805521431773184)基本一致，不过从求叶子结点的数量变成了求节点最多的层的深度，以及节点的数量。

## 代码与实现

```cpp
//
// Created by tanknee on 2021/1/27.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> nodes[100]; // 每个元素代表一个节点链表
int pedigree[100], population[101];  // 族谱树中每一层的叶子结点的数量
int pedigree_depth = -1; // 族谱树的最大深度

/**
 * @param index 下标
 * @param depth 深度
 */
void dfs(int index, int depth) {
    if (!nodes[index].empty()) {
        population[depth] += nodes[index].size();
    }
    // 遍历该节点的所有子节点
    for (int i : nodes[index]) {
        // 因为往下走了一层，所以深度加1
        dfs(i, depth + 1);
    }
}

int main() {
    int N, M, node, num, child, max = 0, max_i = 0;
    // 处理第一行
    cin >> N >> M;
    // 遍历所有的非叶节点，构建节点链表
    for (int i = 0; i < M; ++i) {
        cin >> node >> num;
        for (int j = 0; j < num; ++j) {
            cin >> child;
            nodes[node].push_back(child);
        }
    }
    // 对族谱树进行深度优先遍历
    dfs(1, 0);
    for (int i = 0; i < N; ++i) {
        if (population[i] > max) {
            max = population[i];
            max_i = i + 2;
        }
    }
    cout << max << " " << max_i;
    return 0;
}
```

