//
// Created by tanknee on 2021/1/26.
//

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int cnt = 0, num, max_depth = 0;
vector<vector<int>> edges(100000, vector<int>());

void dfs(int index, int depth) {
    if (edges[index].empty()) {
        if (depth > max_depth) {
            cnt = 1;
            max_depth = depth;
        } else if (depth == max_depth) {
            cnt++;
        }
    }
    for (int i = 0; i < edges[index].size(); ++i) {
        dfs(edges[index][i], depth + 1);
    }
}

int main() {
    double price, inc;
    cin >> num >> price >> inc;
    for (int i = 1; i < num + 1; ++i) {
        int tmp;
        cin >> tmp;
        edges[tmp + 1].push_back(i);
    }
    dfs(0, 0);
    price = price * pow((1 + inc / 100.0), max_depth - 1);
    printf("%.2f %d", price, cnt);
    return 0;
}