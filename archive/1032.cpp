//
// Created by tanknee on 2/25/2021.
//

#include <bits/stdc++.h>
#include <cstring>

using namespace std;

struct node {
    int next;
    char value;
    bool flag;
};

int main() {
    int head_1, head_2, N, addr;
    cin >> head_1 >> head_2 >> N;
    node nodes[100000];
    for (int i = 0; i < N; ++i) {
        cin >> addr;
        cin >> nodes[addr].value >> nodes[addr].next;
    }
    while (head_2 != -1) {
        nodes[head_2].flag = true;
        head_2 = nodes[head_2].next;
    }
    while (head_1 != -1) {
        if (nodes[head_1].flag) {
            printf("%05d", head_1);
            return 0;
        }
        head_1 = nodes[head_1].next;
    }
    cout << -1;
    return 0;
}