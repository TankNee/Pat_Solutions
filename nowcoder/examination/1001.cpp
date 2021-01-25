//
// Created by tanknee on 2021/1/25.
//

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