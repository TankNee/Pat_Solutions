# 题目

## 1032 Sharing (25 分)

To store English words, one method is to use linked lists and store a word letter by letter. To save some space, we may let the words share the same sublist if they share the same suffix. For example, `loading` and `being` are stored as showed in Figure 1.

![fig.jpg](https://images.ptausercontent.com/ef0a1fdf-3d9f-46dc-9a27-21f989270fd4.jpg)

Figure 1

You are supposed to find the starting position of the common suffix (e.g. the position of `i` in Figure 1).

### Input Specification:

Each input file contains one test case. For each case, the first line contains two addresses of nodes and a positive *N* (≤105), where the two addresses are the addresses of the first nodes of the two words, and *N* is the total number of nodes. The address of a node is a 5-digit positive integer, and NULL is represented by −1.

Then *N* lines follow, each describes a node in the format:

```
Address Data Next
```

where`Address` is the position of the node, `Data` is the letter contained by this node which is an English letter chosen from { a-z, A-Z }, and `Next` is the position of the next node.

### Output Specification:

For each case, simply output the 5-digit starting position of the common suffix. If the two words have no common suffix, output `-1` instead.

### Sample Input 1:

```in
11111 22222 9
67890 i 00002
00010 a 12345
00003 g -1
12345 D 67890
00002 n 00003
22222 B 23456
11111 L 00001
23456 e 67890
00001 o 00010
```

### Sample Output 1:

```out
67890
```

### Sample Input 2:

```in
00001 00002 4
00001 a 10001
10001 s -1
00002 a 10002
10002 t -1
```

### Sample Output 2:

```out
-1
```

# 理解与算法

找出两条链表的公共节点，一种暴力的想法是选取一条链表，然后把这条链表的所有节点都跟另一条链表进行比较，如果有一样地址的节点，那就直接返回，但这样会超时，时间复杂度为$O(MN)$，其中M，N为两条链表的长度。

换个角度，直接遍历链表的时候一定会经过链表的重合节点，因此只要在第一次遍历的时候对所有经过的节点打上标记，然后再去另一条链表上寻找有标记的节点，那么就可以将复杂度降到$O(M+N)$，效率大大提高！

## 代码与实现

```cpp
//
// Created by tanknee on 2/25/2021.
//

#include <bits/stdc++.h>
#include <cstring>

using namespace std;

struct node {
    int next;
    char value;
    bool flag;
};

int main() {
    int head_1, head_2, N, addr;
    cin >> head_1 >> head_2 >> N;
    node nodes[100000];
    for (int i = 0; i < N; ++i) {
        cin >> addr;
        cin >> nodes[addr].value >> nodes[addr].next;
    }
    while (head_2 != -1) {
        nodes[head_2].flag = true;
        head_2 = nodes[head_2].next;
    }
    while (head_1 != -1) {
        if (nodes[head_1].flag) {
            printf("%05d", head_1);
            return 0;
        }
        head_1 = nodes[head_1].next;
    }
    cout << -1;
    return 0;
}
```

