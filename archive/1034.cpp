//
// Created by tanknee on 3/11/2021.
//

#include <bits/stdc++.h>

using namespace std;
struct gang {
    int head, cnt;
};

map<string, int> str2idx;
map<int, string> idx2str;
int idx = 0;
int N, K;
vector<vector<int>> matrix(2010, vector<int>(2010));
vector<vector<int>> visit;
vector<int> v_visit;
vector<int> v_weight(2010);

int get_idx(const string &s) {
    if (str2idx.find(s) != str2idx.end()) {
        return str2idx[s];
    } else {
        str2idx[s] = idx;
        idx2str[idx] = s;
        return idx++;
    }
}

void dfs(int cur_idx, int &sum, int &cnt, int &head) {
    if (!v_visit[cur_idx]) {
        v_visit[cur_idx] = 1;
        cnt++;
    }
    if (v_weight[head] < v_weight[cur_idx]) {
        head = cur_idx;
    }
    for (int i = 0; i < N; ++i) {
        if (matrix[cur_idx][i] && !visit[cur_idx][i]) {
            sum += matrix[cur_idx][i];
            visit[cur_idx][i] = visit[i][cur_idx] = 1;
            matrix[cur_idx][i] = matrix[i][cur_idx] = 0;
            dfs(i, sum, cnt, head);
        }
    }
}

int main() {
    string s1, s2;
    int weight;
    vector<gang> gangs;
    cin >> N >> K;
    visit.resize(N, vector<int>(N));
    v_visit.resize(N);
    for (int i = 0; i < N; ++i) {
        cin >> s1 >> s2 >> weight;
        int id1 = get_idx(s1);
        int id2 = get_idx(s2);
        v_weight[id1] += weight;
        v_weight[id2] += weight;
        matrix[id1][id2] += weight;
        matrix[id2][id1] += weight;
    }
    for (int i = 0; i < N; ++i) {
        int sum = 0, cnt = 0, head = i;
        if (!v_visit[i]) {
            dfs(i, sum, cnt, head);
            if (sum > K && cnt > 2) {
                gangs.push_back({head, cnt});
            }
        }
    }
    sort(gangs.begin(), gangs.end(), [](gang g1, gang g2) { return idx2str[g1.head] < idx2str[g2.head]; });
    printf("%d\n", gangs.size());
    for (auto &gang : gangs) {
        printf("%s %d\n", idx2str[gang.head].c_str(), gang.cnt);
    }
    return 0;
}