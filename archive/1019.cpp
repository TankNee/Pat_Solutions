//
// Created by tanknee on 2021/2/14.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
    vector<int> nums;
    long long N, b;
    cin >> N >> b;
//    int index = 0;
    long long tmp = N;
    do {
        nums.push_back(tmp % b);
        tmp /= b;
    } while (tmp != 0);
    for (int i = 0; i < nums.size() / 2 + 1; ++i) {
        if (nums[i] != nums[nums.size() - 1 - i]) {
            cout << "No" << endl;
            break;
        }
        if (i == nums.size() / 2) {
            cout << "Yes" << endl;
            break;
        }
    }
    for (int i = nums.size() - 1; i >= 0; --i) {
        cout << nums[i];
        if (i != 0) cout << " ";
    }
    return 0;
}