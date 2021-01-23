//
// Created by tanknee on 2021/1/23.
//

#include <iostream>
#include <vector>

using namespace std;

vector<int> nodes[100]; // 每个元素代表一个节点链表
int pedigree[100];  // 族谱树中每一层的叶子结点的数量
int pedigree_depth = -1; // 族谱树的最大深度

/**
 * 深度优先算法，遍历整个家族树，如果找到叶子结点就加入到全局变量数组中
 * @param index 下标
 * @param depth 深度
 */
void dfs(int index, int depth) {
    if (nodes[index].empty()) {
        // 如果这个节点没有子节点，那么就是叶子结点
        pedigree[depth]++;
        // 这个叶子结点的深度如果超过原本记录的最大深度，那么就更新最大深度
        pedigree_depth = depth > pedigree_depth ? depth : pedigree_depth;
        return;
    }
    // 遍历该节点的所有子节点
    for (int i : nodes[index]) {
        // 因为往下走了一层，所以深度加1
        dfs(i, depth + 1);
    }
}

int main() {
    int N, M, node, num, child;
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
    // 数组默认值为0，这里输出这个数组的全部内容，长度为pedigree_length
    cout << pedigree[0];
    for (int i = 1; i <= pedigree_depth; ++i) {
        cout << " " << pedigree[i];
    }
    return 0;
}