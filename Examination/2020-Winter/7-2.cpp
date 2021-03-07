//
// Created by tanknee on 3/7/2021.
//

#include <bits/stdc++.h>

using namespace std;
string str, subsequence;

int find_index(int init_idx, char target) {
    for (int i = init_idx; i < str.length(); ++i) {
        if (str[i] == target) return i;
    }
    return -1;
}

int main() {
    cin >> str >> subsequence;
    int init_idx = str.find(subsequence[0]), tmp_init_idx = str.find(
            subsequence[0]), min_length = INT_MAX, tmp_idx, left, right, flag = 0;
    while (init_idx != -1) {
        vector<int> tmp;
        for (char i : subsequence) {
            tmp_idx = find_index(init_idx, i);
            if (tmp_idx == -1) {
                flag = 1;
                break;
            }
            tmp.push_back(tmp_idx);
            init_idx = tmp_idx + 1;
        }
        if (flag) break;
        if (min_length > tmp[tmp.size() - 1] - tmp[0]) {
            min_length = tmp[tmp.size() - 1] - tmp[0];
            right = tmp[tmp.size() - 1];
            left = tmp[0];
        }
        init_idx = find_index(tmp_init_idx + 1, subsequence[0]);
        tmp_init_idx = init_idx;
    }
    cout << str.substr(left, right - left + 1);
    return 0;
}