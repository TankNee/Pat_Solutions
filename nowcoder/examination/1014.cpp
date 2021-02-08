//
// Created by tanknee on 2021/2/1.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
vector<vector<int>> nodes(10000, vector<int>());
int depth = 0;

void dfs(int index, int target, int dep) {
    if (index == target) {
        depth = dep;
        return;
    }
    if (nodes[index].size() == 1 && nodes[index][0] < 0) return;
    for (int i = 0; i < nodes[index].size(); ++i) {
        dfs(nodes[index][i], target, dep + 1);
    }
}

int main() {
    int N;
    double price, increase, sum = 0.0;
    cin >> N >> price >> increase;
    for (int i = 0; i < N; ++i) {
        int tmp, tmp_num;
        cin >> tmp;
        for (int j = 0; j < tmp; ++j) {
            cin >> tmp_num;
            nodes[i].push_back(tmp_num);
        }
        if (tmp == 0) {
            cin >> tmp_num;
            nodes[i].push_back(-tmp_num);
        }
    }
    for (int i = 0; i < N; ++i) {
        if (!(nodes[i].size() == 1 && nodes[i][0] < 0)) continue;
        dfs(0, i, 0);
        sum += price * pow((1 + increase / 100.0), depth) * (-nodes[i][0]);
    }
    printf("%.1f", sum);
    return 0;
}