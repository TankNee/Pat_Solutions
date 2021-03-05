#include <bits/stdc++.h>

using namespace std;

struct node {
    string val;
    int left, right;

    node() {
        left = right = -1;
    }
};

vector<node> nodes;
string res;

void in_order(int root) {
    if (nodes[root].left != -1 && nodes[root].right != -1)
        res.append("(");
    if (nodes[root].left != -1) in_order(nodes[root].left);
    if (nodes[root].val == "-" && nodes[root].left == -1) {
        res.append("(");
    }
    res.append(nodes[root].val);
    if (nodes[root].right != -1) in_order(nodes[root].right);
    if (nodes[root].val == "-" && nodes[root].left == -1) {
        res.append(")");
    }
    if (nodes[root].left != -1 && nodes[root].right != -1)
        res.append(")");
}

int main() {
    int N;
    cin >> N;
    nodes.resize(N + 1, node{});
    for (int i = 1; i <= N; ++i) {
        cin >> nodes[i].val >> nodes[i].left >> nodes[i].right;
    }
    int root = 1;
    for (int i = 1; i <= N; ++i) {
        bool flag = false;
        for (int j = 1; j <= N; ++j) {
            if (nodes[j].left == i || nodes[j].right == i) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            root = i;
            break;
        }
    }
    in_order(root);
    res.erase(res.begin());
    res.erase(res.end() - 1);
    cout << res;

    return 0;
}