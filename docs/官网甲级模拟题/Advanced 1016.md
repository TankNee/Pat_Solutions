# 题目

1016 Phone Bills (25 分)

A long-distance telephone company charges its customers by the following rules:

Making a long-distance call costs a certain amount per minute, depending on the time of day when the call is made. When a customer starts connecting a long-distance call, the time will be recorded, and so will be the time when the customer hangs up the phone. Every calendar month, a bill is sent to the customer for each minute called (at a rate determined by the time of day). Your job is to prepare the bills for each month, given a set of phone call records.

### Input Specification:

Each input file contains one test case. Each case has two parts: the rate structure, and the phone call records.

The rate structure consists of a line with 24 non-negative integers denoting the toll (cents/minute) from 00:00 - 01:00, the toll from 01:00 - 02:00, and so on for each hour in the day.

The next line contains a positive number *N* (≤1000), followed by *N* lines of records. Each phone call record consists of the name of the customer (string of up to 20 characters without space), the time and date (`MM:dd:HH:mm`), and the word `on-line` or `off-line`.

For each test case, all dates will be within a single month. Each `on-line` record is paired with the chronologically next record for the same customer provided it is an `off-line` record. Any `on-line` records that are not paired with an `off-line` record are ignored, as are `off-line` records not paired with an `on-line` record. It is guaranteed that at least one call is well paired in the input. You may assume that no two records for the same customer have the same time. Times are recorded using a 24-hour clock.

### Output Specification:

For each test case, you must print a phone bill for each customer.

Bills must be printed in alphabetical order of customers' names. For each customer, first print in a line the name of the customer and the month of the bill in the format shown by the sample. Then for each time period of a call, print in one line the beginning and ending time and date (`dd:HH:mm`), the lasting time (in minute) and the charge of the call. The calls must be listed in chronological order. Finally, print the total charge for the month in the format shown by the sample.

### Sample Input:

```in
10 10 10 10 10 10 20 20 20 15 15 15 15 15 15 15 20 30 20 15 15 10 10 10
10
CYLL 01:01:06:01 on-line
CYLL 01:28:16:05 off-line
CYJJ 01:01:07:00 off-line
CYLL 01:01:08:03 off-line
CYJJ 01:01:05:59 on-line
aaa 01:01:01:03 on-line
aaa 01:02:00:01 on-line
CYLL 01:28:15:41 on-line
aaa 01:05:02:24 on-line
aaa 01:04:23:59 off-line
```

### Sample Output:

```out
CYJJ 01
01:05:59 01:07:00 61 $12.10
Total amount: $12.10
CYLL 01
01:06:01 01:08:03 122 $24.40
28:15:41 28:16:05 24 $3.85
Total amount: $28.25
aaa 01
02:00:01 04:23:59 4318 $638.80
Total amount: $638.80
```

# 理解与算法

将时间转为以秒为单位的一个整形数字，提高比较效率。和之前有一道停车的题目很像，要考虑哪两条数据是匹配的，并且同一天可能有多个通话记录需要处理，这道题比较复杂和繁琐，要有耐心。

另外还需要计算通话费用，因为通话费用是按照通话的时间段进行划分的，不同时间段的价格不同，这里有很多种情况。

### 按照小时来划分

#### 跨小时

![image-20210214115448119](https://img.tanknee.cn/blogpicbed/2021/02/14/2021021494190122e8850.png)

#### 跨小时且中间涵盖一个小时以上

![image-20210214115527633](https://img.tanknee.cn/blogpicbed/2021/02/14/2021021468d1d566187c4.png)

第二种情况我们可以单独计算中间那个被涵盖的小时的费用，然后把剩下的部分转到第一种情况来计算！

### 按照天来划分

#### 跨天

![image-20210214115448119](https://img.tanknee.cn/blogpicbed/2021/02/14/2021021494190122e8850.png)

#### 跨天且中间涵盖一天以上

![image-20210214115527633](https://img.tanknee.cn/blogpicbed/2021/02/14/2021021468d1d566187c4.png)

跟小时的处理思路一样，都是转为第一种来处理！

不过我们还要想明白如何检查出一个通话记录是中间涵盖了一个小时而不是跨小时，毕竟后者的时间范围`[0-2)`小时，与前者的范围`(1,+∞)`是有重叠部分的，所以我们就将前面的范围缩小，先考虑`(2,+∞)`,然后在考虑剩下的部分！

## 代码与实现

```cpp
//
// Created by tanknee on 2021/2/10.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
int rate[24];
double total_day = 0.0;

struct record {
    int time;
    string name, status;

    bool operator<(const record &r) const {
        if (r.name != name) {
            return name < r.name;
        } else if (r.time != time) {
            return time < r.time;
        } else {
            return status < r.status;
        }
    }

    bool is_pair(const record &r) {
        if (r.name == name && time < r.time && status == "on-line" && r.status == "off-line") return true;
        return false;
    }
};

struct item {
    int start, end, duration;
    double fee;
};

double cal_fee(int start, int end) {
    int month = start / (60 * 24 * 31);
    double sum = 0.0;
    start -= 60 * 24 * 31 * month;
    end -= 60 * 24 * 31 * month;
    // 将其限制在两个半天
    if (end - start > 2 * 24 * 60) {
        int del = (end - start) / (24 * 60) - 1;
        start += del * (24 * 60);
        sum += del * total_day;
    }
    int start_day = start / (24 * 60), end_day = end / (24 * 60);
    start -= start_day * 24 * 60;
    end -= end_day * 24 * 60;
    int start_hour = start / 60, end_hour = end / 60;
    if (start_day == end_day) {
        if (start_hour == end_hour) {
            sum += (end - start) * rate[start_hour] / 100.0;
            return sum;
        }
        int hour = start_hour + 1;
        sum += (hour * 60 - start) * rate[start_hour] / 100.0;
        while (hour != end_hour) {
            sum += 60 * rate[hour] / 100.0;
            hour++;
        }
        sum += (end - end_hour * 60) * rate[end_hour] / 100.0;
    } else {
        if (end_day != start_day + 1) {
            sum += total_day;
        }
        int hour = start_hour + 1;
        sum += (hour * 60 - start) * rate[start_hour] / 100.0;
        while (hour <= 24) {
            sum += 60 * rate[hour] / 100.0;
            hour++;
        }
        hour = 0;
        while (hour != end_hour) {
            sum += 60 * rate[hour] / 100.0;
            hour++;
        }
        sum += (end - end_hour * 60) * rate[end_hour] / 100.0;
    }
    return sum;
}

void print_time(int time) {
    int d, h, m;
    d = (time % (31 * 24 * 60)) / (24 * 60);
    h = (time % (31 * 24 * 60)) % (24 * 60) / 60;
    m = (time % (31 * 24 * 60)) % (24 * 60) % 60;
    printf("%02d:%02d:%02d", d, h, m);
}

int main() {
    int N;
    for (int i = 0; i < 24; ++i) {
        cin >> rate[i];
        total_day += 60 * rate[i] / 100.0;
    }
    cin >> N;
    vector<record> records(N, record{});
    map<string, map<int, vector<item>>> m;
    for (int i = 0; i < N; ++i) {
        cin >> records[i].name;
        int mon, d, h, minute;
        scanf("%d:%d:%d:%d", &mon, &d, &h, &minute);
        records[i].time = mon * 60 * 24 * 31 + d * 60 * 24 + h * 60 + minute;
        cin >> records[i].status;
    }
    sort(records.begin(), records.end());
    for (int i = 0; i < N - 1; ++i) {
        if (records[i].is_pair(records[i + 1])) {
            int month = records[i].time / (60 * 24 * 31);
//            if (m[records[i].name][month].empty()) {
//                item it;
//                it.start = records[i].time;
//                it.end = records[i + 1].time;
//                m[records[i].name][month].push_back(it);
//            }
            item it{};
            it.start = records[i].time;
            it.end = records[i + 1].time;
            it.duration = it.end - it.start;
            it.fee = cal_fee(it.start, it.end);
            m[records[i].name][month].push_back(it);
        }
    }
    for (auto it = m.begin(); it != m.end(); it++) {
        for (auto m_it = m[it->first].begin(); m_it != m[it->first].end(); m_it++) {
            printf("%s %02d\n", it->first.c_str(), m_it->first);
            double sum = 0.0;
            for (int i = 0; i < m_it->second.size(); ++i) {
                print_time(m_it->second[i].start);
                cout << " ";
                print_time(m_it->second[i].end);
                printf(" %d $%.2f\n", m_it->second[i].duration, m_it->second[i].fee);
                sum += m_it->second[i].fee;
            }
            printf("Total amount: $%.2f\n", sum);
        }
    }
    return 0;
}
```

