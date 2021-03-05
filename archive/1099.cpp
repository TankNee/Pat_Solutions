//
// Created by tanknee on 3/4/2021.
//


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

//#include <bits/stdc++.h>
//
//using namespace std;
//
//int idx = 0, N;
//vector<int> in_order;
//
//struct node {
//    node *left, *right;
//    int val, index{};
//
//    node() {
//        left = right = nullptr;
//        val = INT_MAX;
//    }
//};
//
//void insert(node *root, int index, int left, int right) {
//    if (root->index == index) {
//        if (left != -1) {
//            node *l = new node;
//            l->index = left;
//            root->left = l;
//        }
//        if (right != -1) {
//            node *r = new node;
//            r->index = right;
//            root->right = r;
//        }
//        return;
//    }
//    if (root->left) insert(root->left, index, left, right);
//    if (root->right) insert(root->right, index, left, right);
//}
//
//void update_val(node *root) {
//    if (root->left) update_val(root->left);
//    root->val = in_order[idx++];
//    if (root->right) update_val(root->right);
//}
//
//int main() {
//    int t1, t2;
//    cin >> N;
//    if (!N) return 0;
//    in_order.resize(N);
//    node *root = new node;
//    root->index = 0;
//    for (int i = 0; i < N; ++i) {
//        cin >> t1 >> t2;
//        insert(root, i, t1, t2);
//    }
//    for (int i = 0; i < N; ++i) {
//        cin >> in_order[i];
//    }
//    sort(in_order.begin(), in_order.end());
//    update_val(root);
//    queue<node *> q;
//    q.push(root);
////    printf("%d", root->val);
////    if (root->left)
////        q.push(root->left);
////    if (root->right)
////        q.push(root->right);
//    while (!q.empty()) {
//        printf("%d",q.front()->val);
//        if (q.front()->left)
//            q.push(q.front()->left);
//        if (q.front()->right)
//            q.push(q.front()->right);
//        if (q.size() > 1) printf(" ");
//        q.pop();
//    }
//    return 0;
//}