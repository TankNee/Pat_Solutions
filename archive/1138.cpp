//
// Created by tanknee on 3/2/2021.
//

#include <bits/stdc++.h>

using namespace std;
vector<int> pre, in;
int flag = 0;

int find_in_index(int v, int left, int right) {
    for (int i = left; i <= right; ++i) {
        if (in[i] == v) return i;
    }
    return -1;
}

void traversal(int pre_root, int in_root, int pre_left, int in_left, int pre_right, int in_right) {
    if (in_right - in_left == 0) {
        cout << in[in_right];
        flag = 1;
        return;
    }
    if (in_root - in_left > 0) {
        int new_in_root = find_in_index(pre[pre_root + 1], in_left, in_root);
        traversal(pre_root + 1, new_in_root, pre_left + 1, in_left, pre_left + in_root - in_left, in_root - 1);
        return;
    }
    if (in_right - in_root > 0) {
        int new_in_root = find_in_index(pre[pre_root + 1], in_root, in_right);
        traversal(pre_root + 1, new_in_root, pre_left + 1, in_left + 1, pre_right, in_right);
        return;
    }
}


int main() {
    int N;
    cin >> N;
    pre.resize(N);
    in.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> pre[i];
    }
    for (int i = 0; i < N; ++i) {
        cin >> in[i];
    }
    int in_root = find_in_index(pre[0], 0, N);
    traversal(0, in_root, 0, 0, N - 1, N - 1);
    return 0;
}

