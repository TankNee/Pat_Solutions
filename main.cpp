#include <bits/stdc++.h>

using namespace std;
int exists[50];

struct equation {
    int product;
    vector<int> reactants;
};

void print_equation(equation e) {
    for (int i = 0; i < e.reactants.size(); ++i) {
        printf("%02d", e.reactants[i]);
        if (i != e.reactants.size() - 1) printf(" + ");
    }
    printf(" -> %02d\n", e.product);
}

bool test(const equation &e) {
    bool flag = true;
    for (int reactant : e.reactants) {
        if (!exists[reactant]) {
            flag = false;
            break;
        }
    }
    if (flag) {
        for (int reactant : e.reactants) {
            exists[reactant] = 0;
        }
    }
    return flag;
}

int main() {
    int N, M, K;
    cin >> N;
    vector<int> reactants(N), products;
    vector<equation> equations;
    map<int, vector<equation>> m;
    for (int i = 0; i < N; ++i) {
        cin >> reactants[i];
        exists[reactants[i]] = 1;
    }
    cin >> M;
    products.resize(M);
    for (int i = 0; i < M; ++i) {
        cin >> products[i];
        for (int j = 0; j < N; ++j) {
            if (reactants[j] == products[i]) {
                equation e{products[i], {products[i]}};
                m[products[i]].push_back(e);
            }
        }
    }
    cin >> K;
    for (int i = 0; i < K; ++i) {
        equation e;
        char tmp = getchar();
        string num;
        while (tmp != '-') {
            if (tmp == ' ' && !num.empty()) {
                e.reactants.push_back(stoi(num));
                num.clear();
            } else if (tmp >= '0' && tmp <= '9') {
                num.push_back(tmp);
            }
            tmp = getchar();
        }
        num.clear();
        while (tmp != '\n') {
            if (tmp >= '0' && tmp <= '9') {
                num.push_back(tmp);
            }
            tmp = getchar();
        }
        e.product = stoi(num);
        equations.push_back(e);
        m[e.product].push_back(e);
    }
    for (int i = 0; i < M; ++i) {
        sort(m[products[i]].begin(), m[products[i]].end(), [](const equation &e1, const equation &e2) {
            for (int j = 0; j < min(e1.reactants.size(), e2.reactants.size()); ++j) {
                if (e1.reactants[j] != e2.reactants[j]) return e1.reactants[j] < e2.reactants[j];
            }
            return e1.reactants.size() < e2.reactants.size();
        });
    }
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < m[products[i]].size(); ++j) {
            if (test(m[products[i]][j])) {
                print_equation(m[products[i]][j]);
                break;
            }
        }
    }
    return 0;
}