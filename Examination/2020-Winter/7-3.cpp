//
// Created by tanknee on 3/7/2021.
//

#include <bits/stdc++.h>

using namespace std;

struct node {
    int id, level;
    vector<node *> children;
};

int count_space(const string &str) {
    int count = 0;
    for (char i : str) {
        if (i == ' ') count++;
    }
    return count;
}

vector<int> search_routine(int id, node *root, vector<int> routine) {
    if (root->id == id) {
        routine.push_back(id);
        return routine;
    } else if (root->children.empty()) {
        return {};
    }
    routine.push_back(root->id);
    for (auto &i : root->children) {
        auto tmp = search_routine(id, i, routine);
        if (!tmp.empty()) return tmp;
    }
    return {};
}

int main() {
    int N, K, tmp_num;
    scanf("%d\n", &N);
    string tmp;
    node *root;
    for (int i = 0; i < N; ++i) {
        getline(cin, tmp);
        int cnt = count_space(tmp);
        node *n = new node{stoi(tmp), cnt};
        if (!cnt) {
            root = n;
            continue;
        }
        node *tmp_root = root;
        while (tmp_root->level != cnt - 1) {
            tmp_root = tmp_root->children.back();
        }
        tmp_root->children.push_back(n);
    }
    cin >> K;
    for (int i = 0; i < K; ++i) {
        cin >> tmp_num;
        vector<int> routine;
        routine = search_routine(tmp_num, root, {});
        if (routine.empty()) {
            printf("Error: %04d is not found.\n", tmp_num);
        } else {
            for (int j = 0; j < routine.size(); ++j) {
                printf("%04d", routine[j]);
                if (j != routine.size() - 1) printf("->");
            }
            printf("\n");
        }
    }
    return 0;
}