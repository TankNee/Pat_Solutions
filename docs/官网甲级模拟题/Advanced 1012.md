# 题目

## 1012 The Best Rank (25分)

To evaluate the performance of our first year CS majored students, we consider their grades of three courses only: `C` - C Programming Language, `M` - Mathematics (Calculus or Linear Algrbra), and `E` - English. At the mean time, we encourage students by emphasizing on their best ranks -- that is, among the four ranks with respect to the three courses and the average grade, we print the best rank for each student.

For example, The grades of `C`, `M`, `E` and `A` - Average of 4 students are given as the following:

```
StudentID  C  M  E  A
310101     98 85 88 90
310102     70 95 88 84
310103     82 87 94 88
310104     91 91 91 91
```

Then the best ranks for all the students are No.1 since the 1st one has done the best in C Programming Language, while the 2nd one in Mathematics, the 3rd one in English, and the last one in average.

### Input Specification:

Each input file contains one test case. Each case starts with a line containing 2 numbers *N* and *M* (≤2000), which are the total number of students, and the number of students who would check their ranks, respectively. Then *N* lines follow, each contains a student ID which is a string of 6 digits, followed by the three integer grades (in the range of [0, 100]) of that student in the order of `C`, `M` and `E`. Then there are *M* lines, each containing a student ID.

### Output Specification:

For each of the *M* students, print in one line the best rank for him/her, and the symbol of the corresponding rank, separated by a space.

The priorities of the ranking methods are ordered as `A` > `C` > `M` > `E`. Hence if there are two or more ways for a student to obtain the same best rank, output the one with the highest priority.

If a student is not on the grading list, simply output `N/A`.

### Sample Input:

```in
5 6
310101 98 85 88
310102 70 95 88
310103 82 87 94
310104 91 91 91
310105 85 90 90
310101
310102
310103
310104
310105
999999
```

### Sample Output:

```out
1 C
1 M
1 E
1 A
3 A
N/A
```

# 理解与算法

这道题理解起来不难，重点在怎么实现。

写了三四天的PAT，慢慢有点感觉，能用简单的数据结构就用简单的数据结构，不要想着一个庞大的结构体包含你需要的所有状态，这不现实，也不经济，我们应该用足够少的数据量，配合必须的数据容器，来表示全部的信息。

我最开始的想法是用四个数组来表示学生们的成绩，而我们需要对数据进行排序，排序完会丢失学生信息的完整性，就算你用四个结构体来绑定学号和成绩的信息，还是会多很多的冗余信息！

所以我们将学生的信息打包成一个结构体，每次排序之后的排位信息也存储在这个结构体中，并记录这个学生哪门课排名最好！

由上述信息我们这么设计：

```cpp
struct student {
    int id;
    int score[4];
    int rank[4];
    int best;
};
```

- id 学号，因为学号的长度有限制，所以我们可以直接用int类型来存储，如果再大一点我们就用long int，这么做是为了方便快速存取
- score 成绩信息，为了对应不同科目的优先级，0-3分别为A，C，M，E，这样也方便后面计算最佳排名
- rank 每门课的排位信息，与上述成绩score一一对应。
- best 最好的排名信息，值为score与rank数组的一个下标。

遇到的一个问题：

由于存在分数一样的问题，所以如果直接用下标来表示学生成绩的排名就会出现问题，因为一样的分数就应该是一样的排名，所以要和前一个学生进行比较，相同则继承排名！

## 代码与实现[^1]

```cpp
//
// Created by tanknee on 2021/1/25.
//

#include <iostream>
#include <algorithm>

using namespace std;

struct student {
    int id;
    int score[4];
    int rank[4];
    int best;
};
student students[2001];

int exists[1000001], flag = -1;

bool cmp1(student a, student b) { return a.score[flag] > b.score[flag]; }

int main() {
    int N, M, id;
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        cin >> students[i].id >> students[i].score[1] >> students[i].score[2] >> students[i].score[3];
        students[i].score[0] = (students[i].score[1] + students[i].score[2] + students[i].score[3]) / 3.0 + 0.5;
    }
    // 计算学生每门课程的排名
    for (flag = 0; flag <= 3; flag++) {
        sort(students, students + N, cmp1);
        students[0].rank[flag] = 1;
        for (int i = 1; i < N; ++i) {
            students[i].rank[flag] = i + 1;
            // 如果分数相同，那么排名也跟之前的一样
            if (students[i].score[flag] == students[i - 1].score[flag]) {
                students[i].rank[flag] = students[i - 1].rank[flag];
            }
        }
    }
    // 计算每个学生的最好排名
    for (int i = 0; i < N; ++i) {
        exists[students[i].id] = i + 1;
        students[i].best = 0;
        int min_num = students[i].rank[0];
        for (int j = 1; j <= 3; ++j) {
            if (students[i].rank[j] < min_num) {
                min_num = students[i].rank[j];
                students[i].best = j;
            }
        }
    }
    char tmp_chars[5] = {'A', 'C', 'M', 'E'};
    for (int i = 0; i < M; ++i) {
        cin >> id;
        int tmp = exists[id];
        if (tmp) {
            int best = students[tmp - 1].best;
            cout << students[tmp - 1].rank[best] << " " << tmp_chars[best] << endl;
        } else {
            cout << "N/A" << endl;
        }
    }
    return 0;
}
```

[^1]: https://github.com/liuchuo/PAT