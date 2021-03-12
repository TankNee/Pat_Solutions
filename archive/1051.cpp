//
// Created by tanknee on 3/12/2021.
//

#include <bits/stdc++.h>

using namespace std;

int main() {
    int M, N, K;
    bool flag;
    cin >> M >> N >> K;
    int pop_seq[N];
    for (int i = 0; i < K; ++i) {
        flag = false;
        for (int j = 0; j < N; ++j) {
            cin >> pop_seq[j];
        }
        int p_push = 0;
        vector<int> m_stack;
        for (int j = 0; j < N; ++j) {
            if (!m_stack.empty() && pop_seq[j] == m_stack.back()) {
                m_stack.pop_back();
                continue;
            } else {
                // 因为入栈顺序是固定的，且都是1，2，3等顺序，所以可以直接通过值来获得入栈的下标
                if (p_push > pop_seq[j] - 1) {
                    printf("NO\n");
                    flag = true;
                    break;
                } else {
                    for (; p_push < pop_seq[j]; ++p_push) {
                        m_stack.push_back(p_push + 1);
                        if (m_stack.size() > M) {
                            printf("NO\n");
                            flag = true;
                            break;
                        }
                    }
                    if (flag) break;
                    m_stack.pop_back();
                }
            }
        }
        if (!flag) {
            printf("YES\n");
        }
    }
    return 0;
}