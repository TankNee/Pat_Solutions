//
// Created by tanknee on 3/4/2021.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, count = 0;
    cin >> N;
    vector<int> sequence(N), backup(N);
    map<int, int> idx_map;
    for (int i = 0; i < N; ++i) {
        cin >> sequence[i];
        backup[i] = sequence[i];
    }
    sort(backup.begin(), backup.end());
    for (int i = 0; i < N; ++i) {
        idx_map[backup[i]] = i;
    }
    for (int i = 0; i < N; ++i) {
        int target_idx = idx_map[sequence[i]];
        if (target_idx == i) continue;
        count++;
        swap(sequence[i], sequence[target_idx]);
    }
    for (int i = 0; i < N; ++i) {
        int target_idx = idx_map[sequence[i]];
        if (target_idx == i) continue;
        count++;
        swap(sequence[i], sequence[target_idx]);
    }
    cout << count;
    return 0;
}