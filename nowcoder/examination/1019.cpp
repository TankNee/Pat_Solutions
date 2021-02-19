//
// Created by tanknee on 2/19/2021.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    long int num, tmp, factor, count;
    cin >> num;
    tmp = num;
    int sqr = sqrt(num);
    vector<long int> factors;
    while (tmp != 1) {
        factor = 2;
        while (tmp % factor != 0 && factor <= sqr) { factor++; }
        if (num == factor) break;
        if (factor > sqr) {
            factors.push_back(tmp);
            break;
        }
        factors.push_back(factor);
        tmp /= factor;
    }
    cout << num << "=";
    if (factors.empty()) {
        cout << num;
        return 0;
    }
    for (int i = 0; i < factors.size(); ++i) {
        tmp = factors[i];
        cout << tmp;
        count = 1;
        while (i + 1 < factors.size() && factors[i + 1] == tmp) {
            count++;
            i++;
        }
        if (count > 1) {
            cout << "^" << count;
        }
        if (i != factors.size() - 1) cout << "*";
    }
    return 0;
}