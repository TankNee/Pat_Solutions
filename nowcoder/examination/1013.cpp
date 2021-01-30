//
// Created by tanknee on 2021/1/30.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool is_prime(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    int sqr = sqrt(num), i = 2;
    while (i <= sqr) {
        if (num % i == 0) return false;
        i++;
    }
    return true;
}

int main() {
    int t_size, num, tmp;
    cin >> t_size >> num;
    while (!is_prime(t_size))
        t_size++;
    bool hash_table[t_size];
    fill(hash_table, hash_table + t_size, false);
    for (int i = 0; i < num; ++i) {
        cin >> tmp;
        int j;
        for (j = 0; j < t_size; ++j) {
            int pos = (tmp + j * j) % t_size;
            if (!hash_table[pos]) {
                hash_table[pos] = true;
                cout << pos;
                break;
            }
        }
        if (j == t_size) cout << "-";
        if (i != num - 1) cout << " ";
    }
    return 0;
}