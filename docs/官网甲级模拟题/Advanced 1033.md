# 题目

## 1033 To Fill or Not to Fill (25 分)

With highways available, driving a car from Hangzhou to any other city is easy. But since the tank capacity of a car is limited, we have to find gas stations on the way from time to time. Different gas station may give different price. You are asked to carefully design the cheapest route to go.

### Input Specification:

Each input file contains one test case. For each case, the first line contains 4 positive numbers: *C**m**a**x* (≤ 100), the maximum capacity of the tank; *D* (≤30000), the distance between Hangzhou and the destination city; *D**a**v**g* (≤20), the average distance per unit gas that the car can run; and *N* (≤ 500), the total number of gas stations. Then *N* lines follow, each contains a pair of non-negative numbers: *P**i*, the unit gas price, and *D**i* (≤*D*), the distance between this station and Hangzhou, for *i*=1,⋯,*N*. All the numbers in a line are separated by a space.

### Output Specification:

For each test case, print the cheapest price in a line, accurate up to 2 decimal places. It is assumed that the tank is empty at the beginning. If it is impossible to reach the destination, print `The maximum travel distance = X` where `X` is the maximum possible distance the car can run, accurate up to 2 decimal places.

### Sample Input 1:

```in
50 1300 12 8
6.00 1250
7.00 600
7.00 150
7.10 0
7.20 200
7.50 400
7.30 1000
6.85 300
```

### Sample Output 1:

```out
749.17
```

### Sample Input 2:

```
50 1300 12 2
7.10 0
7.00 600
```

### Sample Output 2:

```out
The maximum travel distance = 1200.00
```

# 理解与算法

使用贪心算法，尽可能给油箱加上最便宜的油，如果可达范围内有更便宜的油，那就把油箱加到刚好够抵达那个加油站的油。

遵循这么几条逻辑规则：

1. 将终点看成油价为0，距离为D的加油站，这样可以把终点也纳入考虑。
2. 如果起点处没有加油站，那就直接退出，因为根本走不了。
3. 找出能行驶的最远距离中油价最便宜的那个加油站。
4. 如果有多个加油站油价比当前油箱里的油价便宜，那就选择距离最近的那个作为目标加油站.
5. 如果行驶的最远距离内没有加油站，就直接退出。
6. 要区分油箱里的油能到达的最远距离和加满油能到达的最远距离！
7. 循环迭代的是当前所在的加油站！

## 代码与实现

```cpp
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
```