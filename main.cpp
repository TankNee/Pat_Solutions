#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct bundle {
    int count, index;
};

int main() {
    int num, min = -1, res = -1;
    cin >> num;
    map<int, bundle> m;
    for (int i = 0; i < num; ++i) {
        int tmp;
        cin >> tmp;
        m[tmp].count++;
        m[tmp].index = i;
    }
    for (auto it = m.begin(); it != m.end(); it++) {
        if (it->second.count == 1) {
            if (min == -1) {
                min = it->second.index;
                res = it->first;
            } else if (min > it->second.index) {
                res = it->first;
                min = it->second.index;
            }
        }
    }
    if (res < 0) {
        cout << "None";
    } else {
        cout << res;
    }
    return 0;
}