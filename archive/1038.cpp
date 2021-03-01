//
// Created by tanknee on 2021/3/1.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
    int N;
    cin >> N;
    vector<string> nums(N);
    for (int i = 0; i < N; ++i) {
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end(), [](string n1, string n2) {
        return n1 + n2 < n2 + n1;
    });
    string res;
    for (int i = 0; i < N; ++i) {
        res.append(nums[i]);
    }
    while (res.length() != 0 && res[0] == '0') {
        res.erase(res.begin());
    }
    if (res.length() == 0) cout << 0;
    cout << res;
    return 0;
}