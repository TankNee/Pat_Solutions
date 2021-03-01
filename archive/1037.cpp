//
// Created by tanknee on 2021/3/1.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
    int Nc, Np;
    cin >> Nc;
    vector<long long> coupons(Nc);
    for (int i = 0; i < Nc; ++i) {
        cin >> coupons[i];
    }
    sort(coupons.begin(), coupons.end());
    cin >> Np;
    vector<long long> products(Np);
    for (int i = 0; i < Np; ++i) {
        cin >> products[i];
    }
    sort(products.begin(), products.end());

    long long sum = 0;
    int j = 0, i = 0, l = products.size() - 1;
    for (; i < coupons.size() && coupons[i] < 0 && products[j] < 0; ++i, ++j) {
        sum += coupons[i] * products[j];
    }
    for (int k = coupons.size() - 1; k >= 0 && l >= 0 && coupons[k] > 0 && products[l] > 0; k--, l--) {
        sum += coupons[k] * products[l];
    }
    cout << sum;
    return 0;
}