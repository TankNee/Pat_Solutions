//
// Created by tanknee on 2021/2/14.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
vector<int> post_order, in_order;
map<int, int> level;

void pre(int root, int start, int end, int index) {
    if (start > end) return;
    int i = start;
    while (i < end && in_order[i] != post_order[root]) i++;
    level[index] = post_order[root];
    pre(root - 1 - end + i, start, i - 1, 2 * index + 1);
    pre(root - 1, i + 1, end, 2 * index + 2);
}

int main() {
    int N;
    cin >> N;
    post_order.resize(N);
    in_order.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> post_order[i];
    }
    for (int i = 0; i < N; ++i) {
        cin >> in_order[i];
    }
    pre(N - 1, 0, N - 1, 0);
    auto it = level.begin();
    printf("%d", it->second);
    while(++it != level.end()) printf(" %d", it->second);
    return 0;
}