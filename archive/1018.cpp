//
// Created by tanknee on 3/11/2021.
//


#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
const int inf = 99999999;
int cmax, n, sp, m;
int minNeed = inf, minBack = inf;
int e[510][510], dis[510], weight[510];
bool visit[510];
vector<int> pre[510], path, temppath;

void dfs(int v) {
    temppath.push_back(v);
    if (v == 0) {
        int need = 0, back = 0;
        for (int i = temppath.size() - 1; i >= 0; i--) {
            int id = temppath[i];
            if (weight[id] > 0) {
                back += weight[id];
            } else {
                if (back > (0 - weight[id])) {
                    back += weight[id];
                } else {
                    need += ((0 - weight[id]) - back);
                    back = 0;
                }
            }
        }
        if (need < minNeed) {
            minNeed = need;
            minBack = back;
            path = temppath;
        } else if (need == minNeed && back < minBack) {
            minBack = back;
            path = temppath;
        }
        temppath.pop_back();
        return;
    }
    for (int i = 0; i < pre[v].size(); i++)
        dfs(pre[v][i]);
    temppath.pop_back();
}

int main() {
    fill(e[0], e[0] + 510 * 510, inf);
    fill(dis, dis + 510, inf);
    scanf("%d%d%d%d", &cmax, &n, &sp, &m);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &weight[i]);
        weight[i] = weight[i] - cmax / 2;
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        scanf("%d", &e[a][b]);
        e[b][a] = e[a][b];
    }
    dis[0] = 0;
    for (int i = 0; i <= n; i++) {
        int u = -1, minn = inf;
        for (int j = 0; j <= n; j++) {
            if (visit[j] == false && dis[j] < minn) {
                u = j;
                minn = dis[j];
            }
        }
        if (u == -1) break;
        visit[u] = true;
        for (int v = 0; v <= n; v++) {
            if (visit[v] == false && e[u][v] != inf) {3
                if (dis[v] > dis[u] + e[u][v]) {
                    dis[v] = dis[u] + e[u][v];
                    pre[v].clear();
                    pre[v].push_back(u);
                } else if (dis[v] == dis[u] + e[u][v]) {
                    pre[v].push_back(u);
                }
            }
        }
    }
    dfs(sp);
    printf("%d 0", minNeed);
    for (int i = path.size() - 2; i >= 0; i--)
        printf("->%d", path[i]);
    printf(" %d", minBack);
    return 0;
}

//#include <bits/stdc++.h>
//
//using namespace std;
//
//int stations[501], graph[501][501];
//int capacity, N, Sp, M, t1, t2, tmp;
//
//int get_sent(const vector<int> &routine) {
//    int sent = 0, max_sent = 0;
//    for (int i = 1; i < routine.size(); ++i) {
//        sent += (capacity / 2) - stations[routine[i]];
//        max_sent = max(max_sent, sent);
//    }
//    if (max_sent < 0) return 0;
//    return max_sent;
//}
//
//int get_back(const vector<int> &routine, int init) {
//    int tmp_back = 0;
//    for (int i = 1; i < routine.size(); ++i) {
//        tmp_back += (capacity / 2) - stations[routine[i]];
//    }
//    return init - tmp_back;
//}
//
//void get_sent_and_back(const vector<int> &a, int &sent, int &back) {
//    sent = back = 0;
//    int standard = capacity / 2;
//    for (int i = 1; i < a.size(); i++) {
//        if (stations[a[i]] > standard) back += stations[a[i]] - standard;
//        else if (stations[a[i]] < standard) {
//            if (standard - stations[a[i]] - back >= 0) {
//                sent += standard - stations[a[i]] - back;
//                back = 0;
//            } else {
//                back -= standard - stations[a[i]];
//            }
//        }
//    }
//}
//
//int main() {
//    bool visit[501] = {false};
//    cin >> capacity >> N >> Sp >> M;
//    int dis[N + 1], final_sent, final_back;
//    vector<vector<int>> routines(N + 1, vector<int>{});
//    fill(dis, dis + N + 1, INT_MAX);
//    for (int i = 1; i <= N; ++i) {
//        cin >> stations[i];
//    }
//    for (int i = 0; i < M; ++i) {
//        cin >> t1 >> t2 >> tmp;
//        graph[t1][t2] = tmp;
//        graph[t2][t1] = tmp;
//    }
//    dis[0] = 0;
//    routines[0].push_back(0);
//    for (int i = 0; i < N; ++i) {
//        int u = -1, min_dis = INT_MAX;
//        for (int j = 0; j < N; ++j) {
//            if (dis[j] < min_dis && !visit[j]) {
//                min_dis = dis[j];
//                u = j;
//            }
//        }
//        if (u == -1) break;
//        visit[u] = true;
//        for (int j = 1; j <= N; ++j) {
//            if (!visit[j] && graph[u][j]) {
//                if (dis[u] + graph[u][j] < dis[j]) {
//                    dis[j] = dis[u] + graph[u][j];
//                    routines[j].clear();
//                    for (int k = 0; k < routines[u].size(); ++k) {
//                        routines[j].push_back(routines[u][k]);
//                    }
//                    routines[j].push_back(j);
//                    if (j == Sp) {
//                        get_sent_and_back(routines[j], final_sent, final_back);
//                    }
//                } else if (dis[u] + graph[u][j] == dis[j] && j == Sp) {
//                    int origin_sent, origin_back;
//                    get_sent_and_back(routines[j], origin_sent, origin_back);
//                    routines[u].push_back(j);
//                    int new_sent, new_back;
//                    get_sent_and_back(routines[u], new_sent, new_back);
//                    if (new_sent < origin_sent) {
//                        routines[j] = routines[u];
//                        final_sent = new_sent;
//                        final_back = new_back;
//                    } else if (new_sent == origin_sent && new_back < origin_back) {
//                        routines[j] = routines[u];
//                        final_sent = new_sent;
//                        final_back = new_back;
//                    } else
//                        routines[u].pop_back();
//                }
//            }
//        }
//    }
//    printf("%d ", final_sent);
//    for (int i = 0; i < routines[Sp].size(); ++i) {
//        printf("%d", routines[Sp][i]);
//        if (i != routines[Sp].size() - 1) printf("->");
//    }
//    printf(" %d", final_back);
//    return 0;
//};