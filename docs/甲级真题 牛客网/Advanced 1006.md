# 题目

## Cars on Campus (30)

### **题目描述**

Zhejiang University has 6 campuses and a lot of gates.  From each gate we can collect the in/out times and the plate numbers of the cars crossing the gate.  Now with all the information available, you are supposed to tell, at any specific time point, the number of cars parking on campus, and at the end of the day find the cars that have parked for the longest time period.
### **输入描述:**

Each input file contains one test case.  Each case starts with two positive integers N (<= 10000), the number of records, and K (<= 80000) the number of queries.  Then N lines follow, each gives a record in the format
plate_number hh:mm:ss status
where plate_number is a string of 7 English capital letters or 1-digit numbers; hh:mm:ss represents the time point in a day by hour:minute:second, with the earliest time being 00:00:00 and the latest 23:59:59; and status is either in or out.
Note that all times will be within a single day. Each "in" record is paired with the chronologically next record for the same car provided it is an "out" record. Any "in" records that are not paired with an "out" record are ignored, as are "out" records not paired with an "in" record. It is guaranteed that at least one car is well paired in the input, and no car is both "in" and "out" at the same moment. Times are recorded using a 24-hour clock.

Then K lines of queries follow, each gives a time point in the format hh:mm:ss.  Note: the queries are given in ascending order of the times.
### **输出描述:**

For each query, output in a line the total number of cars parking on campus.  The last line of output is supposed to give the plate number of the car that has parked for the longest time period, and the corresponding time length.  If such a car is not unique, then output all of their plate numbers in a line in alphabetical order, separated by a space.
### **输入例子:**

```
16 7
JH007BD 18:00:01 in
ZD00001 11:30:08 out
DB8888A 13:00:00 out
ZA3Q625 23:59:50 out
ZA133CH 10:23:00 in
ZD00001 04:09:59 in
JH007BD 05:09:59 in
ZA3Q625 11:42:01 out
JH007BD 05:10:33 in
ZA3Q625 06:30:50 in
JH007BD 12:23:42 out
ZA3Q625 23:55:00 in
JH007BD 12:24:23 out
ZA133CH 17:11:22 out
JH007BD 18:07:01 out
DB8888A 06:30:50 in
05:10:00
06:30:50
11:00:00
12:23:42
14:00:00
18:00:00
23:59:00
```

### **输出例子:**

```
1
4
5
2
1
0
1
JH007BD ZD00001 07:20:09
```

## 理解与算法

这道题还是有点难度的，理解题目有点困难。

如何理解题目中pair的概念？一个出，一个进入，并且这两个动作之间，这辆车没有其他动作，这样才算正常的一组操作对。由于给出的数据中就有很多这样需要剔除的数据，所以需要先对数据进行提炼。

这里用的是排序，使用algorithm里的sort算法进行排序！不过这里每一个记录都有比较多的数据，所以我们建立了一个结构体：

```cpp
struct record {
    string plate;
    int time;
    string status;
};
```

今天看到别人写的代码才知道原来C++的结构体也可以直接写成员方法，十分方便，所以，利用这个特性，我们直接对这个结构体重构操作符`<`，供给sort函数进行排序。

```cpp
struct record {
    string plate;
    int time;
    string status;

    bool operator<(const record &r) const {
        if (plate != r.plate) {
            return plate < r.plate;
        } else if (time != r.time) {
            return time < r.time;
        } else {
            return status < r.status;
        }
    }
};
```

这样排序的结果就会按照一个优先级来，类似于SQL语言中的`group by`，先按照车牌排序，再在相同的车牌中按照进出时间排序，最后再在相同车牌相同时间的记录中按照进出状态排序。

同样的，两个记录是否构成pair的方法也可以直接在结构体定义里面写！

```cpp
struct record {
    string plate;
    int time;
    string status;

    bool is_paired(const record &r) const {
        return plate == r.plate && time < r.time && status == "in" && r.status == "out";
    }

    bool operator<(const record &r) const {
        if (plate != r.plate) {
            return plate < r.plate;
        } else if (time != r.time) {
            return time < r.time;
        } else {
            return status < r.status;
        }
    }
};
```

然后再来看题目要我们求什么东西：

1. 某个特定时间点校园里的汽车数量

2. 停车总时长最长的车，以及总时长

第一个问题我们可以用set或者map来写，只要维护一个校园里汽车的集合，当有汽车出入时修改维护这个集合就好了。

第二个问题要注意，我们要求的是停车总时间！！！并不是单独的一个时间段，有可能一辆车几进几出，停了很多次，所以他的时间并不只有一段，要把每一段都加起来才是真正的时间！

## 代码与实现

```cpp
//
// Created by tanknee on 2021/1/27.
//

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;


struct record {
    string plate;
    int time;
    string status;

    bool is_paired(const record &r) const {
        return plate == r.plate && time < r.time && status == "in" && r.status == "out";
    }

    bool operator<(const record &r) const {
        if (plate != r.plate) {
            return plate < r.plate;
        } else if (time != r.time) {
            return time < r.time;
        } else {
            return status < r.status;
        }
    }
};

bool cmp(record r1, record r2) {
    return r1.time < r2.time;
}

string print_time(int time_point) {
    char str[50];
    sprintf(str, "%02d:%02d:%02d", time_point / 60 / 60, time_point % (60 * 60) / 60, time_point % 60);
    return string(str);
}

int main() {
    int N, K, last_index = 0, _h, _m, _s, time = 0, cur_time = 0, max_time = 0;
    map<string, record> m;
    map<string, int> time_record_map;
    cin >> N >> K;
    vector<record> records(N, record{}), valid_records;
    vector<string> max_time_records;
    int result[K];
    for (int i = 0; i < N; ++i) {
        cin >> records[i].plate;
        scanf("%d:%d:%d", &_h, &_m, &_s);
        records[i].time = _h * 60 * 60 + _m * 60 + _s;
        cin >> records[i].status;
    }
    sort(records.begin(), records.end());
    for (int i = 0; i < records.size(); ++i) {
        if (i + 1 < records.size() && records[i].is_paired(records[i + 1])) {
            time_record_map[records[i].plate] += records[i + 1].time - records[i].time;
            if (time_record_map[records[i].plate] > max_time) {
                max_time = time_record_map[records[i].plate];
                max_time_records.clear();
                max_time_records.push_back(records[i].plate);
            } else if (time_record_map[records[i].plate] == max_time) {
                max_time_records.push_back(records[i].plate);
            }
            valid_records.push_back(records[i]);
            valid_records.push_back(records[i + 1]);
        }
    }
    sort(valid_records.begin(), valid_records.end(), cmp);
    for (int i = 0; i < K; ++i) {
        scanf("%d:%d:%d", &_h, &_m, &_s);
        cur_time = _h * 60 * 60 + _m * 60 + _s;
        for (int j = last_index; j < valid_records.size(); ++j) {
            if (valid_records[j].time <= cur_time && valid_records[j].time >= time) {
                last_index = j;
                if (valid_records[j].status == "in") {
                    m[valid_records[j].plate] = valid_records[j];
                } else {
                    m.erase(valid_records[j].plate);
                }
            } else if (valid_records[j].time > cur_time) break;
        }
        result[i] = m.size();
        time = cur_time;
    }
    for (int i = 0; i < K; ++i) {
        cout << result[i] << endl;
    }
    for (int i = 0; i < max_time_records.size(); ++i) {
        if (!i) cout << max_time_records[i];
        else cout << " " << max_time_records[i];
    }
    cout << " " << print_time(max_time);
    return 0;
}
```