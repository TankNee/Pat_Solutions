//
// Created by tanknee on 3/12/2021.
//

#include <bits/stdc++.h>

using namespace std;
int N;
vector<int> seq, level_count;

struct node {
    int key;
    node *left, *right;

    node() {
        key = -1;
        left = right = nullptr;
    }
};

void build_cbt(node *root) {
    int tmp = N - 1;
    queue<node *> q;
    q.push(root);
    while (tmp > 0) {
        if (tmp > 1) {
            tmp -= 2;
            q.front()->left = new node;
            q.push(q.front()->left);
            q.front()->right = new node;
            q.push(q.front()->right);
            q.pop();
        } else if (tmp == 1) {
            tmp--;
            q.front()->left = new node;
            q.push(q.front()->left);
        }
    }
}

bool insert_val(node *root, int val) {
    if (!root) return false;
    if (!root->left && !root->right && root->key != -1) {
        return false;
    }
    if (root->left) {
        if (insert_val(root->left, val)) return true;
    }
    if (root->key == -1) {
        root->key = val;
        return true;
    }
    return insert_val(root->right, val);
}

int main() {
    cin >> N;
    node *root = new node;
    build_cbt(root);
    seq.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> seq[i];
    }
    sort(seq.begin(), seq.end());
    for (int i = 0; i < N; ++i) {
        insert_val(root, seq[i]);
    }
    queue<node *> q;
    q.push(root);
    if (q.front()->left) {
        q.push(q.front()->left);
    }
    if (q.front()->right) {
        q.push(q.front()->right);
    }
    q.pop();
    printf("%d", root->key);
    while (!q.empty()) {
        if (q.front()->left) {
            q.push(q.front()->left);
        }
        if (q.front()->right) {
            q.push(q.front()->right);
        }
        printf(" %d", q.front()->key);
        q.pop();
    }
    return 0;
}