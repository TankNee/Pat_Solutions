//
// Created by tanknee on 2021/1/28.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct node {
    int left, right, value;
};


/**
 * 先对输入进行排序，得到的数组就是中序遍历的树！因为对于二叉搜索树，中序遍历就是从小到大排序。
 * @return
 */
int main() {
    int N;
    cin >> N;
    vector<int> numbers(N, 0), v;
    queue<int> q;
    node nodes[N];
    for (int i = 0; i < N; ++i) {
        cin >> nodes[i].left >> nodes[i].right;
    }
    for (int i = 0; i < N; ++i) {
        cin >> numbers[i];
    }
    sort(numbers.begin(), numbers.end());
    int cur_node = 0, index = 0;
    while (cur_node != -1 || !v.empty()) {
        while (cur_node != -1) {
            v.push_back(cur_node);
            cur_node = nodes[cur_node].left;
        }
        if (!v.empty()) {
            cur_node = v.back();
            v.pop_back();
            nodes[cur_node].value = numbers[index];
            index++;
            cur_node = nodes[cur_node].right;
        }
    }
    cur_node = 0;
    q.push(cur_node);
    while (!q.empty()) {
        cur_node = q.front();
        if (nodes[cur_node].left != -1)
            q.push(nodes[cur_node].left);
        if (nodes[cur_node].right != -1)
            q.push(nodes[cur_node].right);
        cout << nodes[cur_node].value;
        if (q.size() > 1) {
            cout << " ";
        }
        q.pop();
    }
    return 0;
}