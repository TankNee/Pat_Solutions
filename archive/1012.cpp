//
// Created by tanknee on 2021/1/25.
//

#include <iostream>
#include <algorithm>

using namespace std;

struct student {
    int id;
    int score[4];
    int rank[4];
    int best;
};
student students[2001];

int exists[1000001], flag = -1;

bool cmp1(student a, student b) { return a.score[flag] > b.score[flag]; }

int main() {
    int N, M, id;
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        cin >> students[i].id >> students[i].score[1] >> students[i].score[2] >> students[i].score[3];
        students[i].score[0] = (students[i].score[1] + students[i].score[2] + students[i].score[3]) / 3.0 + 0.5;
    }
    // 计算学生每门课程的排名
    for (flag = 0; flag <= 3; flag++) {
        sort(students, students + N, cmp1);
        students[0].rank[flag] = 1;
        for (int i = 1; i < N; ++i) {
            students[i].rank[flag] = i + 1;
            // 如果分数相同，那么排名也跟之前的一样
            if (students[i].score[flag] == students[i - 1].score[flag]) {
                students[i].rank[flag] = students[i - 1].rank[flag];
            }
        }
    }
    // 计算每个学生的最好排名
    for (int i = 0; i < N; ++i) {
        exists[students[i].id] = i + 1;
        students[i].best = 0;
        int min_num = students[i].rank[0];
        for (int j = 1; j <= 3; ++j) {
            if (students[i].rank[j] < min_num) {
                min_num = students[i].rank[j];
                students[i].best = j;
            }
        }
    }
    char tmp_chars[5] = {'A', 'C', 'M', 'E'};
    for (int i = 0; i < M; ++i) {
        cin >> id;
        int tmp = exists[id];
        if (tmp) {
            int best = students[tmp - 1].best;
            cout << students[tmp - 1].rank[best] << " " << tmp_chars[best] << endl;
        } else {
            cout << "N/A" << endl;
        }
    }
    return 0;
}