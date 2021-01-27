//
// Created by tanknee on 2021/1/27.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> nodes[100]; // 每个元素代表一个节点链表
int pedigree[100], population[101];  // 族谱树中每一层的叶子结点的数量
int pedigree_depth = -1; // 族谱树的最大深度

/**
 * 深度优先算法，遍历整个家族树，如果找到叶子结点就加入到全局变量数组中
 * @param index 下标
 * @param depth 深度
 */
void dfs(int index, int depth) {
    if (!nodes[index].empty()) {
        population[depth] += nodes[index].size();
    }
    // 遍历该节点的所有子节点
    for (int i : nodes[index]) {
        // 因为往下走了一层，所以深度加1
        dfs(i, depth + 1);
    }
}

int main() {
    int N, M, node, num, child, max = 0, max_i = 0;
    // 处理第一行
    cin >> N >> M;
    // 遍历所有的非叶节点，构建节点链表
    for (int i = 0; i < M; ++i) {
        cin >> node >> num;
        for (int j = 0; j < num; ++j) {
            cin >> child;
            nodes[node].push_back(child);
        }
    }
    // 对族谱树进行深度优先遍历
    dfs(1, 0);
    for (int i = 0; i < N; ++i) {
        if (population[i] > max) {
            max = population[i];
            max_i = i + 2;
        }
    }
    cout << max << " " << max_i;
    return 0;
}