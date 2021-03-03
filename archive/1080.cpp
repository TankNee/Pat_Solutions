//
// Created by tanknee on 3/3/2021.
//

#include <bits/stdc++.h>

using namespace std;


struct application {
    int ge, gi, id, rank;
    vector<int> preferred_schools;

    bool operator==(const application &a) const {
        double f1 = (ge + gi) / 2.0, f2 = (a.ge + a.gi) / 2.0;
        return f1 == f2 && ge == a.ge;
    }
};

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    int quotas[M];
    vector<application> applications(N);
    vector<vector<application>> schools(M);
    for (int i = 0; i < M; ++i) {
        cin >> quotas[i];
    }
    for (int i = 0; i < N; ++i) {
        cin >> applications[i].ge >> applications[i].gi;
        applications[i].preferred_schools.resize(K);
        for (int j = 0; j < K; ++j) {
            cin >> applications[i].preferred_schools[j];
        }
        applications[i].id = i;
    }
    sort(applications.begin(), applications.end(), [](const application &a1, const application &a2) {
        double f1 = (a1.ge + a1.gi) / 2.0, f2 = (a2.ge + a2.gi) / 2.0;
        if (f1 != f2) {
            return f1 > f2;
        }
        return a1.ge > a2.ge;
    });
    applications[0].rank = 1;
    for (int i = 1; i < applications.size(); ++i) {
        if (applications[i] == applications[i - 1]) {
            applications[i].rank = applications[i - 1].rank;
        } else {
            applications[i].rank = i + 1;
        }
    }
    for (int i = 0; i < applications.size(); ++i) {
        for (int j = 0; j < K; ++j) {
            int school_idx = applications[i].preferred_schools[j], cur_rank = applications[i].rank;
            if (schools[school_idx].size() < quotas[school_idx]) {
                vector<application> tmp_apps;
                for (int k = i; applications[k].rank == cur_rank && k < applications.size(); ++k) {
                    int tmp_school_idx;
                    for (int l = 0; l < K; ++l) {
                        if (schools[applications[k].preferred_schools[l]].size() <
                            quotas[applications[k].preferred_schools[l]]) {
                            tmp_school_idx = applications[k].preferred_schools[l];
                            break;
                        }
                    }
                    if (tmp_school_idx == school_idx) {
                        tmp_apps.push_back(applications[k]);
                        i++;
                    }
                }
                for (auto &tmp_app : tmp_apps) {
                    schools[school_idx].push_back(tmp_app);
                }
                --i;
                break;
            }
        }
    }
    for (int i = 0; i < M; ++i) {
        sort(schools[i].begin(), schools[i].end(), [](const application& a1, const application& a2) {
            return a1.id < a2.id;
        });
        for (int j = 0; j < schools[i].size(); ++j) {
            printf("%d", schools[i][j].id);
            if (j != schools[i].size() - 1) printf(" ");
        }
        printf("\n");
    }
    return 0;
}
