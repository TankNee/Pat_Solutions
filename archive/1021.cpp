//
// Created by tanknee on 2/15/2021.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
int max_depth = 0, N, visit[10001];
vector<vector<int>> edges;
vector<int> roots;

void dfs(int root, int index, int depth) {
    bool flag = false;
    visit[index] = 1;
    for (int i = 0; i < edges[index].size(); ++i) {
        if (!visit[edges[index][i]]) {
            dfs(root, edges[index][i], depth + 1);
            flag = true;
        }
    }
    if (!flag) {
        if (max_depth < depth) {
            roots.clear();
            roots.push_back(root);
            max_depth = depth;
        } else if (max_depth == depth && !roots.empty() && roots.back() != root) {
            roots.push_back(root);
        }
    }
}

int check_connection() {
    int count = 1;
    for (int i = 1; i < N + 1; ++i) {
        if (!visit[i]) {
            dfs(i, i, 0);
            count++;
        }
    }
    return count;
}

int main() {
    int t1, t2;
    cin >> N;
    if (N == 1) {
        cin >> t1;
        cout << 1 << endl;
        return 0;
    }
    edges.resize(N + 1);
    for (int i = 1; i < N; ++i) {
        cin >> t1 >> t2;
        edges[t1].push_back(t2);
        edges[t2].push_back(t1);
    }
    int res = 0;
    for (int i = 1; i < N + 1; ++i) {
        if (!visit[i]) {
            dfs(i, i, 0);
            if (res == 0) {
                res = check_connection();
                if (res != 1) {
                    printf("Error: %d components", res);
                    return 0;
                }
            }
            fill(visit, visit + N + 1, 0);
        }
    }
    for (int root : roots) {
        cout << root << endl;
    }
    return 0;
}