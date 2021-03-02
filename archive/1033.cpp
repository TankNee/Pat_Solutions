//
// Created by tanknee on 3/1/2021.
//

#include <cstdio>
#include <algorithm>

using namespace std;

const double INF = 10000.00;

struct Station {
    double price;
    double distance;
} station[500];

int n;
double c, d, di;

bool cmp(Station s1, Station s2) {
    return s1.distance < s2.distance;
}

int main() {
    scanf("%lf %lf %lf %d", &c, &d, &di, &n);
    for (int i = 0; i < n; i++)
        scanf("%lf %lf", &station[i].price, &station[i].distance);
    // 将终点看成油价为0，距离为d的加油站
    station[n].price = 0.0;
    station[n].distance = d;
    // 将全部加油站按照距离排序
    sort(station, station + n, cmp);
    // 如果最近的加油站的距离不是0，那么车子就无法启动，直接结束程序
    if (station[0].distance != 0.0) {
        printf("The maximum travel distance = 0.00\n");
        return 0;
    }
    // 记录当前抵达的加油站，当前的开销，以及当下油箱里还有多少油
    int curs = 0;
    double cost = 0.00;
    double curgas = 0.0;
    // 只要当前的加油站编号小于总的加油站的数量，就可以继续循环
    while (curs < n) {
        // 从当前加油站出发，携带一整箱汽油，所能到达的最远距离
        double maxrun = station[curs].distance + c * di;
        int k = curs;
        double minprice = INF;
        // 找出能行驶的最远距离中油价最便宜的那个加油站
        // 如果有加油站的油价比当前所在的加油站的油价还要便宜，那么直接选定该加油站
        // 如果存在多个这样的加油站，那么就选择距离最近的那个加油站作为目标！
        for (int i = curs + 1; i <= n && station[i].distance <= maxrun; i++) {
            if (station[i].price < minprice) {
                k = i;
                minprice = station[i].price;
                if (minprice < station[curs].price)
                    break;
            }
        }
        // 如果K==curs说明所能到达的最远距离以内没有任何可以抵达的加油站，直接输出距离
        if (k == curs) {
            printf("The maximum travel distance = %.2lf\n", maxrun);
            return 0;
        }
        if (minprice < station[curs].price) {
            // 先算出当前油箱里的油可以到达的最远距离
            int temp = station[curs].distance + curgas * di;
            // 如果这个最远距离可以抵达目标加油站，那么就算出到达加油站时候的油
            if (temp >= station[k].distance) {
                curgas -= (station[k].distance - station[curs].distance) / di;
            } else {
                // 如果这个最远距离小于目标加油站，那么就在当前加油站加到刚好可以到那个加油站的油
                // 因为根据上面的算法，运行到此处时，只要加满油肯定可以到达那个加油站，所以不用考虑边缘case
                cost += (station[k].distance - temp) / di * station[curs].price;
                curgas = 0.0;
            }
        } else {
            // 如果下一个加油站的油价比当前所在加油站的油更贵，那就应该多用当前加油站的油，所以要在curs加油站把油加满
            // 然后再去计算抵达下一个加油站的时剩余的油量！
            cost += (c - curgas) * station[curs].price;
            curgas = c - (station[k].distance - station[curs].distance) / di;
        }
        // 完成上面的判断后汽车就抵达下一个加油站K
        curs = k;
    }
    printf("%.2lf\n", cost);
    return 0;
}



