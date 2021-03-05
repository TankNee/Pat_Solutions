//
// Created by tanknee on 3/5/2021.
//

#include <bits/stdc++.h>

using namespace std;

map<string, int> str2int;
map<int, string> int2str;
set<int> s;
int idx = 0;

int get_index(const string &address) {
    if (address == "-1") return -1;
    if (str2int.find(address) != str2int.end()) {
        return str2int[address];
    } else {
        str2int[address] = idx;
        int2str[idx++] = address;
        return str2int[address];
    }
}

string get_addr(int num) {
    return int2str[num];
}

int main() {
    string head, t1, t2;
    int N, tmp, head_idx;
    cin >> head >> N;
    vector<int> nodes(N), values(N), rv_list, rm_list;
    for (int i = 0; i < N; ++i) {
        cin >> t1 >> tmp >> t2;
        nodes[get_index(t1)] = get_index(t2);
        values[get_index(t1)] = tmp;
    }
    head_idx = get_index(head);
    while (head_idx != -1) {
        if (s.find(abs(values[head_idx])) != s.end()) {
            rm_list.push_back(head_idx);
        } else {
            s.insert(abs(values[head_idx]));
            rv_list.push_back(head_idx);
        }
        head_idx = nodes[head_idx];
    }
    for (int i = 0; i < rv_list.size(); ++i) {
        printf("%s %d ", get_addr(rv_list[i]).c_str(), values[rv_list[i]]);
        if (i != rv_list.size() - 1) {
            printf("%s\n", get_addr(rv_list[i + 1]).c_str());
        } else {
            printf("-1\n");
        }
    }
    for (int i = 0; i < rm_list.size(); ++i) {
        printf("%s %d ", get_addr(rm_list[i]).c_str(), values[rm_list[i]]);
        if (i != rm_list.size() - 1) {
            printf("%s\n", get_addr(rm_list[i + 1]).c_str());
        } else {
            printf("-1\n");
        }
    }
    return 0;
}