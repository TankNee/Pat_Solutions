# 题目

## 1025 PAT Ranking (25 分)

Programming Ability Test (PAT) is organized by the College of Computer Science and Technology of Zhejiang University. Each test is supposed to run simultaneously in several places, and the ranklists will be merged immediately after the test. Now it is your job to write a program to correctly merge all the ranklists and generate the final rank.

### Input Specification:

Each input file contains one test case. For each case, the first line contains a positive number *N* (≤100), the number of test locations. Then *N* ranklists follow, each starts with a line containing a positive integer *K* (≤300), the number of testees, and then *K* lines containing the registration number (a 13-digit number) and the total score of each testee. All the numbers in a line are separated by a space.

### Output Specification:

For each test case, first print in one line the total number of testees. Then print the final ranklist in the following format:

```
registration_number final_rank location_number local_rank
```

The locations are numbered from 1 to *N*. The output must be sorted in nondecreasing order of the final ranks. The testees with the same score must have the same rank, and the output must be sorted in nondecreasing order of their registration numbers.

### Sample Input:

```in
2
5
1234567890001 95
1234567890005 100
1234567890003 95
1234567890002 77
1234567890004 85
4
1234567890013 65
1234567890011 25
1234567890014 100
1234567890012 85
```

### Sample Output:

```out
9
1234567890005 1 1 1
1234567890014 1 2 1
1234567890001 3 1 2
1234567890003 3 1 2
1234567890004 5 1 4
1234567890012 5 2 2
1234567890002 7 1 5
1234567890013 8 2 3
1234567890011 9 2 4
```

# 理解与算法

又是一道排序题，写好比较函数就行，把握好排序的要求以及输出格式！还有要记得排序要在所有元素全部进入数组之后再排序！

## 代码与实现

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct testee {
    string registration_number;
    int score;
    int location;
    int final_rank, local_rank;
};

int main() {
    int N, count = 0, num;
    cin >> N;
    vector<vector<testee>> locations(N);
    for (int i = 0; i < N; ++i) {
        cin >> num;
        for (int j = 0; j < num; ++j) {
            testee t;
            cin >> t.registration_number >> t.score;
            t.location = i + 1;
            locations[i].push_back(t);
        }
        count += num;
    }
    vector<testee> final;
    for (int i = 0; i < N; ++i) {
        sort(locations[i].begin(), locations[i].end(), [](const testee& t1, const testee& t2) { return t1.score > t2.score; });
        locations[i][0].local_rank = 1;
        final.emplace_back(locations[i][0]);
        for (int j = 1; j < locations[i].size(); ++j) {
            if (locations[i][j].score == locations[i][j - 1].score) {
                locations[i][j].local_rank = locations[i][j - 1].local_rank;
            } else {
                locations[i][j].local_rank = j+1;
            }
            final.emplace_back(locations[i][j]);
        }
    }
    printf("%d\n", count);
    sort(final.begin(), final.end(), [](const testee& t1, const testee& t2) {
        if (t1.score != t2.score) {
            return t1.score > t2.score;
        } else {
            return t1.registration_number < t2.registration_number;
        }
    });
    final[0].final_rank = 1;
    printf("%s %d %d %d\n", final[0].registration_number.c_str(), final[0].final_rank, final[0].location,
           final[0].local_rank);
    for (int j = 1; j < final.size(); ++j) {
        if (final[j].score == final[j - 1].score) {
            final[j].final_rank = final[j - 1].final_rank;
        } else {
            final[j].final_rank = j+1;
        }
        printf("%s %d %d %d\n", final[j].registration_number.c_str(), final[j].final_rank, final[j].location,
               final[j].local_rank);
    }

    return 0;
}
```

