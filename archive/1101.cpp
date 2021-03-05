//
// Created by tanknee on 3/4/2021.
//

#include <bits/stdc++.h>

using namespace std;

struct bundle {
    int max_num, min_num;
};


int main() {
    int N;
    cin >> N;
    vector<int> sequence(N);
    for (int i = 0; i < N; ++i) {
        cin >> sequence[i];
    }
    map<int, bundle> m;
    m[0] = bundle{sequence[0], INT_MAX};
    m[N - 1] = bundle{-1, sequence[N - 1]};
    for (int i = 1; i < N; ++i) {
        if (sequence[i] > m[i - 1].max_num) m[i].max_num = sequence[i];
        else m[i].max_num = m[i - 1].max_num;
    }
    for (int i = N - 2; i >= 0; --i) {
        if (sequence[i] < m[i + 1].min_num) m[i].min_num = sequence[i];
        else m[i].min_num = m[i + 1].min_num;
    }
    vector<int> res;
    for (int i = 0; i < N; ++i) {
        if (i == 0) {
            if (N == 1 || m[i + 1].min_num > sequence[i]) {
                res.push_back(sequence[i]);
            }
            continue;
        }
        if (i == N - 1) {
            if (m[i - 1].max_num < sequence[i]) res.push_back(sequence[i]);
            continue;
        }
        if (m[i - 1].max_num < sequence[i] && m[i + 1].min_num > sequence[i]) {
            res.push_back(sequence[i]);
        }
    }
    sort(res.begin(), res.end());
    if (res.empty()) {
        printf("0\n\n");
        return 0;
    }
    printf("%d\n", res.size());
    for (int i = 0; i < res.size(); ++i) {
        printf("%d", res[i]);
        if (i != res.size() - 1) printf(" ");
    }

    return 0;
}