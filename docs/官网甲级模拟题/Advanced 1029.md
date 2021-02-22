# 题目

## 1029 Median (25 分)

Given an increasing sequence S of N integers, the median is the number at the middle position. For example, the median of S1 = { 11, 12, 13, 14 } is 12, and the median of S2 = { 9, 10, 15, 16, 17 } is 15. The median of two sequences is defined to be the median of the nondecreasing sequence which contains all the elements of both sequences. For example, the median of S1 and S2 is 13.

Given two increasing sequences of integers, you are asked to find their median.

### Input Specification:

Each input file contains one test case. Each case occupies 2 lines, each gives the information of a sequence. For each sequence, the first positive integer N (≤2×105) is the size of that sequence. Then N integers follow, separated by a space. It is guaranteed that all the integers are in the range of **long int**.

### Output Specification:

For each test case you should output the median of the two given sequences in a line.

### Sample Input:

```in
4 11 12 13 14
5 9 10 15 16 17
```

### Sample Output:

```out
13
```

# 理解与算法

找中位数，暴力一点直接用sort函数对两个数组进行排序，然后根据：
$$
median_{index} = ceil(sequence.size / 2.0) - 1;
$$
算出中位数的下标，暴力搞定。

## 代码与实现

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    int N;
    long int tmp;
    cin >> N;
    vector<long int> sequence;
    for (int i = 0; i < N; ++i) {
        cin >> tmp;
        sequence.push_back(tmp);
    }
    cin >> N;
    for (int i = 0; i < N; ++i) {
        cin >> tmp;
        sequence.push_back(tmp);
    }
    sort(sequence.begin(), sequence.end());
    int median_index = ceil(sequence.size() / 2.0) - 1;
    cout << sequence[median_index];
    return 0;
}
```

