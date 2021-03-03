//
// Created by tanknee on 3/3/2021.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;
    cin >> N;
    long double a, b, c;
    for (int i = 0; i < N; ++i) {
        cin >> a >> b >> c;
        if (a + b > c) {
            printf("Case #%d: true\n", i + 1);
        } else {
            printf("Case #%d: false\n", i + 1);
        }
    }
    return 0;
}
