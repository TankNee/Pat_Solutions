//
// Created by tanknee on 2/17/2021.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct testee {
    string registration_number;
    int score;
    int location;
    int final_rank, local_rank;
};

int main() {
    int N, count = 0, num;
    cin >> N;
    vector<vector<testee>> locations(N);
    for (int i = 0; i < N; ++i) {
        cin >> num;
        for (int j = 0; j < num; ++j) {
            testee t;
            cin >> t.registration_number >> t.score;
            t.location = i + 1;
            locations[i].push_back(t);
        }
        count += num;
    }
    vector<testee> final;
    for (int i = 0; i < N; ++i) {
        sort(locations[i].begin(), locations[i].end(),
             [](const testee &t1, const testee &t2) { return t1.score > t2.score; });
        locations[i][0].local_rank = 1;
        final.emplace_back(locations[i][0]);
        for (int j = 1; j < locations[i].size(); ++j) {
            if (locations[i][j].score == locations[i][j - 1].score) {
                locations[i][j].local_rank = locations[i][j - 1].local_rank;
            } else {
                locations[i][j].local_rank = j + 1;
            }
            final.emplace_back(locations[i][j]);
        }
    }
    printf("%d\n", count);
    sort(final.begin(), final.end(), [](const testee &t1, const testee &t2) {
        if (t1.score != t2.score) {
            return t1.score > t2.score;
        } else {
            return t1.registration_number < t2.registration_number;
        }
    });
    final[0].final_rank = 1;
    printf("%s %d %d %d\n", final[0].registration_number.c_str(), final[0].final_rank, final[0].location,
           final[0].local_rank);
    for (int j = 1; j < final.size(); ++j) {
        if (final[j].score == final[j - 1].score) {
            final[j].final_rank = final[j - 1].final_rank;
        } else {
            final[j].final_rank = j + 1;
        }
        printf("%s %d %d %d\n", final[j].registration_number.c_str(), final[j].final_rank, final[j].location,
               final[j].local_rank);
    }

    return 0;
}