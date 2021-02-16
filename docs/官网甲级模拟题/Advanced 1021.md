# 题目

## 1021 Deepest Root (25 分)

A graph which is connected and acyclic can be considered a tree. The height of the tree depends on the selected root. Now you are supposed to find the root that results in a highest tree. Such a root is called **the deepest root**.

### Input Specification:

Each input file contains one test case. For each case, the first line contains a positive integer *N* (≤104) which is the number of nodes, and hence the nodes are numbered from 1 to *N*. Then *N*−1 lines follow, each describes an edge by given the two adjacent nodes' numbers.

### Output Specification:

For each test case, print each of the deepest roots in a line. If such a root is not unique, print them in increasing order of their numbers. In case that the given graph is not a tree, print `Error: K components` where `K` is the number of connected components in the graph.

### Sample Input 1:

```in
5
1 2
1 3
1 4
2 5
```

### Sample Output 1:

```out
3
4
5
```

### Sample Input 2:

```in
5
1 3
1 4
2 5
3 4
```

### Sample Output 2:

```out
Error: 2 components
```

# 理解与算法

也是树的遍历，不过没有指定根节点，把每个节点都试一下就行，如果第一次遍历结束并不是所有节点都访问成功，那么就说明这个图不是连通图，直接进行连通块的查找。

连通块的查找也不复杂，只要最后所有的顶点都访问到了就算查找结束，一个例子：

```cpp
int check_connection() {
    int count = 1;
    for (int i = 1; i < N + 1; ++i) {
        if (!visit[i]) {
            dfs(i, i, 0);
            count++;
        }
    }
    return count;
}
```

## 代码与实现

```cpp
//
// Created by tanknee on 2/15/2021.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
int max_depth = 0, N, visit[10001];
vector<vector<int>> edges;
vector<int> roots;

void dfs(int root, int index, int depth) {
    bool flag = false;
    visit[index] = 1;
    for (int i = 0; i < edges[index].size(); ++i) {
        if (!visit[edges[index][i]]) {
            dfs(root, edges[index][i], depth + 1);
            flag = true;
        }
    }
    if (!flag) {
        if (max_depth < depth) {
            roots.clear();
            roots.push_back(root);
            max_depth = depth;
        } else if (max_depth == depth && !roots.empty() && roots.back() != root) {
            roots.push_back(root);
        }
    }
}

int check_connection() {
    int count = 1;
    for (int i = 1; i < N + 1; ++i) {
        if (!visit[i]) {
            dfs(i, i, 0);
            count++;
        }
    }
    return count;
}

int main() {
    int t1, t2;
    cin >> N;
    if (N == 1) {
        cin >> t1;
        cout << 1 << endl;
        return 0;
    }
    edges.resize(N + 1);
    for (int i = 1; i < N; ++i) {
        cin >> t1 >> t2;
        edges[t1].push_back(t2);
        edges[t2].push_back(t1);
    }
    int res = 0;
    for (int i = 1; i < N + 1; ++i) {
        if (!visit[i]) {
            dfs(i, i, 0);
            if (res == 0) {
                res = check_connection();
                if (res != 1) {
                    printf("Error: %d components", res);
                    return 0;
                }
            }
            fill(visit, visit + N + 1, 0);
        }
    }
    for (int root : roots) {
        cout << root << endl;
    }
    return 0;
}
```