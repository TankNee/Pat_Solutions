//
// Created by tanknee on 2021/1/30.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
struct node {
    int user_id, depth;
};

int main() {
    int N, L, K;
    cin >> N >> L;
    vector<vector<int>> users(N + 1, vector<int>());
    for (int i = 1; i <= N; ++i) {
        int tmp, tmp_user;
        cin >> tmp;
        for (int j = 0; j < tmp; ++j) {
            cin >> tmp_user;
            users[tmp_user].push_back(i);
        }
    }
    cin >> K;
    int tmp, visit[N + 1], depth = 0, cur_user, count = 0;
    queue<node> q;
    for (int i = 0; i < K; ++i) {
        cin >> tmp;
        count = 0;
        depth = 0;
        fill(visit, visit + N + 1, 0);
        visit[tmp] = 1;
        for (int j = 0; j < q.size(); ++j) {
            q.pop();
        }
        for (int j = 0; j < users[tmp].size(); ++j) {
            node n;
            n.user_id = users[tmp][j];
            n.depth = 0;
            q.push(n);
        }
        while (!q.empty() && depth < L) {
            cur_user = q.front().user_id;
            depth = q.front().depth;
            q.pop();
            if (visit[cur_user]) continue;
            visit[cur_user] = 1;
            count++;
            for (int j = 0; j < users[cur_user].size() && depth + 1 < L; ++j) {
                node n;
                n.user_id = users[cur_user][j];
                n.depth = depth + 1;
                q.push(n);
            }
        }
        cout << count << endl;
    }

    return 0;
}