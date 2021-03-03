//
// Created by tanknee on 3/3/2021.
//

#include <bits/stdc++.h>

using namespace std;

struct testee {
    int score;
    string id;
};

struct school_node {
    string name;
    vector<testee> t;
    int tws{}, rank;
};

void to_lower_case(string &origin) {
    for (char &i : origin) {
        if (i >= 'A' && i <= 'Z') {
            i += 32;
        }
    }
}

int cal_tws(vector<testee> t) {
    double sum = 0.0;
    for (auto &i : t) {
        if (i.id.find('B') != -1) {
            sum += i.score / 1.5;
        } else if (i.id.find('A') != -1) {
            sum += i.score * 1.0;
        } else {
            sum += i.score * 1.5;
        }
    }
    return floor(sum);
}


int main() {
    int N;
    cin >> N;
    unordered_map<string, vector<testee>> schools;
    vector<school_node> nodes;
    string school;
    for (int i = 0; i < N; ++i) {
        testee t;
        cin >> t.id >> t.score >> school;
        to_lower_case(school);
        schools[school].push_back(t);
    }
    for (auto &tmp_school : schools) {
        school_node sn{tmp_school.first, tmp_school.second, cal_tws(tmp_school.second)};
        nodes.push_back(sn);
    }
    sort(nodes.begin(), nodes.end(),
         [](const school_node &sn1, const school_node &sn2) {
             if (sn1.tws != sn2.tws) {
                 return sn1.tws > sn2.tws;
             } else if (sn1.t.size() != sn2.t.size()) {
                 return sn1.t.size() < sn2.t.size();
             } else {
                 return sn1.name < sn2.name;
             }
         });
    nodes[0].rank = 1;
    printf("%d\n%d %s %d %d\n", nodes.size(), nodes[0].rank, nodes[0].name.c_str(), nodes[0].tws, nodes[0].t.size());
    for (int i = 1; i < nodes.size(); ++i) {
        if (nodes[i].tws == nodes[i - 1].tws) {
            nodes[i].rank = nodes[i - 1].rank;
        } else {
            nodes[i].rank = i + 1;
        }
        printf("%d %s %d %d\n", nodes[i].rank, nodes[i].name.c_str(), nodes[i].tws, nodes[i].t.size());
    }
    return 0;
}
