//
// Created by tanknee on 2021/2/10.
//

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool is_prime(int N) {
    if (N <= 1) return false;
    int sqr = int(sqrt(N * 1.0));
    for (int i = 2; i <= sqr; ++i) {
        if (N % i == 0) return false;
    }
    return true;
}

int main() {
    int N, D;
    while (scanf("%d", &N) != EOF) {
        if (N < 0) break;
        cin >> D;
        if (!is_prime(N)) {
            printf("No\n");
            continue;
        }
        // 反转
        int len = 0, arr[100];
        do {
            arr[len++] = N % D;
            N = N / D;
        } while (N != 0);
        for (int i = 0; i < len; i++)
            N = N * D + arr[i];
        printf("%s", is_prime(N) ? "Yes\n" : "No\n");
    }
    return 0;
}