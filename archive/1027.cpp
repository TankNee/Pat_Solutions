//
// Created by tanknee on 2/20/2021.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

string to_mars(int color) {
    string res;
    int n = color / 13;
    if (n >= 10) {
        res.append(n == 10 ? "A" : n == 11 ? "B" : "C");
    } else res.append(to_string(n));
    n = color % 13;
    if (n >= 10) {
        res.append(n == 10 ? "A" : n == 11 ? "B" : "C");
    } else res.append(to_string(n));
    return res;
}

int main() {
    int R, G, B;
    cin >> R >> G >> B;
    printf("#%s%s%s", to_mars(R).c_str(), to_mars(G).c_str(), to_mars(B).c_str());
    return 0;
}