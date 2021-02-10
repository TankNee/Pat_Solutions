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