# 题目

## 1020 Tree Traversals (25 分)

Suppose that all the keys in a binary tree are distinct positive integers. Given the postorder and inorder traversal sequences, you are supposed to output the level order traversal sequence of the corresponding binary tree.

### Input Specification:

Each input file contains one test case. For each case, the first line gives a positive integer *N* (≤30), the total number of nodes in the binary tree. The second line gives the postorder sequence and the third line gives the inorder sequence. All the numbers in a line are separated by a space.

### Output Specification:

For each test case, print in one line the level order traversal sequence of the corresponding binary tree. All the numbers in a line must be separated by exactly one space, and there must be no extra space at the end of the line.

### Sample Input:

```in
7
2 3 1 5 7 6 4
1 2 3 4 5 6 7
```

### Sample Output:

```out
4 1 6 3 5 7 2
```

# 理解与算法

常规的一道二叉树遍历，给出后序遍历和中序遍历，然后让你求层序遍历的结果。

两个思路：

- 在重建二叉树的时候顺便找出层序遍历的结果。
- 先重建二叉树，然后再用BFS进行层序遍历。

毫无疑问，前者的效率更高。在做这道题目的时候还要知道一个很重要的规律，在层序遍历中，root的左节点的编号是$2*root+1$。右节点是$2*root+2$，所以我们使用的遍历代码如下：

```cpp
map<int, int> level;
void pre(int root, int start, int end, int index) {
    if (start > end) return;
    int i = start;
    // 找到中序遍历中的根节点
    while (i < end && in_order[i] != post_order[root]) i++;
    // 将对应的节点放到层序遍历中指定的位置
    level[index] = post_order[root];
    pre(root - 1 - end + i, start, i - 1, 2 * index + 1);
    pre(root - 1, i + 1, end, 2 * index + 2);
}
```

## 代码与实现

```cpp
//
// Created by tanknee on 2021/2/14.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
vector<int> post_order, in_order;
map<int, int> level;

void pre(int root, int start, int end, int index) {
    if (start > end) return;
    int i = start;
    while (i < end && in_order[i] != post_order[root]) i++;
    level[index] = post_order[root];
    pre(root - 1 - end + i, start, i - 1, 2 * index + 1);
    pre(root - 1, i + 1, end, 2 * index + 2);
}

int main() {
    int N;
    cin >> N;
    post_order.resize(N);
    in_order.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> post_order[i];
    }
    for (int i = 0; i < N; ++i) {
        cin >> in_order[i];
    }
    pre(N - 1, 0, N - 1, 0);
    auto it = level.begin();
    printf("%d", it->second);
    while(++it != level.end()) printf(" %d", it->second);
    return 0;
}
```