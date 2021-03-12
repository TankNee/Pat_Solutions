//
// Created by tanknee on 3/12/2021.
//

#include <bits/stdc++.h>

using namespace std;

struct node {
    int address, key, next;
};

int main() {
    int N, head, a, k, n;
    cin >> N >> head;
    vector<node> nodes(N), tmp_nodes;
    int m_map[100010];
    for (int i = 0; i < N; ++i) {
        cin >> a >> k >> n;
        nodes[i].address = a;
        nodes[i].key = k;
        nodes[i].next = n;
        m_map[a] = i;
    }
    while (head != -1) {
        tmp_nodes.push_back(nodes[m_map[head]]);
        if (nodes[m_map[head]].next == -1) break;
        head = nodes[m_map[head]].next;
    }
    sort(tmp_nodes.begin(), tmp_nodes.end(), [](node n1, node n2) {
        return n1.key < n2.key;
    });
    if (tmp_nodes.empty()) {
        printf("%d -1\n", tmp_nodes.size());
        return 0;
    }
    printf("%d %05d\n", tmp_nodes.size(), tmp_nodes[0].address);
    for (int i = 0; i < tmp_nodes.size(); ++i) {
        printf("%05d %d ", tmp_nodes[i].address, tmp_nodes[i].key);
        if (i != tmp_nodes.size() - 1) {
            printf("%05d\n", tmp_nodes[i + 1].address);
        } else {
            printf("-1");
        }
    }
    return 0;
}