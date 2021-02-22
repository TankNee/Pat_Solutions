# 题目

## 1027 Colors in Mars (20 分)

People in Mars represent the colors in their computers in a similar way as the Earth people. That is, a color is represented by a 6-digit number, where the first 2 digits are for `Red`, the middle 2 digits for `Green`, and the last 2 digits for `Blue`. The only difference is that they use radix 13 (0-9 and A-C) instead of 16. Now given a color in three decimal numbers (each between 0 and 168), you are supposed to output their Mars RGB values.

### Input Specification:

Each input file contains one test case which occupies a line containing the three decimal color values.

### Output Specification:

For each test case you should output the Mars RGB value in the following format: first output `#`, then followed by a 6-digit number where all the English characters must be upper-cased. If a single color is only 1-digit long, you must print a `0` to its left.

### Sample Input:

```in
15 43 71
```

### Sample Output:

```out
#123456
```

# 理解与算法

13进制数的转换，记得考虑英文字符，没什么难度。

## 代码与实现

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

string to_mars(int color) {
    string res;
    int n = color / 13;
    if (n >= 10) {
        res.append(n == 10 ? "A" : n == 11 ? "B" : "C");
    } else res.append(to_string(n));
    n = color % 13;
    if (n >= 10) {
        res.append(n == 10 ? "A" : n == 11 ? "B" : "C");
    } else res.append(to_string(n));
    return res;
}

int main() {
    int R, G, B;
    cin >> R >> G >> B;
    printf("#%s%s%s", to_mars(R).c_str(), to_mars(G).c_str(), to_mars(B).c_str());
    return 0;
}
```

