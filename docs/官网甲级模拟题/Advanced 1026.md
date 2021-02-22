# 题目

## 1026 Table Tennis (30 分)

A table tennis club has N tables available to the public. The tables are numbered from 1 to N. For any pair of players, if there are some tables open when they arrive, they will be assigned to the available table with the smallest number. If all the tables are occupied, they will have to wait in a queue. It is assumed that every pair of players can play for at most 2 hours.

Your job is to count for everyone in queue their waiting time, and for each table the number of players it has served for the day.

One thing that makes this procedure a bit complicated is that the club reserves some tables for their VIP members. When a VIP table is open, the first VIP pair in the queue will have the privilege to take it. However, if there is no VIP in the queue, the next pair of players can take it. On the other hand, if when it is the turn of a VIP pair, yet no VIP table is available, they can be assigned as any ordinary players.

### Input Specification:

Each input file contains one test case. For each case, the first line contains an integer `N` (≤10000) - the total number of pairs of players. Then `N` lines follow, each contains 2 times and a VIP tag: `HH:MM:SS` - the arriving time, `P` - the playing time in minutes of a pair of players, and `tag` - which is 1 if they hold a VIP card, or 0 if not. It is guaranteed that the arriving time is between 08:00:00 and 21:00:00 while the club is open. It is assumed that no two customers arrives at the same time. Following the players' info, there are 2 positive integers: `K` (≤100) - the number of tables, and `M` (< K) - the number of VIP tables. The last line contains `M` table numbers.

### Output Specification:

For each test case, first print the arriving time, serving time and the waiting time for each pair of players in the format shown by the sample. Then print in a line the number of players served by each table. Notice that the output must be listed in chronological order of the serving time. The waiting time must be rounded up to an integer minute(s). If one cannot get a table before the closing time, their information must NOT be printed.

### Sample Input:

```in
9
20:52:00 10 0
08:00:00 20 0
08:02:00 30 0
20:51:00 10 0
08:10:00 5 0
08:12:00 10 1
20:50:00 10 0
08:01:30 15 1
20:53:00 10 1
3 1
2
```

### Sample Output:

```out
08:00:00 08:00:00 0
08:01:30 08:01:30 0
08:02:00 08:02:00 0
08:12:00 08:16:30 5
08:10:00 08:20:00 10
20:50:00 20:50:00 0
20:51:00 20:51:00 0
20:52:00 20:52:00 0
3 3 2
```

# 理解与算法

这里大部分的思路和之前银行排队问题差不多，不过因为有VIP客户的存在，所以要多考虑VIP出现时是要插队的，这里插队的特定条件是：

**先到的人是非VIP，但此时没有桌子可用，直到下一张桌子被释放的时间段中，有VIP用户抵达，那么就会被插队！**

可见只有这种情况需要特殊考量，其他都没什么区别！

## 代码与实现

```cpp
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
```

