//
// Created by tanknee on 2021/1/24.
//

#include <iostream>
#include <map>

using namespace std;

int main() {
    int count, exponents;
    double coefficients, m1[1001] = {0.0}, result[2001] = {0.0};
    cin >> count;
    for (int i = 0; i < count; ++i) {
        cin >> exponents >> coefficients;
        m1[exponents] = coefficients;
    }
    cin >> count;
    for (int i = 0; i < count; ++i) {
        cin >> exponents >> coefficients;
        for (int j = 0; j < 1001; ++j) {
            if (m1[j] != 0.0)
                result[j + exponents] += m1[j] * coefficients;
        }
    }
    count = 0;
    for (int i = 2000; i >= 0; i--) {
        if (result[i] != 0.0)
            count++;
    }
    printf("%d", count);
    for (int i = 2000; i >= 0; i--) {
        if (result[i] != 0.0)
            printf(" %d %.1f", i, result[i]);
    }
    return 0;
}