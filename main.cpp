#include <bits/stdc++.h>

using namespace std;
string cmd;
vector<int> m_stack, s;

void insert(int key) {
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] >= key) {
            s.insert(s.begin() + i, key);
            return;
        }
    }
    s.push_back(key);
}

int main() {
    int N, key;
    scanf("%d\n", &N);
    for (int i = 0; i < N; ++i) {
        getline(cin, cmd);
        if (cmd == "Pop") {
            if (s.empty()) {
                printf("Invalid\n");
                continue;
            }
            printf("%d\n", m_stack.back());
            auto it = find(s.begin(), s.end(), m_stack.back());
            s.erase(it);
            m_stack.pop_back();
        } else if (cmd == "PeekMedian") {
            if (s.empty()) {
                printf("Invalid\n");
                continue;
            }
            if (s.size() % 2 == 0) {
                printf("%d\n", *(s.begin() + (s.size() / 2) - 1));
            } else {
                if (s.size() == 1) {
                    printf("%d\n", m_stack[0]);
                } else {
                    printf("%d\n", *(s.begin() + ((s.size() + 1) / 2) - 1));
                }
            }
        } else {
            key = stoi(cmd.substr(5));
            insert(key);
            m_stack.push_back(key);
        }
    }
    return 0;
}
