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