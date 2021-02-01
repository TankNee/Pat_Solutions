# 题目

## Deduplication on a Linked List (25)

### **题目描述**

Given a singly linked list L with integer keys, you are supposed to remove the nodes with duplicated absolute values of the keys.  That is, for each value K, only the first node of which the value or absolute value of its key equals K will be kept.  At the mean time, all the removed nodes must be kept in a separate list.  For example, given L being 21→-15→-15→-7→15, you must output 21→-15→-7, and the removed list -15→15.

### **输入描述:**

Each input file contains one test case.  For each case, the first line contains the address of the first node, and a positive N (<= 105) which is the total number of nodes.  The address of a node is a 5-digit nonnegative integer, and NULL is represented by -1.
Then N lines follow, each describes a node in the format:
Address Key Next
where Address is the position of the node, Key is an integer of which absolute value is no more than 104, and Next is the position of the next node.

### **输出描述:**

For each case, output the resulting linked list first, then the removed list.  Each node occupies a line, and is printed in the same format as in the input.


### **输入例子:**

```
00100 5
99999 -7 87654
23854 -15 00000
87654 15 -1
00000 -15 99999
00100 21 23854
```

### **输出例子:**

```
00100 21 23854
23854 -15 99999
99999 -7 -1
00000 -15 87654
87654 15 -1
```

## 理解与算法

这道题也不算很难，找出绝对值重复的节点，然后将这些节点放到另一个链表中即可，最后按照新的链表顺序输出。

要注意调整建立新的链表后也要记得调整节点的next指针的值！

还有代码输出的格式也要跟原来的格式完全一致！注意-1直接输出为-1而不是带0的数字字符！

这里使用printf比较方便实现这种效果！

```c++
printf("%05d %d %05d\n", rm_nodes[i].address, rm_nodes[i].value, rm_nodes[i].next);
```

## 代码与实现

```c++
//
// Created by tanknee on 2021/1/27.
//

#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct node {
    int address;
    int value;
    int next;

    bool operator=(node n) const {
        return address == n.address;
    }

    bool operator<(node n) const {
        return address < n.address;
    }
};

int main() {
    int head_address, N;
    cin >> head_address >> N;
    vector<node> nodes, re_nodes, rm_nodes;
    node head;
    set<node> s;
    set<int> k;
    for (int i = 0; i < N; ++i) {
        node n{};
        cin >> n.address >> n.value >> n.next;
        s.insert(n);
        if (n.address == head_address) {
            head.address = n.address;
            head.next = n.next;
            head.value = n.value;
        }
    }
    node n;
    n.address = head.next;
    nodes.push_back(head);
    for (int i = 1; i < N; ++i) {
        auto it = s.find(n);
        nodes.push_back((*it));
        n.address = (*it).next;
    }
    for (int i = 0; i < nodes.size(); ++i) {
        if (k.count(abs(nodes[i].value))) {
            re_nodes.rbegin()->next = nodes[i].next;
            nodes[i].next = -1;
            if (rm_nodes.size() != 0) {
                rm_nodes.rbegin()->next = nodes[i].address;
            }
            rm_nodes.push_back(nodes[i]);
        } else {
            k.insert(abs(nodes[i].value));
            re_nodes.push_back(nodes[i]);
        }
    }
    for (int i = 0; i < re_nodes.size(); ++i) {
        if (re_nodes[i].next != -1)
            printf("%05d %d %05d\n", re_nodes[i].address, re_nodes[i].value, re_nodes[i].next);
        else
            printf("%05d %d %d\n", re_nodes[i].address, re_nodes[i].value, re_nodes[i].next);
    }
    for (int i = 0; i < rm_nodes.size(); ++i) {
        if (rm_nodes[i].next != -1)
            printf("%05d %d %05d\n", rm_nodes[i].address, rm_nodes[i].value, rm_nodes[i].next);
        else
            printf("%05d %d %d\n", rm_nodes[i].address, rm_nodes[i].value, rm_nodes[i].next);
    }
    return 0;
}
```