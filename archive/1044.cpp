//
// Created by tanknee on 3/8/2021.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, M, min_gap = INT_MAX;
    bool flag = false, f = false;
    cin >> N >> M;
    int diamonds[N + 1];
    map<int, int> m;
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &diamonds[i]);
    }
    for (int i = 1; i <= N; ++i) {
        int sum = diamonds[i], j = i + 1;
        while (sum < M && j <= N) {
            sum += diamonds[j++];
        }
        if (j > N && sum < M) {
            if (!f) {
                f = true;
                continue;
            } else break;
        }
        if (sum == M) {
            flag = true;
            printf("%d-%d\n", i, j - 1);
        } else if (!flag && sum > M) {
            if (min_gap > sum - M) {
                min_gap = sum - M;
                m.clear();
                m[i] = j - 1;
            } else if (min_gap == sum - M) {
                m[i] = j - 1;
            }
        }
    }
    if (!flag) {
        for (auto &it : m) {
            printf("%d-%d\n", it.first, it.second);
        }
    }
    return 0;
}