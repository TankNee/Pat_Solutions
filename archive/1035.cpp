//
// Created by tanknee on 2021/3/1.
//

#include <iostream>
#include <vector>

using namespace std;

struct account {
    string name, pwd;
};

void replace_all(string &origin, char target, char replacement) {
    for (char &i : origin) {
        if (i == target) i = replacement;
    }
}

int main() {
    int N;
    cin >> N;
    vector<account> origin(N, account{});
    vector<account> modified;
    for (int i = 0; i < N; ++i) {
        cin >> origin[i].name >> origin[i].pwd;
        if (origin[i].pwd.find('1') != -1 || origin[i].pwd.find('0') != -1 || origin[i].pwd.find('l') != -1 ||
            origin[i].pwd.find('O') != -1) {
            replace_all(origin[i].pwd, '1', '@');
            replace_all(origin[i].pwd, '0', '%');
            replace_all(origin[i].pwd, 'l', 'L');
            replace_all(origin[i].pwd, 'O', 'o');
            modified.push_back(origin[i]);
        }
    }
    if (modified.empty()) {
        if (N == 1) {
            cout << "There is 1 account and no account is modified";
        } else {
            printf("There are %d accounts and no account is modified", N);
        }
        return 0;
    }
    cout << modified.size() << endl;
    for (auto & i : modified) {
        printf("%s %s\n", i.name.c_str(), i.pwd.c_str());
    }
    return 0;
}