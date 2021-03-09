//
// Created by tanknee on 3/9/2021.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    vector<int> coins(N);
    for (int i = 0; i < N; ++i) {
        cin >> coins[i];
    }
    sort(coins.begin(), coins.end());
    if (N < 1000) {
        for (int i = 0; i < N; ++i) {
            for (int j = i + 1; j < N; ++j) {
                if (coins[i] + coins[j] == M) {
                    printf("%d %d", coins[i], coins[j]);
                    return 0;
                }
            }
        }
        printf("No Solution");
        return 0;
    }
    int i = 0, j = N - 1;
    while (i < j) {
        while (coins[i] + coins[j] > M) j--;
        if (coins[i] + coins[j] == M) {
            printf("%d %d", coins[i], coins[j]);
            return 0;
        }
        while (coins[i] + coins[j] < M) i++;
        if (coins[i] + coins[j] == M) {
            printf("%d %d", coins[i], coins[j]);
            return 0;
        }
    }
    printf("No Solution");
    return 0;
}
