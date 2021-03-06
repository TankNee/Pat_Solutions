# 题目

## 1030 Travel Plan (30 分)

A traveler's map gives the distances between cities along the highways, together with the cost of each highway. Now you are supposed to write a program to help a traveler to decide the shortest path between his/her starting city and the destination. If such a shortest path is not unique, you are supposed to output the one with the minimum cost, which is guaranteed to be unique.

### Input Specification:

Each input file contains one test case. Each case starts with a line containing 4 positive integers *N*, *M*, *S*, and *D*, where *N* (≤500) is the number of cities (and hence the cities are numbered from 0 to *N*−1); *M* is the number of highways; *S* and *D* are the starting and the destination cities, respectively. Then *M* lines follow, each provides the information of a highway, in the format:

```
City1 City2 Distance Cost
```

where the numbers are all integers no more than 500, and are separated by a space.

### Output Specification:

For each test case, print in one line the cities along the shortest path from the starting point to the destination, followed by the total distance and the total cost of the path. The numbers must be separated by a space and there must be no extra space at the end of output.

### Sample Input:

```in
4 5 0 3
0 1 1 20
1 3 2 30
0 3 4 10
0 2 2 20
2 3 1 20
```

### Sample Output:

```out
0 2 3 3 40
```

# 理解与算法

给出一个图，求其最短路径，如果最短路径有多条，则选择开销最低的那条，用Djikstra就能很方便的解决，只要在替换最短路径的时候存储路径链表即可。

## 代码与实现

```cpp
//
// Created by tanknee on 2/24/2021.
//

#include <bits/stdc++.h>

using namespace std;

struct node {
    int distance, cost;
};
int N, M, S, D, visit[500];
vector<vector<node>> highways;

int main() {
    int tmp1, tmp2;
    cin >> N >> M >> S >> D;
    int dis[N], cost[N];
    fill(dis, dis + N, INT_MAX);
    fill(cost, cost + N, INT_MAX);
    vector<vector<int>> routines(N, vector<int>{});
    highways.resize(N, vector<node>(N, node{}));
    for (int i = 0; i < M; ++i) {
        cin >> tmp1 >> tmp2;
        cin >> highways[tmp1][tmp2].distance >> highways[tmp1][tmp2].cost;
        highways[tmp2][tmp1].distance = highways[tmp1][tmp2].distance;
        highways[tmp2][tmp1].cost = highways[tmp1][tmp2].cost;
    }
    dis[S] = 0;
    cost[S] = 0;
    routines[S].push_back(S);
    for (int i = 0; i < N; ++i) {
        int u = -1, min = INT_MAX;
        for (int j = 0; j < N; ++j) {
            if (!visit[j] && dis[j] < min) {
                min = dis[j];
                u = j;
            }
        }
        if (u == -1) break;
        visit[u] = 1;
        for (int j = 0; j < N; ++j) {
            if (visit[j] || !highways[u][j].distance) continue;
            if (dis[u] + highways[u][j].distance < dis[j]) {
                dis[j] = dis[u] + highways[u][j].distance;
                cost[j] = cost[u] + highways[u][j].cost;
                routines[j].clear();
                for (int k = 0; k < routines[u].size(); ++k) {
                    routines[j].push_back(routines[u][k]);
                }
                routines[j].push_back(j);
            } else if (dis[u] + highways[u][j].distance == dis[j]) {
                if (cost[u] + highways[u][j].cost < cost[j]) {
                    routines[j].clear();
                    for (int k = 0; k < routines[u].size(); ++k) {
                        routines[j].push_back(routines[u][k]);
                    }
                    routines[j].push_back(j);
                    cost[j] = cost[u] + highways[u][j].cost;
                }
            }
        }
    }
    for (int i = 0; i < routines[D].size(); ++i) {
        cout << routines[D][i] << " ";
    }
    cout << dis[D] << " " << cost[D];
    return 0;
}
```

