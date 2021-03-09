//
// Created by tanknee on 3/9/2021.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
    int N, K, tmp, tmp_course;
    string name;
    cin >> N >> K;
    vector<vector<string>> course_list(K + 1, vector<string>{});
    for (int i = 0; i < N; ++i) {
        cin >> name >> tmp;
        for (int j = 0; j < tmp; ++j) {
            cin >> tmp_course;
            course_list[tmp_course].push_back(name);
        }
    }
    for (int i = 1; i <= K; ++i) {
        printf("%d %d\n", i, course_list[i].size());
        sort(course_list[i].begin(), course_list[i].end(), [](string n1, string n2) { return n1 < n2; });
        for (int j = 0; j < course_list[i].size(); ++j) {
            printf("%s\n", course_list[i][j].c_str());
        }
    }
    return 0;
}
