//
// Created by tanknee on 2/19/2021.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int num;
    cin >> num;
    for (int i = 1; i < num + 1; ++i) {
        long double a, b, c;
        cin >> a >> b >> c;
        cout << "Case #" << i << ": " << (a + b > c ? "true" : "false") << endl;
    }
    return 0;
}