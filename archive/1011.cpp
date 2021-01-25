//
// Created by tanknee on 2021/1/25.
//

#include <iostream>

using namespace std;

int main() {
    float odd, result = 1;
    int max[3];
    char r[3] = {'W', 'T', 'L'};
    for (int i = 0; i < 3; ++i) {
        float tmp_max = 0;
        for (int j = 0; j < 3; ++j) {
            cin >> odd;
            if (odd > tmp_max) {
                tmp_max = odd;
                max[i] = j;
            }
        }
        result *= tmp_max;
    }
    result = (result * 0.65 - 1) * 2;
    cout << r[max[0]] << " " << r[max[1]] << " " << r[max[2]] << " ";
    printf("%.2f", result);
    return 0;
}