//
// Created by tanknee on 3/8/2021.
//

#include <bits/stdc++.h>

using namespace std;
vector<int> orders(55);

int get_final_idx(int idx, int times) {
    for (int i = 1; i <= times; ++i) {
        idx = orders[idx];
    }
    return idx;
}

int main() {
    int K;
    cin >> K;
    for (int i = 1; i <= 54; ++i) {
        cin >> orders[i];
    }
    vector<int> new_orders(55);
    for (int i = 1; i <= 54; ++i) {
        new_orders[get_final_idx(i, K)] = i;
    }
    for (int i = 1; i <= 54; ++i) {
        int cur = new_orders[i];
        if (cur >= 1 && cur <= 13) {
            printf("S%d", cur);
        } else if (cur >= 14 && cur <= 26) {
            printf("H%d", cur - 13);
        } else if (cur >= 27 && cur <= 39) {
            printf("C%d", cur - 26);
        } else if (cur >= 40 && cur <= 52) {
            printf("D%d", cur - 39);
        } else if (cur >= 53) {
            printf("J%d", cur - 52);
        }
        if (i != 54) printf(" ");
    }
    return 0;
}