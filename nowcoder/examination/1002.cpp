//
// Created by tanknee on 2021/1/26.
//

//Dijkstra算法只是给了我们遍历求最短路径的方法，但是通过这个遍历方法我们可以做更多其他的
//事情，而这些就是灵活运用的部分。
//思路：Dijkstra是用来球最短路径的，该题可以把cost当作最短路径来看待，然后就是根据本题因
//地制宜，求出最小成本到达ROM的同时，记录有多少不同的路径以该最小成本到达，其中最优的路径
//是那一条，不需要一下子给出整条路径，只需要有链表能把路径给带出来就行了。
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <limits>
using namespace std;
struct Point {
    int k;//城市编号
    int routes=0;//有几条线路可以到达该点
    int depth=0;//路径中第几个点
    int p=-1;//推荐路线的父节点
    int accum_happy=0;//到该点积累的快乐指数，与depth结合可以计算平均快乐指数
    int accum_cost = numeric_limits<int>::max();
    bool visited = false;
};
vector<Point> points;
map<string, int> Cities;
//map的开销会比较大，内存占用也比较大，所以使用一个map，其他都可以用vector了，
//由城市名得到索引。
vector<string> Index;//与Cities配合，它是由索引得到城市名
vector<int> Happiness;
vector < vector<int>> Costs;
vector<vector<int>> adjacency;
void print_path(int end);
void dijkstra(int N);
inline int find_least(vector<Point> &points) {
    int index = 0, minor = numeric_limits<int>::max();
    for (int j = 1;j < points.size();++j) {
        if (points[j].visited==false&&points[j].accum_cost < minor) {
            minor = points[j].accum_cost;
            index = j;
        }
    }
    return index;
}
inline void change(int least, int j) {
    points[j].p = least;
    points[j].accum_cost = points[least].accum_cost + Costs[least][j];
    points[j].accum_happy = points[least].accum_happy + Happiness[j];
    points[j].depth = points[least].depth + 1;
    points[j].routes = points[least].routes;
}
inline void update(int least, int j) {
    Point &former = points[least];
    Point &current = points[j];
    current.routes += former.routes;
    if (former.accum_happy + Happiness[j]>current.accum_happy) {
        current.accum_happy = former.accum_happy + Happiness[j];
        current.p = least;
        current.depth = former.depth + 1;
    }
    else if (former.accum_happy + Happiness[j] == current.accum_happy) {
        if (former.depth + 1 > current.depth) {
            current.p = least;
            current.depth = former.depth + 1;
        }
    }
}
void dijkstra(int N) {
    for (int i = 0;i < N;++i) {
        int least = find_least(points);
        Point &least_p = points[least];
        least_p.visited = true;
        vector<int> branch = adjacency[least];
        for (int j = 0;j < branch.size();++j) {
            if (least_p.accum_cost + Costs[least][branch[j]] < points[branch[j]].accum_cost) {
                change(least, branch[j]);
            }
            else if (least_p.accum_cost + Costs[least][branch[j]] == points[branch[j]].accum_cost) {
                update(least, branch[j]);
            }
        }
    }
}
int main() {
    int N, K;
    string start;
    while (cin >> N >> K >> start) {
        points.resize(N);
        points[0].accum_cost = 0;
        points[0].routes = 1;
        Index.resize(N);
        Happiness.resize(N);
        Costs.resize(N, vector<int>(N));
        adjacency.resize(N);
        Cities[start] = 0;
        Index[0] = start;
        Happiness[0] = 0;
        string city;
        int happy;
        for (int i = 1;i < N;++i) {
            points[i].k = i;
            cin >> city >> happy;
            Cities[city] = i;
            Index[i] = city;
            Happiness[i] = happy;
        }
        string city1, city2;
        int cost;
        for (int i = 0;i < K;++i) {
            cin >> city1 >> city2 >> cost;
            Costs[Cities[city1]][Cities[city2]] = cost;
            Costs[Cities[city2]][Cities[city1]] = cost;
            adjacency[Cities[city1]].push_back(Cities[city2]);
            adjacency[Cities[city2]].push_back(Cities[city1]);
        }

        //至此数据接收完毕
        dijkstra(N);
        int end = Cities["ROM"];
        cout << points[end].routes << " " << points[end].accum_cost << " " << points[end].accum_happy << " " << points[end].accum_happy / points[end].depth << endl;
        print_path(end);
    }
}
void print_path(int end) {
    Point p = points[end];
    if (p.p != -1) {
        print_path(p.p);
        cout << Index[end];
        if (Cities["ROM"] != end) {
            cout << "->";
        }
        else {
            cout << endl;
        }
    }
    else {
        cout << Index[end] << "->";
    }
}

/**
 *
#include <iostream>
#include <map>
#include <vector>
#include <climits>

using namespace std;

struct node {
    string name;
    int happiness{};
};
vector<node> cities(200, node{});

int get_index(const string &name) {
    for (int i = 1; i < cities.size(); ++i) {
        if (cities[i].name == name) return i;
    }
    return 0;
}

int get_sum_happiness(vector<int> routes) {
    int sum = 0;
    for (int i = 1; i < routes.size(); ++i) {
        sum += cities[routes[i]].happiness;
    }
    return sum;
}

int main() {
    string startup;
    int N, K, count = 0, rom_index, happiness_sum = 0;
    cin >> N >> K >> startup;
    vector<vector<int>> roads(N, vector<int>(N, INT_MAX));
    vector<vector<int>> traces(N, vector<int>(1, 0));
    int dis[N];
    bool visit[N];
    fill(dis, dis + N, INT_MAX);
    fill(visit, visit + N, false);
    cities[0].name = startup;
    cities[0].happiness = 0;
    for (int i = 1; i < N; ++i) {
        cin >> cities[i].name >> cities[i].happiness;
    }
    rom_index = get_index("ROM");
    for (int i = 0; i < K; ++i) {
        string t1, t2;
        int tmp, i1, i2;
        cin >> t1 >> t2 >> tmp;
        i1 = get_index(t1);
        i2 = get_index(t2);
        roads[i1][i2] = tmp;
        roads[i2][i1] = tmp;
    }
    dis[0] = 0;
    // 目标是找到罗马最短的路，如果长度相同再考虑其他的东西
    for (int i = 0; i < N; ++i) {
        int u = -1, min_dis = INT_MAX;
        for (int j = 0; j < N; ++j) {
            if (!visit[j] && dis[j] < min_dis) {
                min_dis = dis[j];
                u = j;
            }
        }
        if (u == -1) break;
        visit[u] = true;
        for (int j = 0; j < N; ++j) {
            if (!visit[j] && roads[u][j] != INT_MAX) {
                if (dis[u] + roads[u][j] < dis[j]) {
                    dis[j] = dis[u] + roads[u][j];
                    traces[j].clear();
                    for (int k = 0; k < traces[u].size(); ++k) {
                        traces[j].emplace_back(traces[u][k]);
                    }
                    traces[j].emplace_back(j);
                    if (cities[j].name == "ROM") count = 1;
                } else if (dis[u] + roads[u][j] == dis[j] && cities[j].name == "ROM") {
                    count++;
                    int sum1 = get_sum_happiness(traces[j]);
                    traces[u].emplace_back(j);
                    int sum2 = get_sum_happiness(traces[u]);
                    traces[u].pop_back();
                    if (sum2 > sum1 || (sum1 == sum2 && (traces[u].size() + 1 < traces[j].size()))) {
                        traces[j].clear();
                        for (int k = 0; k < traces[u].size(); ++k) {
                            traces[j].emplace_back(traces[u][k]);
                        }
                        traces[j].emplace_back(j);
                    }
                }
            }
        }
    }
    for (int i = 1; i < traces[rom_index].size(); ++i) {
        happiness_sum += cities[traces[rom_index][i]].happiness;
    }
    cout << count << " " << dis[rom_index] << " " << happiness_sum << " "
         << happiness_sum / (traces[rom_index].size() - 1) << endl;
    cout << cities[traces[rom_index][0]].name;
    for (int i = 1; i < traces[rom_index].size(); ++i) {
        cout << "->" << cities[traces[rom_index][i]].name;
    }

    return 0;
}
**/
