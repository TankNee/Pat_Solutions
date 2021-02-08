//
// Created by tanknee on 2021/2/7.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
struct bundle {
    int weight;
    int id;
    int rank;
};

int main() {
    int people_num, mice_num;
    cin >> people_num >> mice_num;
    vector<bundle> people(people_num, bundle{});
    vector<bundle> tmp_list(people_num, bundle{});
    for (int i = 0; i < people_num; ++i) {
        cin >> people[i].weight;
        people[i].id = i;
    }
    for (int i = 0; i < people_num; ++i) {
        int tmp;
        cin >> tmp;
        tmp_list[i] = people[tmp];
    }
    vector<bundle> new_list;
    while (true) {
        new_list.clear();
        int rank = ceil(tmp_list.size() / (mice_num * 1.0)) + 1;
        for (int i = 0; i < tmp_list.size(); i += mice_num) {
            int length = i + mice_num > tmp_list.size() ? tmp_list.size() - i : mice_num;
            make_heap(tmp_list.begin() + i, tmp_list.begin() + i + length,
                      [](bundle b1, bundle b2) { return b1.weight < b2.weight; });
            new_list.push_back(*(tmp_list.begin() + i));
            for (int j = i + 1; j < i + length; ++j) {
                people[tmp_list[j].id].rank = rank;
            }
        }
        if (new_list.size() == 1) {
            people[new_list[0].id].rank = 1;
            break;
        }
        tmp_list = new_list;
    }
    for (int i = 0; i < people_num; ++i) {
        cout << people[i].rank;
        if (i != people_num - 1) cout << " ";
    }
    return 0;
}