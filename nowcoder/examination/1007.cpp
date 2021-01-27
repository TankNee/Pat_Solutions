//
// Created by tanknee on 2021/1/27.
//

#include <iostream>
#include <cmath>

using namespace std;


int main() {
    long long num, tmp, min, max_length = 0, sqr;
    cin >> num;
    min = num;
    sqr = (long long) sqrt(num * 1.0);
    for (long long i = 2; i <= sqr; ++i) {
        tmp = num;
        long long j = i;
        while (tmp % j == 0) {
            tmp /= j;
            j++;
        }
        tmp = j - 1;
        if (tmp - i + 1 > max_length) {
            max_length = tmp - i + 1;
            min = i;
        }
    }
    max_length = max_length == 0 ? 1 : max_length;
    cout << max_length << endl;
    cout << min;
    for (long long i = min + 1; i < min + max_length; ++i) {
        cout << "*" << i;
    }
    return 0;
}