//
// Created by tanknee on 2/16/2021.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <set>

using namespace std;

struct block {
    int id;
    string title;
    string author;
    vector<string> keywords;
    string publisher;
    int year;
};

int main() {
    int block_num;
    map<string, set<int>> title_map, author_map, keywords_map, publisher_map, year_map;
    cin >> block_num;
    block tmp_block;
    string tmp;
    for (int i = 0; i < block_num; ++i) {
        scanf("%d\n", &tmp_block.id);
        getline(cin, tmp_block.title);
        title_map[tmp_block.title].insert(tmp_block.id);
        getline(cin, tmp_block.author);
        author_map[tmp_block.author].insert(tmp_block.id);
        while (cin >> tmp) {
            keywords_map[tmp].insert(tmp_block.id);
            if (getchar() == '\n') break;
        }
        getline(cin, tmp_block.publisher);
        publisher_map[tmp_block.publisher].insert(tmp_block.id);
        scanf("%d\n", &tmp_block.year);
        year_map[to_string(tmp_block.year)].insert(tmp_block.id);
    }
    int query_num;
    cin >> query_num;
    for (int i = 0; i < query_num; ++i) {
        scanf("%d: ", &block_num);
        getline(cin, tmp);

        printf("%d: %s\n", block_num, tmp.c_str());
        if (year_map.find(tmp) != year_map.end()) {
            for (auto it = year_map[tmp].begin(); it != year_map[tmp].end(); it++) {
                printf("%07d\n", *it);
            }
            continue;
        }
        if (title_map.find(tmp) != title_map.end()) {
            for (auto it = title_map[tmp].begin(); it != title_map[tmp].end(); it++) {
                printf("%07d\n", *it);
            }
            continue;
        }
        if (author_map.find(tmp) != author_map.end()) {
            for (auto it = author_map[tmp].begin(); it != author_map[tmp].end(); it++) {
                printf("%07d\n", *it);
            }
            continue;
        }
        if (keywords_map.find(tmp) != keywords_map.end()) {
            for (auto it = keywords_map[tmp].begin(); it != keywords_map[tmp].end(); it++) {
                printf("%07d\n", *it);
            }
            continue;
        }
        if (publisher_map.find(tmp) != publisher_map.end()) {
            for (auto it = publisher_map[tmp].begin(); it != publisher_map[tmp].end(); it++) {
                printf("%07d\n", *it);
            }
            continue;
        }
        cout << "Not Found" << endl;
    }
    return 0;
}