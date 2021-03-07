//
// Created by tanknee on 3/7/2021.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    map<string, vector<int>> m;
    string tmp;
    for (int i = 0; i < K; ++i) {
        int course_idx, stu_num;
        cin >> course_idx >> stu_num;
        for (int j = 0; j < stu_num; ++j) {
            cin >> tmp;
            m[tmp].push_back(course_idx);
        }
    }
    for (int i = 0; i < N; ++i) {
        cin >> tmp;
        printf("%s %d", tmp.c_str(), m[tmp].size());
        sort(m[tmp].begin(), m[tmp].end());
        for (int j = 0; j < m[tmp].size(); ++j) {
            printf(" %d", m[tmp][j]);
        }
        printf("\n");
    }
    return 0;
}