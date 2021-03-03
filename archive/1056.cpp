//
// Created by tanknee on 3/2/2021.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct node {
    int id, weight, rank;
};

int main() {
    int Np, Ng;
    cin >> Np >> Ng;
    vector<node> nodes(Np), tmp, final(Np);
    vector<int> order(Np);
    for (int i = 0; i < Np; ++i) {
        cin >> nodes[i].weight;
        nodes[i].id = i;
        final[i].weight = nodes[i].weight;
        final[i].id = i;
    }
    for (int i = 0; i < Np; ++i) {
        cin >> order[i];
    }
    int size = Np, flag = 1;
    for (int i = 0; i < size; i += Ng) {
        int max = -1, max_index = -1;
        for (int j = i; j < i + Ng && j < size; ++j) {
            if (flag) {
                if (nodes[order[j]].weight > max) {
                    max = nodes[order[j]].weight;
                    max_index = order[j];
                }
                continue;
            }
            if (nodes[j].weight > max) {
                max = nodes[i].weight;
                max_index = nodes[i].id;
            }
        }
        tmp.push_back(nodes[max_index]);
        for (int j = i; j < i + Ng && j < size; ++j) {
            if (flag) {
                if (order[j] != max_index)
                    final[order[j]].rank = ceil(size * 1.0 / Ng) + 1;
                continue;
            }
            if (nodes[j].id != max_index) {
                final[nodes[j].id].rank = ceil(size * 1.0 / Ng) + 1;
            }
        }
        if (i + Ng >= size) {
            if (tmp.size() == 1) {
                final[tmp[0].id].rank = 1;
                break;
            }
            if (flag) flag = 0;
            size = tmp.size();
            nodes.clear();
            for (int j = 0; j < size; ++j) {
                nodes.emplace_back(tmp[j]);
            }
            tmp.clear();
            i = -Ng;
        }
    }
    for (int i = 0; i < final.size(); ++i) {
        cout << final[i].rank;
        if (i != final.size() - 1) cout << " ";
    }
    return 0;
}

