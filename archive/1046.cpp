//
// Created by tanknee on 3/9/2021.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, M, t1, t2, total = 0, sum = 0;
    cin >> N;
    vector<int> dis(N + 1), tmp_list(N + 1), reverse(N + 1);
    for (int i = 1; i <= N; ++i) {
        cin >> dis[i];
        total += dis[i];
    }
    for (int i = 2; i <= N; ++i) {
        if (reverse[i - 1] == 0) {
            if (tmp_list[i - 1] + dis[i - 1] <= total - (tmp_list[i - 1] + dis[i - 1])) {
                tmp_list[i] = tmp_list[i - 1] + dis[i - 1];
            } else {
                tmp_list[i] = total - (tmp_list[i - 1] + dis[i - 1]);
                reverse[i] = 1;
            }
        } else {
            if (tmp_list[i - 1] - dis[i - 1] <= total - (tmp_list[i - 1] - dis[i - 1])) {
                tmp_list[i] = tmp_list[i - 1] - dis[i - 1];
                reverse[i] = 1;
            } else {
                tmp_list[i] = total - (tmp_list[i - 1] - dis[i - 1]);
            }
        }
    }
    cin >> M;
    map<int, int> m;
    for (int i = 0; i < M; ++i) {
        cin >> t1 >> t2;
        if (t1 > t2) swap(t1, t2);
        if ((reverse[t1] && reverse[t2]) || (!reverse[t1] && !reverse[t2])) {
            printf("%d\n", min(abs(tmp_list[t2] - tmp_list[t1]), total - abs(tmp_list[t2] - tmp_list[t1])));
        } else {
            printf("%d\n", min(abs(tmp_list[t2] + tmp_list[t1]), total - abs(tmp_list[t2] + tmp_list[t1])));
        }
    }

    return 0;
}
