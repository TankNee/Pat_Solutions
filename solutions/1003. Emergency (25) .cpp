#include <iostream>
#include <algorithm>
using namespace std;
int n, m, c1, c2;
int e[510][510], weight[510], dis[510], num[510], w[510];
bool visit[510];
const int inf = 99999999;
int main() {
    scanf("%d%d%d%d", &n, &m, &c1, &c2);
    for(int i = 0; i < n; i++)
        scanf("%d", &weight[i]);
    fill(e[0], e[0] + 510 * 510, inf);
    fill(dis, dis + 510, inf);
    int a, b, c;
    for(int i = 0; i < m; i++) {
        scanf("%d%d%d", &a, &b, &c);
        e[a][b] = e[b][a] = c;
    }
    dis[c1] = 0;
    w[c1] = weight[c1];
    num[c1] = 1;
    // 遍历所有城市
    for(int i = 0; i < n; i++) {
        int u = -1, minn = inf;
        for(int j = 0; j < n; j++) {
            // 如果j城市没有被访问过并且到这个城市的距离小于之前的距离，那么就更新最小距离
            if(visit[j] == false && dis[j] < minn) {
                u = j;
                minn = dis[j];
            }
        }
        // 如果还是-1代表是非联通点直接退出
        if(u == -1) break;
        // 这样就遍历完这个
        visit[u] = true;
        for(int v = 0; v < n; v++) {
            if(visit[v] == false && e[u][v] != inf) {
                if(dis[u] + e[u][v] < dis[v]) {
                    dis[v] = dis[u] + e[u][v];
                    num[v] = num[u];
                    w[v] = w[u] + weight[v];
                } else if(dis[u] + e[u][v] == dis[v]) {
                    num[v] = num[v] + num[u];
                    if(w[u] + weight[v] > w[v])
                        w[v] = w[u] + weight[v];
                }
            }
        }
    }
    printf("%d %d", num[c2], w[c2]);
    return 0;
}