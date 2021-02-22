//
// Created by tanknee on 2/22/2021.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    int N;
    long int tmp;
    cin >> N;
    vector<long int> sequence;
    for (int i = 0; i < N; ++i) {
        cin >> tmp;
        sequence.push_back(tmp);
    }
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> tmp;
        sequence.push_back(tmp);
    }
    sort(sequence.begin(), sequence.end());
    int median_index = ceil(sequence.size() / 2.0) - 1;
    cout << sequence[median_index];
    return 0;
}