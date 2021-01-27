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