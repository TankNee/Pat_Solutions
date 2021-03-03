//
// Created by tanknee on 3/2/2021.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, max_length = 0;
    cin >> N;
    long long sequence[N], p;
    cin >> p;
    for (int i = 0; i < N; ++i) {
        cin >> sequence[i];
    }
    sort(sequence, sequence + N);
    for (int i = 0; i < N; ++i) {
        int j = i + max_length;
        long long m = sequence[i] * p;
        while (sequence[j] <= m && j < N) j++;
        max_length = max(j - i, max_length);
        if (j >= N) break;
    }
    cout << max_length;
    return 0;
}



