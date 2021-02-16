# 题目

## 1017 Queueing at Bank (25 分)

Suppose a bank has *K* windows open for service. There is a yellow line in front of the windows which devides the waiting area into two parts. All the customers have to wait in line behind the yellow line, until it is his/her turn to be served and there is a window available. It is assumed that no window can be occupied by a single customer for more than 1 hour.

Now given the arriving time *T* and the processing time *P* of each customer, you are supposed to tell the average waiting time of all the customers.

### Input Specification:

Each input file contains one test case. For each case, the first line contains 2 numbers: *N* (≤104) - the total number of customers, and *K* (≤100) - the number of windows. Then *N* lines follow, each contains 2 times: `HH:MM:SS` - the arriving time, and *P* - the processing time in minutes of a customer. Here `HH` is in the range [00, 23], `MM` and `SS` are both in [00, 59]. It is assumed that no two customers arrives at the same time.

Notice that the bank opens from 08:00 to 17:00. Anyone arrives early will have to wait in line till 08:00, and anyone comes too late (at or after 17:00:01) will not be served nor counted into the average.

### Output Specification:

For each test case, print in one line the average waiting time of all the customers, in minutes and accurate up to 1 decimal place.

### Sample Input:

```in
7 3
07:55:00 16
17:00:01 2
07:59:59 15
08:01:00 60
08:00:00 30
08:00:02 2
08:03:00 10
```

### Sample Output:

```out
8.2
```

# 理解与算法

这道题与[1014](./Advanced%201014.md)基本一致，看起来是多线程，实际上是我们在处理的时候是单线程，因为我们只考虑结束时间最早的那个窗口，并且这里的顾客不是一下子全到齐的，而是一段时间来一个，所以我们要考虑顾客的到达时间，如果最早结束当前业务的那个窗口的时间早于用户到达时间，那么这个顾客不用等待，否则就要等待这两个时间的时间差。

## 代码与实现

```cpp
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
```

