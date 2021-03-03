//
// Created by tanknee on 3/3/2021.
//

#include <bits/stdc++.h>

using namespace std;

struct person {
    string name;
    int height;

    bool operator<(const person &p) const {
        if (height != p.height) return height > p.height;
        return name < p.name;
    }
};

int main() {
    int N, K;
    cin >> N >> K;
    vector<person> persons(N);
    for (int i = 0; i < N; ++i) {
        cin >> persons[i].name >> persons[i].height;
    }
    int capacity = floor(N / K);
    int last_row = N % capacity + capacity;
    sort(persons.begin(), persons.end());
    vector<vector<string>> rows;
    for (int i = 0; i < N;) {
        vector<string> row;
        int idx, length;
        if (i == 0) {
            length = last_row;
        } else
            length = capacity;
        row.resize(length);
        idx = length / 2;
        row[idx] = persons[i++].name;
        for (int j = 1; j < length; j++, i++) {
            if (j & 1) {
                row[idx - j / 2 - 1] = persons[i].name;
            } else {
                row[idx + j / 2] = persons[i].name;
            }
        }
        rows.push_back(row);
    }
    for (auto &row : rows) {
        for (int j = 0; j < row.size(); ++j) {
            printf("%s", row[j].c_str());
            if (j != row.size() - 1) printf(" ");
        }
        printf("\n");
    }
    return 0;
}
