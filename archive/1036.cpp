//
// Created by tanknee on 2021/3/1.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct student {
    string name, id;
    char sex;
    int grade;
};

int main() {
    int N;
    vector<student> males;
    vector<student> females;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        student s;
        cin >> s.name >> s.sex >> s.id >> s.grade;
        if (s.sex == 'M') {
            males.push_back(s);
        } else {
            females.push_back(s);
        }
    }
    sort(males.begin(), males.end(), [](const student &s1, const student &s2) { return s1.grade < s2.grade; });
    sort(females.begin(), females.end(), [](const student &s1, const student &s2) { return s1.grade > s2.grade; });
    if (males.empty()) {
        if (females.empty()) cout << "Absent" << endl;
        else {
            cout << females[0].name << " " << females[0].id << endl;
        }
        cout << "Absent" << endl;
        cout << "NA";
        return 0;
    } else if (females.empty()) {
        cout << "Absent" << endl;
        if (males.empty()) cout << "Absent" << endl;
        else {
            cout << males[0].name << " " << males[0].id << endl;
        }
        cout << "NA";
        return 0;
    }
    cout << females[0].name << " " << females[0].id << endl;
    cout << males[0].name << " " << males[0].id << endl;
    cout << females[0].grade - males[0].grade;
    return 0;
}