# 题目

1038 Recover the Smallest Number (30 分)

Given a collection of number segments, you are supposed to recover the smallest number from them. For example, given { 32, 321, 3214, 0229, 87 }, we can recover many numbers such like 32-321-3214-0229-87 or 0229-32-87-321-3214 with respect to different orders of combinations of these segments, and the smallest number is 0229-321-3214-32-87.

### Input Specification:

Each input file contains one test case. Each case gives a positive integer *N* (≤104) followed by *N* number segments. Each segment contains a non-negative integer of no more than 8 digits. All the numbers in a line are separated by a space.

### Output Specification:

For each test case, print the smallest number in one line. Notice that the first digit must not be zero.

### Sample Input:

```in
5 32 321 3214 0229 87
```

### Sample Output:

```out
22932132143287
```

# 理解与算法

给出一个字符串列表，求出组成的数字最小的组合。

```cpp
sort(nums.begin(), nums.end(), [](string n1, string n2) {
    return n1 + n2 < n2 + n1;
});
```

因为两个字符串最多只有两个组合，所以只要将两个组合中较小的放在前面即可，而且这里都是数字，所以可以直接用字典序进行比较！

## 代码与实现

```cpp
//
// Created by tanknee on 2021/3/1.
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int main() {
    int N;
    cin >> N;
    vector<string> nums(N);
    for (int i = 0; i < N; ++i) {
        cin >> nums[i];
    }
    sort(nums.begin(), nums.end(), [](string n1, string n2) {
        return n1 + n2 < n2 + n1;
    });
    string res;
    for (int i = 0; i < N; ++i) {
        res.append(nums[i]);
    }
    while (res.length() != 0 && res[0] == '0') {
        res.erase(res.begin());
    }
    if (res.length() == 0) cout << 0;
    cout << res;
    return 0;
}
```