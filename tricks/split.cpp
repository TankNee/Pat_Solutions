//
// Created by tanknee on 2/23/2021.
//

#include <bits/stdc++.h>

using namespace std;

vector<string> split(string origin, const string& separator) {
    int sep_index = origin.find(separator);
    vector<string> res;
    while (sep_index != -1) {
        res.push_back(origin.substr(0, sep_index));
        origin = origin.substr(sep_index + 1);
        sep_index = origin.find(separator);
    }
    if (origin.length()) res.push_back(origin);
    return res;
}