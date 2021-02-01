# 题目

## Build A Binary Search Tree (30)

### **题目描述**

A Binary Search Tree (BST) is recursively defined as a binary tree which has the following properties:
The left subtree of a node contains only nodes with keys less than the node's key.
The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
Both the left and right subtrees must also be binary search trees. 
Given the structure of a binary tree and a sequence of distinct integer keys, there is only one way to fill these keys into the tree so that the resulting tree satisfies the definition of a BST.  You are supposed to output the level order traversal sequence of that tree.  The sample is illustrated by Figure 1 and 2.

![img](http://uploadfiles.nowcoder.com/images/20150613/805592_1434173853368_1099A.jpg)

### **输入描述:**

Each input file contains one test case.  For each case, the first line gives a positive integer N (<=100) which is the total number of nodes in the tree.  The next N lines each contains the left and the right children of a node in the format "left_index right_index", provided that the nodes are numbered from 0 to N-1, and 0 is always the root.  If one child is missing, then -1 will represent the NULL child pointer.  Finally N distinct integer keys are given in the last line.

### **输出描述:**

For each test case, print in one line the level order traversal sequence of that tree.  All the numbers must be separated by a space, with no extra space at the end of the line.

### **输入例子:**

```
9
1 6
2 3
-1 -1
-1 4
5 -1
-1 -1
7 -1
-1 8
-1 -1
73 45 11 58 82 25 67 38 42
```

### **输出例子:**

```
58 25 82 11 38 67 45 73 42
```

# 理解与算法

这道题是变相重构二叉树，不过这里有了更多的条件与限制，构建出来的二叉树是二叉搜索树BST，满足下面几点：

- 左子树的所有节点都比根节点小
- 右节点所有节点都比根节点大
- BST的前序遍历就是全部元素的升序排列

重构二叉树很重要的一个方法就是通过其全部节点的遍历方式来重构！

根据二叉搜索树的第三个特点，我们可以先找出其前序遍历的结果集：将所有节点值进行升序排列！

然后要怎么样才能把数据填入到预先设定好的节点中？按照一定的顺序来：每次填入的节点都是剩下没有填入数值的节点中排序最小的节点！也就是以下的优先度：

1. 左子树
2. 根节点
3. 右子树

给出这样一个搜索方法：

```c
int cur_node = 0, index = 0;
while (cur_node != -1 || !v.empty()) {
    while (cur_node != -1) {
        v.push_back(cur_node);
        cur_node = nodes[cur_node].left;
    }
    if (!v.empty()) {
        cur_node = v.back();
        v.pop_back();
        nodes[cur_node].value = numbers[index];
        index++;
        cur_node = nodes[cur_node].right;
    }
}
```

找出最左的叶子结点，并记录查找路径：

```c
while (cur_node != -1) {
    v.push_back(cur_node);
    cur_node = nodes[cur_node].left;
}
```

当查找到的节点是空节点，则回退到上一层，将最小的那个数赋值给它，因为当左节点为空，下一个应该填充的值就是路径的最后一个节点，如果是右节点为空，根据我们的代码逻辑，此时根节点必定是赋值过的，那么就找上一个经过的节点，同样也是路径的最后那个节点，这样两种逻辑也就归一了，可以使用同一段代码来实现。

```c
if (!v.empty()) {
    cur_node = v.back();
    v.pop_back();
    nodes[cur_node].value = numbers[index];
    index++;
    cur_node = nodes[cur_node].right;
}
```

构建完二叉树之后其实就没什么难度，直接用宽度优先搜索BFS进行遍历就可以。

## 代码与实现

```c
//
// Created by tanknee on 2021/1/28.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct node {
    int left, right, value;
};


/**
 * 先对输入进行排序，得到的数组就是中序遍历的树！因为对于二叉搜索树，中序遍历就是从小到大排序。
 * @return
 */
int main() {
    int N;
    cin >> N;
    vector<int> numbers(N, 0), v;
    queue<int> q;
    node nodes[N];
    for (int i = 0; i < N; ++i) {
        cin >> nodes[i].left >> nodes[i].right;
    }
    for (int i = 0; i < N; ++i) {
        cin >> numbers[i];
    }
    sort(numbers.begin(), numbers.end());
    int cur_node = 0, index = 0;
    while (cur_node != -1 || !v.empty()) {
        while (cur_node != -1) {
            v.push_back(cur_node);
            cur_node = nodes[cur_node].left;
        }
        if (!v.empty()) {
            cur_node = v.back();
            v.pop_back();
            nodes[cur_node].value = numbers[index];
            index++;
            cur_node = nodes[cur_node].right;
        }
    }
    cur_node = 0;
    q.push(cur_node);
    while (!q.empty()) {
        cur_node = q.front();
        if (nodes[cur_node].left != -1)
            q.push(nodes[cur_node].left);
        if (nodes[cur_node].right != -1)
            q.push(nodes[cur_node].right);
        cout << nodes[cur_node].value;
        if (q.size() > 1) {
            cout << " ";
        }
        q.pop();
    }
    return 0;
}
```