# 题目

## 1013 Battle Over Cities (25分)

It is vitally important to have all the cities connected by highways in a war. If a city is occupied by the enemy, all the highways from/toward that city are closed. We must know immediately if we need to repair any other highways to keep the rest of the cities connected. Given the map of cities which have all the remaining highways marked, you are supposed to tell the number of highways need to be repaired, quickly.

For example, if we have 3 cities and 2 highways connecting *c**i**t**y*1-*c**i**t**y*2 and *c**i**t**y*1-*c**i**t**y*3. Then if *c**i**t**y*1 is occupied by the enemy, we must have 1 highway repaired, that is the highway *c**i**t**y*2-*c**i**t**y*3.

### Input Specification:

Each input file contains one test case. Each case starts with a line containing 3 numbers *N* (<1000), *M* and *K*, which are the total number of cities, the number of remaining highways, and the number of cities to be checked, respectively. Then *M* lines follow, each describes a highway by 2 integers, which are the numbers of the cities the highway connects. The cities are numbered from 1 to *N*. Finally there is a line containing *K* numbers, which represent the cities we concern.

### Output Specification:

For each of the *K* cities, output in a line the number of highways need to be repaired if that city is lost.

### Sample Input:

```in
3 2 3
1 2
1 3
1 2 3
```

### Sample Output:

```out
1
0
0
```

# 理解与算法

又是一道关于图的问题，这道题考的是连通性！

在去掉一个点之后，剩下的图是否是连通的，如果是连通的那么就不需要修道路，如果在经过一次搜索之后仍然未被访问，那就说明这个点不在上一个点的访问图中，所以要修一条路到这个点。

需要修路的情况：

![image-20210125151302786](https://img.tanknee.cn/blogpicbed/2021/01/25/202101252ec9faa92f37f.png)

不需要修路的情况：

![image-20210125151222055](https://img.tanknee.cn/blogpicbed/2021/01/25/20210125ec7e0934e8f36.png)

> 忽略点之间的箭头，这道题不是有向图，**是无向图。**

做这道题的时候发现深度优先搜索真的是非常常用的一种算法，不管是找最短路径，还是求图的连通性，都会用到，应该算是比较常见的一种图的遍历方法了吧。

下面给一个dfs的模板，方便以后参考：

```c++
int highways[1001][1001], n;
bool visited[1001];

void dfs(int city_id) {
  	// 搜索到这个点，就代表我们将要访问他了
    visited[city_id] = true;
    for (int i = 1; i <= n; ++i) {
        // 不搜索已经访问过的点以及没有边到达的点，提高搜索效率。
        if (!visited[i] && highways[city_id][i]) {
            dfs(i);
        }
    }
}
```

写题目的时候经常会被情景绕进去，比如这道题说被占领的城市要关掉所有的公路，难道我们要操作邻接矩阵，将这个城市到所有顶点的边都设置为0吗，不是的，我们只需要跳过这个点就够了，怎么跳过，将他标记为已访问，当然这里的标记并不一定是通用的，可能有很多不同的办法。

## 代码与实现[^1]

```c++
//
// Created by tanknee on 2021/1/25.
//

#include <iostream>

using namespace std;
int highways[1001][1001], n;
bool visited[1001];

void dfs(int city_id) {
    visited[city_id] = true;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i] && highways[city_id][i]) {
            dfs(i);
        }
    }
}

int main() {
    int m, k, c1, c2;
    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) {
        cin >> c1 >> c2;
        // 非有向图，应该要输入两条边，否则会出错！
        highways[c1][c2] = highways[c2][c1] = 1;
    }
    for (int i = 0; i < k; ++i) {
        fill(visited, visited + n + 1, false);
        int count = 0;
        cin >> c1;
        // 下面这么写的目的是，从一个城市出发，能否到达其他所有的城市
        // 其实我们不用考虑被敌人占领的城市！或者说，我们只要遵循不以这个被占领的城市为起点出发前往其他城市就行！
        // 所以我们直接将被占领的城市标记为已访问。
        visited[c1] = true;
        for (int j = 1; j <= n; ++j) {
            // 如果之后的城市中有的城市仍然是未访问的状态，那么说明这个点与前面的点并不相通，所以至少要修一条路到这个城市
            if (!visited[j]) {
                dfs(j);
                count++;
            }
        }
        // 由于我们不知道第一个城市是否被访问过，所以为了普适性，都加上1！如果访问的第一个城市就能走到其他所有的城市，那么就说明这个图是联通的！
        cout << count - 1 << endl;
    }

    return 0;
}
```

[^1]: https://github.com/liuchuo/PAT