//
// Created by tanknee on 2021/1/23.
//

#include <iostream>
#include <vector>
#include <climits>

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