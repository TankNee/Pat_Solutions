//
// Created by tanknee on 3/4/2021.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
    string origin, res = "";
    cin >> origin;
    char flag = origin[0];
    origin.erase(origin.begin());
    int dot_pos = origin.find('.'), e_pos = origin.find('E');
    int exponent = stoi(origin.substr(e_pos + 1));
    if (exponent < 0) {
        res.append("0.");
        for (int i = 0; i < abs(exponent + dot_pos); ++i) {
            res.append("0");
        }
        for (int i = 0; i < e_pos; ++i) {
            if (origin[i] == '.') continue;
            res += origin[i];
        }
    } else {
        int length = e_pos - dot_pos - 1;
        for (int i = 0; i < e_pos; ++i) {
            if (origin[i] == '.') continue;
            res += origin[i];
        }
        if (exponent > length) {
            for (int i = 0; i < exponent - length; ++i) {
                res.append("0");
            }
        } else if (exponent < length) {
            res.insert(dot_pos + exponent, ".");
        }
    }
    while (res[0] == '0' && res[1] != '.') res.erase(res.begin());
    if (flag == '-') cout << '-';
    cout << res;
    return 0;
}