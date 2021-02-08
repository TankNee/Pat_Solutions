//
// Created by tanknee on 2021/2/5.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    string s;
    cin >> s;
    int dict[256], max_length = 0, left_index = 0;
    for (int i = 0; i < s.length(); ++i) {
        // 滑动窗口，如果这个数从来没有访问过，或者这个数最后出现的位置在当前窗口之外(left_index,i),那么就可以更新窗口长度。
        if (dict[s[i]] == 0 || dict[s[i]] < left_index) {
            max_length = max(max_length, i - left_index + 1);
        } else {
            // 如果这个数被访问过了，且在窗口之内，那么就将最左侧的游标更新为这个数的下一个数
            left_index = dict[s[i]];
        }
        dict[s[i]] = i + 1;
    }
    cout << max_length;
    return 0;
}