//
// Created by tanknee on 3/12/2021.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    int characters[130];
    fill(characters, characters + 130, 0);
    for (char i : s2) {
        characters[i]++;
    }
    for (char i : s1) {
        if (!characters[i]) {
            printf("%c", i);
        }
    }
    return 0;
}