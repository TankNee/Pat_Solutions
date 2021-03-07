//
// Created by tanknee on 3/7/2021.
//

#include <bits/stdc++.h>

using namespace std;

bool is_symmetric(const string &str) {
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] != str[str.length() - i - 1]) return false;
    }
    return true;
}

int main() {
    string origin;
    int max_length = 0;
    getline(cin, origin);
    for (int i = 0; i < origin.length(); ++i) {
        for (int j = origin.length() - 1; j >= i; --j) {
            string tmp = origin.substr(i, j - i + 1);
            if (is_symmetric(tmp) && tmp.length() > max_length) {
                max_length = tmp.length();
            }
        }
    }
    printf("%d", max_length);
    return 0;
}