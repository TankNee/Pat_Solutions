//
// Created by tanknee on 2021/1/24.
//

#include <iostream>

using namespace std;

int main() {
    int count, sum = 0, current_floor = 0, pre_floor = 0;
    cin >> count;
    for (int i = 0; i < count; ++i) {
        cin >> current_floor;
        if (current_floor > pre_floor) {
            sum += 5 + (current_floor - pre_floor) * 6;
        } else if (current_floor < pre_floor) {
            sum += 5 + (pre_floor - current_floor) * 4;
        } else {
            sum += 5;
        }
        pre_floor = current_floor;
    }
    cout << sum;
}