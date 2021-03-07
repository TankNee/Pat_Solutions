//
// Created by tanknee on 3/7/2021.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
    int N;
    scanf("%d", &N);
    int f1 = 0, f2 = 1, tmp;
    while (f2 < N) {
        tmp = f2;
        f2 = f1 + f2;
        f1 = tmp;
    }
    if (abs(f1 - N) < abs(f2 - N)) {
        printf("%d", f1);
    } else if (abs(f1 - N) > abs(f2 - N)) {
        printf("%d", f2);
    } else {
        printf("%d", f1);
    }
    return 0;
}
