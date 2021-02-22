//
// Created by tanknee on 2/22/2021.
//

#include <iostream>
#include <algorithm>

using namespace std;

struct student {
    int id, grade;
    string name;
};

void print_list(const student s[], int N) {
    for (int i = 0; i < N; ++i) {
        printf("%06d %s %d\n", s[i].id, s[i].name.c_str(), s[i].grade);
    }
}

int main() {
    int N, C;
    cin >> N >> C;
    student students[N];
    for (int i = 0; i < N; ++i) {
        cin >> students[i].id >> students[i].name >> students[i].grade;
    }
    if (C == 1) {
        sort(students, students + N, [](student s1, student s2) {
            return s1.id < s2.id;
        });
    } else if (C == 2) {
        sort(students, students + N, [](student s1, student s2) {
            if (s1.name != s2.name) {
                return s1.name < s2.name;
            } else {
                return s1.id < s2.id;
            }
        });
    } else if (C == 3) {
        sort(students, students + N, [](student s1, student s2) {
            if (s1.grade != s2.grade) {
                return s1.grade < s2.grade;
            } else {
                return s1.id < s2.id;
            }
        });
    }
    print_list(students, N);
    return 0;
}