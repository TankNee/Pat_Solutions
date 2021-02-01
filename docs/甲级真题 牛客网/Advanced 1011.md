# 题目

## Forwards on Weibo (30)

### **题目描述**

Weibo is known as the Chinese version of Twitter.  One user on Weibo may have many followers, and may follow many other users as well.  Hence a social network is formed with followers relations.  When a user makes a post on Weibo, all his/her followers can view and forward his/her post, which can then be forwarded again by their followers.  Now given a social network, you are supposed to calculate the maximum potential amount of forwards for any specific user, assuming that only L levels of indirect followers are counted.

### **输入描述:**

Each input file contains one test case.  For each case, the first line contains 2 positive integers: N (<=1000), the number of users; and L (<=6), the number of levels of indirect followers that are counted.  Hence it is assumed that all the users are numbered from 1 to N.  Then N lines follow, each in the format:
M[i] user_list[i]
where M[i] (<=100) is the total number of people that user[i] follows; and user_list[i] is a list of the M[i] users that are followed by user[i].  It is guaranteed that no one can follow oneself.  All the numbers are separated by a space.
Then finally a positive K is given, followed by K UserID's for query.

### **输出描述:**

For each UserID, you are supposed to print in one line the maximum potential amount of forwards this user can triger, assuming that everyone who can view the initial post will forward it once, and that only L levels of indirect followers are counted.

### **输入例子:**

```
7 3
3 2 3 4
0
2 5 6
2 3 1
2 3 4
1 4
1 5
2 2 6
```

### **输出例子:**

```
4
5
```

# 理解与算法

不难，将关注列表转置一下变成粉丝列表就行，然后进行深度优先搜索，或者广度优先搜索，都可以，注意把控好遍历的深度就行。

使用一个结构体来记录深度会方便很多，不用也可以，稍微麻烦一点。

## 代码与实现

```c
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
struct node {
    int user_id, depth;
};

int main() {
    int N, L, K;
    cin >> N >> L;
    vector<vector<int>> users(N + 1, vector<int>());
    for (int i = 1; i <= N; ++i) {
        int tmp, tmp_user;
        cin >> tmp;
        for (int j = 0; j < tmp; ++j) {
            cin >> tmp_user;
            users[tmp_user].push_back(i);
        }
    }
    cin >> K;
    int tmp, visit[N + 1], depth = 0, cur_user, count = 0;
    queue<node> q;
    for (int i = 0; i < K; ++i) {
        cin >> tmp;
        count = 0;
        depth = 0;
        fill(visit, visit + N + 1, 0);
        visit[tmp] = 1;
        for (int j = 0; j < q.size(); ++j) {
            q.pop();
        }
        for (int j = 0; j < users[tmp].size(); ++j) {
            node n;
            n.user_id = users[tmp][j];
            n.depth = 0;
            q.push(n);
        }
        while (!q.empty() && depth < L) {
            cur_user = q.front().user_id;
            depth = q.front().depth;
            q.pop();
            if (visit[cur_user]) continue;
            visit[cur_user] = 1;
            count++;
            for (int j = 0; j < users[cur_user].size() && depth + 1 < L; ++j) {
                node n;
                n.user_id = users[cur_user][j];
                n.depth = depth + 1;
                q.push(n);
            }
        }
        cout << count << endl;
    }

    return 0;
}
```

