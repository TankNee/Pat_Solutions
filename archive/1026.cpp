//
// Created by tanknee on 2/18/2021.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
struct person {
    int arrive, start, time;
    bool vip;
}tempperson;
struct tablenode {
    int end = 8 * 3600, num;
    bool vip;
};
bool cmp1(person a, person b) {
    return a.arrive < b.arrive;
}
bool cmp2(person a, person b) {
    return a.start < b.start;
}
vector<person> player;
vector<tablenode> table;
void alloctable(int personid, int tableid) {
    if(player[personid].arrive <= table[tableid].end)
        player[personid].start = table[tableid].end;
    else
        player[personid].start = player[personid].arrive;
    table[tableid].end = player[personid].start + player[personid].time;
    table[tableid].num++;
}
int findnextvip(int vipid) {
    vipid++;
    while(vipid < player.size() && player[vipid].vip == false) vipid++;
    return vipid;
}
int main() {
    int n, k, m, viptable;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int h, m, s, temptime, flag;
        scanf("%d:%d:%d %d %d", &h, &m, &s, &temptime, &flag);
        tempperson.arrive = h * 3600 + m * 60 + s;
        tempperson.start = 21 * 3600;
        if(tempperson.arrive >= 21 * 3600) continue;
        tempperson.time = temptime <= 120 ? temptime * 60 : 7200;
        tempperson.vip = ((flag == 1) ? true : false);
        player.push_back(tempperson);
    }
    scanf("%d%d", &k, &m);
    table.resize(k + 1);
    for(int i = 0; i < m; i++) {
        scanf("%d", &viptable);
        table[viptable].vip = true;
    }
    sort(player.begin(), player.end(), cmp1);
    int i = 0, vipid = -1;
    vipid = findnextvip(vipid);
    while(i < player.size()) {
        int index = -1, minendtime = 999999999;
        for(int j = 1; j <= k; j++) {
            if(table[j].end < minendtime) {
                minendtime = table[j].end;
                index = j;
            }
        }
        if(table[index].end >= 21 * 3600) break;
        if(player[i].vip == true && i < vipid) {
            i++;
            continue;
        }
        if(table[index].vip == true) {
            if(player[i].vip == true) {
                alloctable(i, index);
                if(vipid == i) vipid = findnextvip(vipid);
                i++;
            } else {
                if(vipid < player.size() && player[vipid].arrive <= table[index].end) {
                    alloctable(vipid, index);
                    vipid = findnextvip(vipid);
                } else {
                    alloctable(i, index);
                    i++;
                }
            }
        } else {
            if(player[i].vip == false) {
                alloctable(i, index);
                i++;
            } else {
                int vipindex = -1, minvipendtime = 999999999;
                for(int j = 1; j <= k; j++) {
                    if(table[j].vip == true && table[j].end < minvipendtime) {
                        minvipendtime = table[j].end;
                        vipindex = j;
                    }
                }
                if(vipindex != -1 && player[i].arrive >= table[vipindex].end) {
                    alloctable(i, vipindex);
                    if(vipid == i) vipid = findnextvip(vipid);
                    i++;
                } else {
                    alloctable(i, index);
                    if(vipid == i) vipid = findnextvip(vipid);
                    i++;
                }
            }
        }
    }
    sort(player.begin(), player.end(), cmp2);
    for(i = 0; i < player.size() && player[i].start < 21 * 3600; i++) {
        printf("%02d:%02d:%02d ", player[i].arrive / 3600, player[i].arrive % 3600 / 60, player[i].arrive % 60);
        printf("%02d:%02d:%02d ", player[i].start / 3600, player[i].start % 3600 / 60, player[i].start % 60);
        printf("%.0f\n", round((player[i].start - player[i].arrive) / 60.0));
    }
    for(int i = 1; i <= k; i++) {
        if(i != 1) printf(" ");
        printf("%d", table[i].num);
    }
    return 0;
}

/**
 *
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct customer {
    int arrive_time, play_time, serving_time, wait_time;
    int is_vip;
    bool is_arranged;
};

void print_time(customer c) {
    int h, m, s;
    h = c.arrive_time / (60 * 60);
    m = (c.arrive_time % (60 * 60)) / 60;
    s = (c.arrive_time % (60 * 60)) % 60;
    printf("%02d:%02d:%02d ", h, m, s);
    h = c.serving_time / (60 * 60);
    m = (c.serving_time % (60 * 60)) / 60;
    s = (c.serving_time % (60 * 60)) % 60;
    printf("%02d:%02d:%02d ", h, m, s);
    printf("%.0f\n", round(c.wait_time / 60.0));
}

int main() {
    int N, table_num, vip_table_num;
    cin >> N;
    vector<customer> customers(N, customer{});
    vector<int> tables, table_count;
    for (int i = 0; i < N; ++i) {
        int h, m, s;
        scanf("%d:%d:%d", &h, &m, &s);
        customers[i].arrive_time = h * 60 * 60 + m * 60 + s;
        cin >> customers[i].play_time;
        customers[i].play_time *= 60;
        cin >> customers[i].is_vip;
        customers[i].is_arranged = false;
    }
    sort(customers.begin(), customers.end(), [](customer c1, customer c2) { return c1.arrive_time < c2.arrive_time; });
    cin >> table_num >> vip_table_num;
    tables.resize(table_num, 1);
    table_count.resize(table_num);
    for (int i = 0; i < vip_table_num; ++i) {
        int index;
        cin >> index;
        tables[index - 1] = -1;
    }
    int i;
    for (i = 0; i < N; ++i) {
        if (customers[i].is_arranged || customers[i].play_time > 2 * 60 * 60) continue;

        int table_index = 0, min_time = abs(tables[0]);
        for (int j = 1; j < table_num; ++j) {
            if (abs(tables[j]) < abs(min_time)) {
                min_time = abs(tables[j]);
                table_index = j;
            }
        }
        int flag = tables[table_index] > 0 ? 1 : -1;
        if (min_time >= 21 * 60 * 60) break;
        // 如果最早释放的那张桌子是vip桌，且接下来等待队列中有vip，那么就将这张桌子给他。
        if (tables[table_index] < 0) {
            int tmp = i;
            while (!customers[tmp].is_vip && tmp < N) tmp++;
            if (tmp < N && tmp != i && customers[tmp].is_vip && customers[tmp].arrive_time <= min_time) {
                customers[tmp].serving_time = flag * tables[table_index];
                tables[table_index] += flag * customers[tmp].play_time;
                customers[tmp].wait_time = customers[tmp].serving_time - customers[tmp].arrive_time;
                customers[tmp].is_arranged = true;
                table_count[table_index]++;

                i--;
                continue;
            }
        }
        if (min_time <= customers[i].arrive_time) {
            tables[table_index] = flag * (customers[i].arrive_time + customers[i].play_time);
            customers[i].serving_time = customers[i].arrive_time;
        } else {
            customers[i].serving_time = flag * tables[table_index];
            tables[table_index] += flag * customers[i].play_time;
            customers[i].wait_time = customers[i].serving_time - customers[i].arrive_time;
        }
        table_count[table_index]++;
    }
    sort(customers.begin(), customers.end(),
         [](customer c1, customer c2) { return c1.serving_time < c2.serving_time; });
    for (int j = customers.size() - i; j < customers.size(); ++j) {
        print_time(customers[j]);
    }
    for (int j = 0; j < table_count.size(); ++j) {
        cout << table_count[j];
        if (j != table_count.size() - 1) cout << " ";
    }
    return 0;
}
**/