# 题目与翻译

## 1003 Emergency 紧急情况 (25分)

As an emergency rescue team leader of a city, you are given a special map of your country. The map shows several scattered cities connected by some roads. Amount of rescue teams in each city and the length of each road between any pair of cities are marked on the map. When there is an emergency call to you from some other city, your job is to lead your men to the place as quickly as possible, and at the mean time, call up as many hands on the way as possible.

作为一个城市的紧急救援队队长，你会得到一张特殊的国家地图。这张地图显示了由一些道路连接起来的几个零散的城市。每个城市的救援队伍数量以及每一对城市之间的道路长度都在地图上标注出来。当其他城市给你打紧急电话时，你的工作就是带领你的人尽快赶到那个地方，同时，在路上尽可能多的召集人手。

### Input Specification:

### 输入规格:

Each input file contains one test case. For each test case, the first line contains 4 positive integers: *N* (≤500) - the number of cities (and the cities are numbered from 0 to *N*−1), *M* - the number of roads, *C*1 and *C*2 - the cities that you are currently in and that you must save, respectively. The next line contains *N* integers, where the *i*-th integer is the number of rescue teams in the *i*-th city. Then *M* lines follow, each describes a road with three integers *c*1, *c*2 and *L*, which are the pair of cities connected by a road and the length of that road, respectively. It is guaranteed that there exists at least one path from *C*1 to *C*2.

每个输入文件包含一个测试用例。对于每个测试案例，第一行包含4个正整数: n (≤500)-城市数量(城市数量从0到 n-1) ，m-道路数量，c1和 c2-你目前所在的城市和你必须保存的城市。下一行包含 n 个整数，其中 i-th 整数表示第 i 城市救援队的数量。然后是 m 线，每条线描述一条有三个整数 c1，c2和 l 的道路，这三个整数分别是由一条道路连接起来的两个城市和这条道路的长度。它保证至少存在一条从 c1到 c2的路径。

### Output Specification:

### 输出规格:

For each test case, print in one line two numbers: the number of different shortest paths between *C*1 and *C*2, and the maximum amount of rescue teams you can possibly gather. All the numbers in a line must be separated by exactly one space, and there is no extra space allowed at the end of a line.

对于每个测试用例，用一行打印两个数字: c1和 c2之间不同的最短路径的数量，以及您可能召集的救援队伍的最大数量。一行中的所有数字必须正好用一个空格隔开，并且在一行的末尾不允许有额外的空格。

### Sample Input:

### 样本输入:

```in
5 6 0 2
1 2 1 5 3
0 1 1
0 2 2
0 3 1
1 2 1
2 4 1
3 4 1
```

### Sample Output:

### 示例输出:

```out
2 4
```

# 理解与算法

城市，道路，路程长度，这几个要素很容易联想到图。

首先我们来定义需要的数据结构：

- 起始节点到其他各个节点的距离数组，dis，当还无法到达某个节点时，就将这个节点的距离设置为无穷远
- 起始节点到其他各个节点的最短路径的数量数组，初始值为0，除了到起始节点本身的路径数量为1
- 起始节点到其他各个节点的能召集的最大救援队数量
- 起始节点到其他各个节点的访问数组，代表是否访问过这个节点

```cpp
vector<vector<int>> edge(N, vector<int>(N, INT_MAX));
// 到i顶点的距离
vector<int> dis(N, INT_MAX);
// c1和 c2之间不同的最短路径的数量
vector<int> roads(N, 0);
// 到i顶点的救援队的数量
vector<int> teams(N, 0);
// 是否访问过i顶点
vector<bool> visit(N, false);
```
因为我们有众多的节点需要遍历，所以不可避免地用到循环，**确定循环前我们需要知道循环条件**，很显然，每个节点至少要访问一次，此处的访问是指访问它的邻接链表，也就是**从该点出发能够到达的其他节点**。

而后我们还要知道**如何找到下一个访问的节点**，图并不是线性的，图是网状结构，没有明确的先后关系，理想状态中，最佳的访问顺序是拓扑序，当一个节点被访问之后就拿掉所有的出边，再去寻找下一个没有入边的节点，理由是这样就不可能出现访问其他节点导致以前的最短路程出现问题。例如下面这个图：

![image-20210121103912807](https://img.tanknee.cn/blogpicbed/2021/01/21/202101214f59f84a7bc11.png)

如果从C1出发，先走C2，再走到C4之类的节点就会导致C1-C2这条边不是最短路程，而出现这个问题的原因就是因为直接走C2它的入度并不为0，而是1，因为C3还可以到C2！

但是维护一个入度数组十分复杂，代价较大，我们可以换一种方式，在遍历完一个节点之后我们选择下一个未被访问过的节点中，路程最近的节点，这个节点有可能不是初始节点的邻接节点，这样做的目的就是不可能从起始节点出发经过其他未访问的节点再到这个节点的路程小于当前的路程！

还是那上面这张图举个例子，C1-C3的距离为2，而C1-C2的距离为4，4 > 2是既定事实，不管怎么走只要经过C2再绕回C3就不可能出现路径更短的情况！

```cpp
for (int j = 0; j < N; j++) {
    // 找出没访问过的顶点中距离最近的点
    if (!visit[j] && dis[j] < minn) {
        u = j;
        minn = dis[j];
    }
}
```

然后我们再来寻找最短路径的最大数量以及救援队的数量。很显然，我们要先找到最短路径，方法就是用Dijkstra算法：遍历当前访问节点的所有邻接节点，如果路程比记录的路程更短，就覆盖原有数据：

```cpp
if (dis[u] + edge[u][v] < dis[v]) {
    dis[v] = dis[u] + edge[u][v];
    // 因为找到了有更短路程的路径，就用新的路径的条数覆盖原有的路径条数
    roads[v] = roads[u];
    teams[v] = teams[u] + weight[v];
}
```

这里的u为当前访问节点，v为u的邻接节点。因为找到了更短的路，所以原本的路径都失效了，现在有效的路径是从u出发到v的路径，而根据题目的描述，两个城市之间只有一条路，所以上面的赋值语句实际含义为：

```cpp
roads[v] = roads[u] * 1;
```

如果有多条路径，那可以把1换成路径的数量。

而当路程等于最短路程时，就相当于新发现了一条路，并且由于每个节点仅仅访问一次，所以不会有重复的问题，不需要考虑去重。

```cpp
else if (dis[u] + edge[u][v] == dis[v]) {
    // 如果v这个点没有被访问过，并且从起始点到v点的距离=从起始点到u再到v的距离
    // 那就是说到相同的目的地，路程一样长，但是走过的路是不一样的，就把这些不同的路和原本的路径的数量相加。
    roads[v] = roads[v] + roads[u];
    if (teams[u] + weight[v] > teams[v]) {
        teams[v] = teams[u] + weight[v];
    }
}
```

因为到下个节点v经过的路径每一条都是完全不同的，所以可以直接相加，并且也是因为俩城市只有一条路，所以实际含义为:

```cpp
roads[v] = roads[v] + roads[u] * 1;
```

如果这个最短路径能够携带的救援队数量比原来的要多，就更新原来的数据，因为最短路径都是一样长的，所以救援队并不需要考虑归属问题，我们只要求数量！

## 代码[^1]

```cpp
#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

int main() {
    //读取第一行数据
    int N, M, C1, C2;
    cin >> N >> M >> C1 >> C2;
    vector<int> weight(N, 0);
    for (int i = 0; i < N; i++) {
        cin >> weight[i];
    }

    vector<vector<int>> edge(N, vector<int>(N, INT_MAX));
    // 到i顶点的距离
    vector<int> dis(N, INT_MAX);
    // c1和 c2之间不同的最短路径的数量
    vector<int> roads(N, 0);
    // 到i顶点的救援队的数量
    vector<int> teams(N, 0);
    // 是否访问过i顶点
    vector<bool> visit(N, false);

    //初始化边权值表
    int c1, c2, L;
    for (int i = 0; i < M; i++) {
        cin >> c1 >> c2 >> L;
        edge[c1][c2] = edge[c2][c1] = L;
    }
    dis[C1] = 0;
    teams[C1] = weight[C1];
    roads[C1] = 1;

    for (int i = 0; i < N; ++i) {
        int u = -1, minn = INT_MAX;
        for (int j = 0; j < N; j++) {
            // 找出没访问过的顶点中距离最近的点
            if (!visit[j] && dis[j] < minn) {
                u = j;
                minn = dis[j];
            }
        }
        if (u == -1) break;
        visit[u] = true;
        for (int v = 0; v < N; v++) {
            // 如果v这个点没有访问过，且u到v是有路径的，那么就有可能刷新最短距离。
            if (!visit[v] && edge[u][v] != INT_MAX) {
                if (dis[u] + edge[u][v] < dis[v]) {
                    dis[v] = dis[u] + edge[u][v];
                  	// 因为找到了有更短路程的路径，就用新的路径的条数覆盖原有的路径条数
                    roads[v] = roads[u];
                    teams[v] = teams[u] + weight[v];
                } else if (dis[u] + edge[u][v] == dis[v]) {
                    // 如果v这个点没有被访问过，并且从起始点到v点的距离=从起始点到u再到v的距离
                    // 那就是说到相同的目的地，路程一样长，但是走过的路是不一样的，就把这些不同的路和原本的路径的数量相加。
                    roads[v] = roads[v] + roads[u];
                    if (teams[u] + weight[v] > teams[v]) {
                        teams[v] = teams[u] + weight[v];
                    }
                }
            }
        }
    }
    cout << roads[C2] << " " << teams[C2] << endl;
    return 0;
}
```

[^1]: https://zhuanlan.zhihu.com/p/138001717