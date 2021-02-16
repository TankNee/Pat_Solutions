# 题目

## 1014 Waiting in Line (30 分)

Suppose a bank has *N* windows open for service. There is a yellow line in front of the windows which devides the waiting area into two parts. The rules for the customers to wait in line are:

- The space inside the yellow line in front of each window is enough to contain a line with *M* customers. Hence when all the *N* lines are full, all the customers after (and including) the (*N**M*+1)st one will have to wait in a line behind the yellow line.
- Each customer will choose the shortest line to wait in when crossing the yellow line. If there are two or more lines with the same length, the customer will always choose the window with the smallest number.
- *C**u**s**t**o**m**e**r**i* will take *T**i* minutes to have his/her transaction processed.
- The first *N* customers are assumed to be served at 8:00am.

Now given the processing time of each customer, you are supposed to tell the exact time at which a customer has his/her business done.

For example, suppose that a bank has 2 windows and each window may have 2 customers waiting inside the yellow line. There are 5 customers waiting with transactions taking 1, 2, 6, 4 and 3 minutes, respectively. At 08:00 in the morning, *c**u**s**t**o**m**e**r*1 is served at *w**i**n**d**o**w*1 while *c**u**s**t**o**m**e**r*2 is served at *w**i**n**d**o**w*2. *C**u**s**t**o**m**e**r*3 will wait in front of *w**i**n**d**o**w*1 and *c**u**s**t**o**m**e**r*4 will wait in front of *w**i**n**d**o**w*2. *C**u**s**t**o**m**e**r*5 will wait behind the yellow line.

At 08:01, *c**u**s**t**o**m**e**r*1 is done and *c**u**s**t**o**m**e**r*5 enters the line in front of *w**i**n**d**o**w*1 since that line seems shorter now. *C**u**s**t**o**m**e**r*2 will leave at 08:02, *c**u**s**t**o**m**e**r*4 at 08:06, *c**u**s**t**o**m**e**r*3 at 08:07, and finally *c**u**s**t**o**m**e**r*5 at 08:10.

### Input Specification:

Each input file contains one test case. Each case starts with a line containing 4 positive integers: *N* (≤20, number of windows), *M* (≤10, the maximum capacity of each line inside the yellow line), *K* (≤1000, number of customers), and *Q* (≤1000, number of customer queries).

The next line contains *K* positive integers, which are the processing time of the *K* customers.

The last line contains *Q* positive integers, which represent the customers who are asking about the time they can have their transactions done. The customers are numbered from 1 to *K*.

### Output Specification:

For each of the *Q* customers, print in one line the time at which his/her transaction is finished, in the format `HH:MM` where `HH` is in [08, 17] and `MM` is in [00, 59]. Note that since the bank is closed everyday after 17:00, for those customers who cannot be served before 17:00, you must output `Sorry` instead.

### Sample Input:

```in
2 2 7 5
1 2 6 4 3 534 2
3 4 5 6 7
```

### Sample Output:

```out
08:07
08:06
08:10
17:00
Sorry
```

# 理解与算法

一个排队的模型，每个窗口同一时间只能处理一个客户的事物，该用户之后排队的人数有限，这部分排队的人就是 yellow line以内的人，yellow line 之外的人没有固定的队伍。

这道题的难点在于看似有多个窗口，需要处理很多并行的事物，其实不然，除了第一次要给每个窗口都填充满之外，剩下的循环中，只需要考虑 pop 时间最短的那个窗口！也就是队伍向前挪的时间最早的那个窗口。

## 代码与实现

```cpp
//
// Created by tanknee on 2021/2/8.
//

#include <iostream>
#include <queue>
#include <vector>

using namespace std;
struct node {
    int poptime, endtime;
    queue<int> q;
};

int main() {
    int n, m, k, q, index = 1;
    scanf("%d%d%d%d", &n, &m, &k, &q);
    vector<int> time(k + 1), result(k + 1);
    for (int i = 1; i <= k; i++) {
        scanf("%d", &time[i]);
    }
    vector<node> window(n + 1);
    vector<bool> sorry(k + 1, false);
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (index <= k) {
                window[j].q.push(time[index]);
                if (window[j].endtime >= 540)
                    sorry[index] = true;
                window[j].endtime += time[index];
                if (i == 1)
                    window[j].poptime = window[j].endtime;
                result[index] = window[j].endtime;
                index++;
            }

        }
    }
    while (index <= k) {
        int tempmin = window[1].poptime, tempwindow = 1;
        for (int i = 2; i <= n; i++) {
            if (window[i].poptime < tempmin) {
                tempwindow = i;
                tempmin = window[i].poptime;
            }
        }
        window[tempwindow].q.pop();
        window[tempwindow].q.push(time[index]);
        window[tempwindow].poptime += window[tempwindow].q.front();
        if (window[tempwindow].endtime >= 540)
            sorry[index] = true;
        window[tempwindow].endtime += time[index];
        result[index] = window[tempwindow].endtime;
        index++;
    }
    for (int i = 1; i <= q; i++) {
        int query, minute;
        scanf("%d", &query);
        minute = result[query];
        if (sorry[query] == true) {
            printf("Sorry\n");
        } else {
            printf("%02d:%02d\n", (minute + 480) / 60, (minute + 480) % 60);
        }
    }
    return 0;
}
```

