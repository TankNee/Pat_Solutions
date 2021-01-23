//
// Created by tanknee on 2021/1/23.
//

#include <iostream>

using namespace std;

/**
 * 判断时间1是否大于时间2，如果大于则返回true，小于返回false，不存在相同的情况
 * @param time_1
 * @param time_2
 * @return compared result
 */
bool compare_time(const string& time_1, const string& time_2) {
    if (time_1.substr(0, 2) > time_2.substr(0, 2)) {
        return true;
    } else if (time_1.substr(0, 2) == time_2.substr(0, 2)) {
        if (time_1.substr(3, 2) > time_2.substr(3, 2)) {
            return true;
        } else if (time_1.substr(3, 2) == time_2.substr(3, 2)) {
            if (time_1.substr(6, 2) > time_2.substr(6, 2)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    string earliest_in_people, earliest_in_time, last_out_people, last_out_time, people, in_time, out_time;
    int count;
    cin >> count;
    cin >> earliest_in_people >> earliest_in_time >> last_out_time;
    last_out_people = earliest_in_people;
    for (int i = 1; i < count; ++i) {
        cin >> people >> in_time >> out_time;
        if (!compare_time(in_time, earliest_in_time)) {
            earliest_in_time = in_time;
            earliest_in_people = people;
        }
        if (compare_time(out_time, last_out_time)) {
            last_out_time = out_time;
            last_out_people = people;
        }
    }
    cout << earliest_in_people << " " << last_out_people;
    return 0;
}