//
// Created by tanknee on 3/8/2021.
//

#include <bits/stdc++.h>

using namespace std;
vector<int> nodes, post, mirror_post;

bool valid(int left, int right) {
    if (left == right) {
        post.push_back(nodes[left]);
        return true;
    }
    int right_child_root = left + 1;
    while (nodes[right_child_root] < nodes[left] && right_child_root <= right) right_child_root++;
    for (int i = right_child_root; i <= right; ++i) {
        if (nodes[left] > nodes[i]) {
            return false;
        }
    }
    bool flag = true;
    if (left + 1 < right_child_root) {
        flag = valid(left + 1, right_child_root - 1);
    }
    if (right >= right_child_root) {
        flag = flag && valid(right_child_root, right);
    }
    post.push_back(nodes[left]);
    return flag;
}

bool mirror_valid(int left, int right) {
    if (left >= right) {
        mirror_post.push_back(nodes[left]);
        return true;
    }
    int right_child_root = left + 1;
    while (nodes[right_child_root] >= nodes[left] && right_child_root <= right) right_child_root++;
    for (int i = right_child_root; i <= right; ++i) {
        if (nodes[left] <= nodes[i]) {
            return false;
        }
    }bool flag = true;
    if (left + 1 < right_child_root) {
        flag = mirror_valid(left + 1, right_child_root - 1);
    }
    if (right >= right_child_root) {
        flag = flag && mirror_valid(right_child_root, right);
    }
    mirror_post.push_back(nodes[left]);
    return flag;
}

int main() {
    int N;
    bool flag1, flag2;
    cin >> N;
    nodes.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> nodes[i];
    }
    flag1 = valid(0, N - 1);
    if (!flag1)
        flag2 = mirror_valid(0, N - 1);
    if (!(flag1 || flag2)) cout << "NO";
    else {
        printf("YES\n");
        if (flag1) {
            for (int i = 0; i < N; ++i) {
                printf("%d", post[i]);
                if (i != N - 1) printf(" ");
            }
        } else {
            for (int i = 0; i < N; ++i) {
                printf("%d", mirror_post[i]);
                if (i != N - 1) printf(" ");
            }
        }
    }
    return 0;
}