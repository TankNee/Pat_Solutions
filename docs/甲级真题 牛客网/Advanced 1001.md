# 题目

## 1001 Public Bike Management (30)

### **题目描述**

There is a public bike service in Hangzhou City which provides great convenience to the tourists from all over the world.  One may rent a bike at any station and return it to any other stations in the city.
The Public Bike Management Center (PBMC) keeps monitoring the real-time capacity of all the stations.  A station is said to be in perfect condition if it is exactly half-full.  If a station is full or empty, PBMC will collect or send bikes to adjust the condition of that station to perfect.  And more, all the stations on the way will be adjusted as well. 
 When a problem station is reported, PBMC will always choose the shortest path to reach that station.  If there are more than one shortest path, the one that requires the least number of bikes sent from PBMC will be chosen.

![](https://img.tanknee.cn/blogpicbed/2021/01/26/20210126cfe9733c42979.png)


Figure 1


Figure 1 illustrates an example.  The stations are represented by vertices and the roads correspond to the edges.  The number on an edge is the time taken to reach one end station from another.  The number written inside a vertex S is the current number of bikes stored at S.  Given that the maximum capacity of each station is 10.  To solve the problem at S3, we have 2 different shortest paths:
1. PBMC -> S1 -> S3.  In this case, 4 bikes must be sent from PBMC, because we can collect 1 bike from S1 and then take 5 bikes to S3, so that both stations will be in perfect conditions.
2. PBMC -> S2 -> S3.  This path requires the same time as path 1, but only 3 bikes sent from PBMC and hence is the one that will be chosen.


### **输入描述:**


Each input file contains one test case.  For each case, the first line contains 4 numbers: Cmax (<= 100), always an even number, is the maximum capacity of each station; N (<= 500), the total number of stations; Sp, the index of the problem station (the stations are numbered from 1 to N, and PBMC is represented by the vertex 0); and M, the number of roads.  The second line contains N non-negative numbers Ci (i=1,...N) where each  Ci is the current number of bikes at Si respectively.  Then M lines follow, each contains 3 numbers: Si, Sj, and Tij which describe the time Tij taken to move betwen stations Si and Sj.  All the numbers in a line are separated by a space.


### **输出描述:**

For each test case, print your results in one line.  First output the number of bikes that PBMC must send.  Then after one space, output the path in the format: 0->S1->...->Sp.  Finally after another space, output the number of bikes that we must take back to PBMC after the condition of Sp is adjusted to perfect.
Note that if such a path is not unique, output the one that requires minimum number of bikes that we must take back to PBMC.  The judge's data guarantee that such a path is unique.


### **输入例子:**

```in
10 3 3 5
6 7 0
0 1 1
0 2 1
0 3 3
1 3 1
2 3 1
```

### **输出例子:**

```out
3 0->2->3 0
```

# 理解与算法

一个关于图的问题，基础问题是计算最短路径，然后在所有的最短路径中寻找更优的路径。

- 路程相同，优先选择从PBMC带出的自行车少的那条路
- 带出的自行车相同，就优先选择带回PBMC的自行车少的那条

同时还需要记录最短路径的完整链路，我这里使用了vector来存储，但感觉会有很多冗余，因为并不是所有路在计算最后的路径时都会用上！

该怎么计算从PBMC带出的自行车数量，在已知行进路线的情况下：

```c++
int get_sent(vector<int> links) {
    int sum = 0, min = INT_MAX;
    for (int i = 1; i < links.size(); ++i) {
        sum += stock[links[i]] - capacity / 2;
        min = sum < min ? sum : min;
    }
    if (min < 0) {
        return -min;
    }
    return 0;
}
```

为了让沿途所有的站点都恢复到perfect状态，我们必须考虑到最坏的情况，就好比我们将携带的自行车的数量描绘成一个函数，这个函数不能为负数！所以在初始为0的情况下，找到这个函数的最小值，就是我们出门的时候要带的自行车数量！

<img src="https://img.tanknee.cn/blogpicbed/2021/01/26/20210126a9d3b73fcefdb.png" alt="image-20210126134205256" style="zoom:50%;" />

同理，当我们知道了带出门的自行车数量的时候，就能很方便的知道带回去的数量。

```c++
int get_back(vector<int> links, int init) {
    int sum = 0;
    for (int i = 1; i < links.size(); ++i) {
        sum += stock[links[i]] - capacity / 2;
    }
    return sum + init;
}
```

这道题也算是一个很不错的dijkstra的模板题，用来练手挺不错。

## 代码与实现

```c++
#include <iostream>
#include <vector>
#include <climits>

using namespace std;
int stock[501], dis[501], capacity;

int get_back(vector<int> links, int init) {
    int sum = 0;
    for (int i = 1; i < links.size(); ++i) {
        sum += stock[links[i]] - capacity / 2;
    }
    return sum + init;
}

int get_sent(vector<int> links) {
    int sum = 0, min = INT_MAX;
    for (int i = 1; i < links.size(); ++i) {
        sum += stock[links[i]] - capacity / 2;
        min = sum < min ? sum : min;
    }
    if (min < 0) {
        return -min;
    }
    return 0;
}

int main() {
    int n, problem_station, m, s1, s2, length;
    bool visit[501];
    fill(visit, visit + 501, false);
    fill(dis, dis + 501, INT_MAX);
    cin >> capacity >> n >> problem_station >> m;

    vector<vector<int>> roads(n + 1, vector<int>(n + 1, INT_MAX));
    vector<vector<int>> nearest_roads(n + 1, vector<int>(1, 0));

    for (int i = 1; i <= n; ++i) {
        cin >> stock[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> s1 >> s2 >> length;
        roads[s1][s2] = length;
        roads[s2][s1] = length;
    }
    dis[0] = 0;
    for (int i = 0; i <= n; ++i) {
        int u = -1, min_num = INT_MAX;
        for (int j = 0; j <= n; j++) {
            // 找出没访问过的顶点中距离最近的点
            if (!visit[j] && dis[j] < min_num) {
                u = j;
                min_num = dis[j];
            }
        }
        if (u == -1) break;
        visit[u] = true;
        for (int v = 1; v <= n; v++) {
            // 如果v这个点没有访问过，且u到v是有路径的，那么就有可能刷新最短距离。
            if (!visit[v] && roads[u][v] != INT_MAX) {
                if (dis[u] + roads[u][v] < dis[v]) {
                    dis[v] = dis[u] + roads[u][v];
                    // 如果到这个点的路径没有被记录，那就将这个点加进去
                    if (nearest_roads[v].size() == 1) {
                        nearest_roads[v].push_back(v);
                    } else {
                        // 如果已经有链路，就清空，将从原点到u的链路加进来，再加入v;
                        nearest_roads[v].clear();
                        for (int j = 0; j < nearest_roads[u].size(); ++j) {
                            nearest_roads[v].push_back(nearest_roads[u][j]);
                        }
                        nearest_roads[v].push_back(v);
                    }
                } else if (dis[u] + roads[u][v] == dis[v] && v == problem_station) {
                    int tmp1 = get_sent(nearest_roads[v]);
                    nearest_roads[u].push_back(v);
                    int tmp2 = get_sent(nearest_roads[u]);
                    nearest_roads[u].pop_back();
                    if (tmp1 > tmp2) {
                        nearest_roads[v].clear();
                        for (int j = 0; j < nearest_roads[u].size(); ++j) {
                            nearest_roads[v].push_back(nearest_roads[u][j]);
                        }
                        nearest_roads[v].push_back(v);
                    } else if (tmp1 == tmp2) {
                        tmp1 = get_back(nearest_roads[v], tmp1);
                        nearest_roads[u].push_back(v);
                        tmp2 = get_back(nearest_roads[u], tmp2);
                        nearest_roads[u].pop_back();
                        if (tmp1 > tmp2) {
                            nearest_roads[v].clear();
                            for (int j = 0; j < nearest_roads[u].size(); ++j) {
                                nearest_roads[v].push_back(nearest_roads[u][j]);
                            }
                            nearest_roads[v].push_back(v);
                        }
                    }
                }
            }
        }
    }
    cout << get_sent(nearest_roads[problem_station]) << " " << nearest_roads[problem_station][0];
    for (int i = 1; i < nearest_roads[problem_station].size(); ++i) {
        cout << "->" << nearest_roads[problem_station][i];
    }
    cout << " " << get_back(nearest_roads[problem_station], get_sent(nearest_roads[problem_station]));
    return 0;
}
```

