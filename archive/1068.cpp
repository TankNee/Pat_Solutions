//
// Created by tanknee on 3/2/2021.
//


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int dp[10010], w[10010];
bool choice[10010][110];

int cmp1(int a, int b) { return a > b; }

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &w[i]);
    sort(w + 1, w + n + 1, cmp1);
    for (int i = 1; i <= n; i++) {
        for (int j = m; j >= w[i]; j--) {
            if (dp[j] <= dp[j - w[i]] + w[i]) {
                choice[i][j] = true;
                dp[j] = dp[j - w[i]] + w[i];
            }
        }
    }
    if (dp[m] != m) printf("No Solution");
    else {
        vector<int> arr;
        int v = m, index = n;
        while (v > 0) {
            if (choice[index][v] == true) {
                arr.push_back(w[index]);
                v -= w[index];
            }
            index--;
        }
        for (int i = 0; i < arr.size(); i++) {
            if (i != 0) printf(" ");
            printf("%d", arr[i]);
        }
    }
    return 0;
}

//#include <bits/stdc++.h>
//
//using namespace std;
//int N, M, visit[10000], max_size = 0;
//vector<int> coins;
//vector<vector<int>> solutions;
//
//bool exist(vector<int> solution) {
//    for (auto &i : solutions) {
//        if (i.size() != solution.size()) continue;
//        bool flag = false;
//        for (int j = 0; j < i.size(); ++j) {
//            if (i[j] != solution[j]) {
//                flag = true;
//                break;
//            }
//        }
//        if (!flag) {
//            return true;
//        }
//    }
//    return false;
//}
//
//void find_solutions(int target, vector<int> cur_solution) {
//    if (target == 0) {
//        if (cur_solution.size() < max_size) return;
//        max_size = cur_solution.size();
//        if (!exist(cur_solution))
//            solutions.push_back(cur_solution);
//        return;
//    }
//    for (int i = 0; i < coins.size() && coins[i] <= target; ++i) {
//        if (!visit[i]) {
//            visit[i] = 1;
//            cur_solution.push_back(coins[i]);
//            find_solutions(target - coins[i], cur_solution);
//            cur_solution.pop_back();
//            visit[i] = 0;
//        }
//    }
//}
//
//int main() {
//    cin >> N >> M;
//    int tmp;
//    for (int i = 0; i < N; ++i) {
//        cin >> tmp;
//        coins.push_back(tmp);
//    }
//    sort(coins.begin(), coins.end());
//    vector<int> list;
//    find_solutions(M, list);
//    if (solutions.empty()) {
//        cout << "No Solution";
//        return 0;
//    }
//    sort(solutions[0].begin(), solutions[0].end());
//    for (int i = 0; i < solutions[0].size(); ++i) {
//        cout << solutions[0][i];
//        if (i != solutions[0].size() - 1) cout << " ";
//    }
//    return 0;
//}
//
