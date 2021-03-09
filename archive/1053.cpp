//
// Created by tanknee on 3/9/2021.
//

#include <bits/stdc++.h>

using namespace std;
vector<int> weights;
vector<vector<int>> matrix, solutions;
long long S;
int N, M, t1, t2, t3;


void dfs(int idx, long long sum, vector<int> solution) {
    solution.push_back(weights[idx]);
    if (matrix[idx].empty()) {
        if (sum == S) {
            solutions.push_back(solution);
        }
        return;
    }
    for (int i = 0; i < matrix[idx].size(); ++i) {
        dfs(matrix[idx][i], sum + weights[matrix[idx][i]], solution);
    }
}

int main() {
    cin >> N >> M >> S;
    weights.resize(N + 1, 0);
    matrix.resize(N + 1, vector<int>{});
    for (int i = 0; i < N; ++i) {
        cin >> weights[i];
    }
    for (int i = 0; i < M; ++i) {
        cin >> t1 >> t2;
        for (int j = 0; j < t2; ++j) {
            cin >> t3;
            matrix[t1].push_back(t3);
        }
    }
    dfs(0, weights[0], {});
    sort(solutions.begin(), solutions.end(), [](const vector<int> &s1, const vector<int> &s2) {
        for (int i = 0; i < min(s1.size(), s2.size()); ++i) {
            if (s1[i] != s2[i]) return s1[i] > s2[i];
        }
        return s1[0] > s2[0];
    });
    for (auto &solution : solutions) {
        for (int j = 0; j < solution.size(); ++j) {
            printf("%d", solution[j]);
            if (j != solution.size() - 1) printf(" ");
        }
        printf("\n");
    }
    return 0;
}