//
// Created by tanknee on 3/7/2021.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, M, L, tmp;
    cin >> N >> M;
    vector<int> f_colors(201), dp;
    for (int i = 1; i <= M; ++i) {
        cin >> tmp;
        f_colors[tmp] = i;
    }
    cin >> L;
    vector<int> colors;
    for (int i = 0; i < L; ++i) {
        cin >> tmp;
        if (f_colors[tmp]) {
            colors.push_back(tmp);
        }
    }
    dp.resize(colors.size());
    int max_length = -1;
    // 与递归相反，自顶向下更加方便编写代码！
    for (int i = 0; i < colors.size(); ++i) {
        dp[i] = 1;
        for (int j = 0; j < i; ++j) {
            if (f_colors[colors[i]] >= f_colors[colors[j]])
                dp[i] = max(dp[i], dp[j] + 1);
        }
        max_length = max(max_length, dp[i]);
    }
    printf("%d", max_length);
    return 0;
}