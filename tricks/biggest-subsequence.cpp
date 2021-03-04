//
// Created by tanknee on 3/4/2021.
//

// 最大连续子序列和

#include <iostream>

using namespace std;

int main() {
    int N;
    cin >> N;
    int sequence[N], dp[N];
    for (int i = 0; i < N; ++i) {
        cin >> sequence[i];
    }
    // 设置边界条件
    dp[0] = sequence[0];
    for (int i = 1; i < N; ++i) {
        dp[i] = max(sequence[i], dp[i - 1] + sequence[i]);
    }
    int max_num = dp[0];
    for (int i = 1; i < N; ++i) {
        if (dp[i] > max_num) {
            max_num = dp[i];
        }
    }
    printf("%d", max_num);
    return 0;
}