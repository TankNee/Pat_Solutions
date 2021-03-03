//
// Created by tanknee on 3/3/2021.
//

#include <iostream>

// 双指针法求解两数字之和为一个固定的数的组合，一个置于左侧，一个置于右侧，每次只需要判断两个指针指向的数的和
// 大了就将右指针左移，小了就将左指针右移，相等即输出。
// 时间复杂度为O(N)，空间复杂度为O(N)

using namespace std;

int main() {
    int i = 0, j = 9, a[10], m = 8;
    while (i <= j) {
        if (a[i] + a[j] == m) {
            printf("%d", m);
            i++, j--;
        } else if (a[i] + a[j] > m) {
            j--;
        } else {
            i++;
        }
    }
    return 0;
}
