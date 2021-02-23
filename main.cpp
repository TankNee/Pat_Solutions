#include <bits/stdc++.h>

using namespace std;

int main() {
    map<int, vector<int>> m;
    int N, M, K, tmp1, tmp2, flag = 0;
    cin >> N >> M;
    map<int, int> visit_map;
    for (int i = 0; i < N; ++i) {
        cin >> tmp1 >> tmp2;
        m[tmp1].push_back(tmp2);
        m[tmp2].push_back(tmp1);
        visit_map[tmp1] = 1;
        visit_map[tmp2] = 1;
    }
    for (int i = 0; i < M; ++i) {
        cin >> K;
        vector<int> tmp_list(K);
        flag = 0;
        for (int j = 0; j < K; ++j) {
            cin >> tmp_list[j];
        }
        for (int j = 0; j < K; ++j) {
            if (!visit_map[tmp_list[j]]) continue;
            for (int k = 0; k < K; ++k) {
                if (k == j || !visit_map[tmp_list[k]]) continue;
                for (int l = 0; l < m[tmp_list[k]].size(); ++l) {
                    if (m[tmp_list[k]][l] == tmp_list[j]) {
                        flag = 1;
                        cout << "No" << endl;
                        break;
                    }
                }
                if (flag) break;
            }
            if (flag) break;
        }
        if (!flag) {
            cout << "Yes" << endl;
        }
    }
    return 0;
}