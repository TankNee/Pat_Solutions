//
// Created by tanknee on 2021/1/27.
//

#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct node {
    int address;
    int value;
    int next;

    bool operator=(node n) const {
        return address == n.address;
    }

    bool operator<(node n) const {
        return address < n.address;
    }
};

int main() {
    int head_address, N;
    cin >> head_address >> N;
    vector<node> nodes, re_nodes, rm_nodes;
    node head;
    set<node> s;
    set<int> k;
    for (int i = 0; i < N; ++i) {
        node n{};
        cin >> n.address >> n.value >> n.next;
        s.insert(n);
        if (n.address == head_address) {
            head.address = n.address;
            head.next = n.next;
            head.value = n.value;
        }
    }
    node n;
    n.address = head.next;
    nodes.push_back(head);
    for (int i = 1; i < N; ++i) {
        auto it = s.find(n);
        nodes.push_back((*it));
        n.address = (*it).next;
    }
    for (int i = 0; i < nodes.size(); ++i) {
        if (k.count(abs(nodes[i].value))) {
            re_nodes.rbegin()->next = nodes[i].next;
            nodes[i].next = -1;
            if (rm_nodes.size() != 0) {
                rm_nodes.rbegin()->next = nodes[i].address;
            }
            rm_nodes.push_back(nodes[i]);
        } else {
            k.insert(abs(nodes[i].value));
            re_nodes.push_back(nodes[i]);
        }
    }
    for (int i = 0; i < re_nodes.size(); ++i) {
        if (re_nodes[i].next != -1)
            printf("%05d %d %05d\n", re_nodes[i].address, re_nodes[i].value, re_nodes[i].next);
        else
            printf("%05d %d %d\n", re_nodes[i].address, re_nodes[i].value, re_nodes[i].next);
    }
    for (int i = 0; i < rm_nodes.size(); ++i) {
        if (rm_nodes[i].next != -1)
            printf("%05d %d %05d\n", rm_nodes[i].address, rm_nodes[i].value, rm_nodes[i].next);
        else
            printf("%05d %d %d\n", rm_nodes[i].address, rm_nodes[i].value, rm_nodes[i].next);
    }
    return 0;
}