//
// Created by tanknee on 2/19/2021.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int g1, s1, k1, g2, s2, k2, g3, s3, k3;
    scanf("%d.%d.%d %d.%d.%d", &g1, &s1, &k1, &g2, &s2, &k2);
    int flag = 0;
    if (k1 + k2 >= 29) {
        k3 = k1 + k2 - 29;
        flag = 1;
    } else k3 = k1 + k2;
    if (s1 + s2 + flag >= 17) {
        s3 = s1 + s2 + flag - 17;
        flag = 1;
    } else {
        s3 = s1 + s2 + flag;
        flag = 0;
    }
    g3 = g1 + g2 + flag;
    printf("%d.%d.%d", g3, s3, k3);
    return 0;
}