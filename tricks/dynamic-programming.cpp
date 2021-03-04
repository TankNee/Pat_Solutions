//
// Created by tanknee on 3/4/2021.
//

// 数塔问题
// 5
// 8 7
// 12 7 16 ...

#include <iostream>

using namespace std;
const int maxn = 1000;
int f[maxn][maxn], dp[maxn][maxn];
// 使用递归的标准是主问题可以划分为重复的子问题，且主问题的最优解要求子问题也是最优解，具有递归的特性！
int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j <= i; ++j) {
            scanf("%d", &f[i][j]);
        }
    }
    // 边界,最后一层是递归的返回条件！
    for (int i = 1; i <= n; ++i) {
        dp[n][i] = f[n][i];
    }
    // 自下而上计算每一层每个节点的最大值！因为最后一行是固定的数值，所以从倒数第二行开始计算。
    for (int i = n - 1; i >= 1; --i) {
        for (int j = 1; j <= i; ++j) {
            // 状态转移方程
            // 找到下一层中，该数字的左右两个节点中的最大值，然后再加上本身节点的值，就是该节点从下到上路径的最大值！
            dp[i][j] = max(dp[i + 1][j], dp[i + 1][j + 1]) + f[i][j];
        }
    }
    printf("%d", dp[1][1]);
    return 0;
}