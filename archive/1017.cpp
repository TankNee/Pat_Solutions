//
// Created by tanknee on 2021/2/11.
//

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct customer {
    int time;
    double process_time;

    bool operator<(const customer &c) const {
        return time < c.time;
    }
};

struct node {
    int pop_time, end_time;
    queue<customer> q;
};

int main() {
    int N, K, sum = 0;
    cin >> N >> K;
    vector<customer> customers;
    for (int i = 0; i < N; ++i) {
        int h, m, s;
        double pt;
        scanf("%d:%d:%d %lf", &h, &m, &s, &pt);
        if (h * 60 * 60 + m * 60 + s > 17 * 60 * 60) continue;
        customer c{};
        // 八点钟之前到的都记为负数
        c.time = (h - 8) * 60 * 60 + m * 60 + s;
        c.process_time = pt > 60.0 ? 3600.0 : pt * 60.0;
        customers.push_back(c);
    }
    if (customers.empty()) {
        printf("0.0");
        return 0;
    }
    sort(customers.begin(), customers.end());
    // 八点之前到的都是等待时间
    for (int i = 0; customers[i].time < 0; ++i) {
        sum -= customers[i].time;
        customers[i].time = 0;
    }
    vector<int> windows(K);
    for (int i = 0; i < customers.size(); ++i) {
        int min_time = windows[0], index = 0;
        for (int j = 1; j < K; ++j) {
            if (windows[j] < min_time) {
                min_time = windows[j];
                index = j;
            }
        }
        if (windows[index] <= customers[i].time) {
            windows[index] = customers[i].time + customers[i].process_time;
        } else {
            sum += windows[index] - customers[i].time;
            windows[index] += customers[i].process_time;
        }
    }
    printf("%.1f", (1.0 * sum) / (1.0 * customers.size()) / 60.0);
    return 0;
}