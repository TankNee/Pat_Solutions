//
// Created by tanknee on 2021/1/24.
//

#include <iostream>
#include <vector>

using namespace std;
int main() {
    int count;
    cin >> count;
    vector<int> v(count);
    // 最大值默认为-1，方便后面判断有没有找到最大值
    // 左右下标初始值为整个数组的左右下标！
    int max = -1, temp_max = 0, temp_index = 0, left = 0, right = count - 1;
    for (int i = 0; i < count; ++i) {
        cin >> v[i];
        temp_max += v[i];
        // 如果和已经小于零了，那么再往下走肯定不会是最大子序列！
        if (temp_max < 0) {
            // 重置临时最大值变量
            temp_max = 0;
            // 然后将下标移动到下一个值
            temp_index = i + 1;
        } else if (temp_max > max) {
            // 如果找到了一个更大的和，就记录这个最大值和左右下标，因为起伏不定所以左下标会一直变化，就使用temp_index来作为下标
            max = temp_max;
            left = temp_index;
            right = i;
        }
    }
    // 如果最大值小于0，那么说明没找到大于0的最大值，就将其置为0！
    if (max < 0) max = 0;
    cout << max << " " << v[left] << " " << v[right];
    return 0;
}