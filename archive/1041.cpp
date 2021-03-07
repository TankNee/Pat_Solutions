//
// Created by tanknee on 3/7/2021.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    scanf("%d", &N);
    vector<int> origin(N);
    map<int, int> m;
    for (int i = 0; i < N; ++i) {
        cin >> origin[i];
        m[origin[i]]++;
    }
    for (int i = 0; i < N; ++i) {
        if (m[origin[i]] == 1) {
            printf("%d", origin[i]);
            return 0;
        }
    }
    printf("None");
    return 0;
}