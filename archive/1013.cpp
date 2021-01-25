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