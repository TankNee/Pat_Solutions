# 题目

## 1049 Counting Ones (30 分)

The task is simple: given any positive integer *N*, you are supposed to count the total number of 1's in the decimal form of the integers from 1 to *N*. For example, given *N* being 12, there are five 1's in 1, 10, 11, and 12.

### Input Specification:

Each input file contains one test case which gives the positive *N* (≤230).

### Output Specification:

For each test case, print the number of 1's in one line.

### Sample Input:

```in
12
```

### Sample Output:

```out
5
```

# 理解与算法

求小于数字N的所有整数中，带有1的个数，且11算两个1 。暴力解可以拿到22分，直接遍历就行。

正确的解法是一位一位的考虑，判断每位为1时其他位的可能形式！并且每次只计算当前选中的那位为1的组合！所以不会有重复计算！

下面考虑三种不同的位取值：

- 选中的当前位是0，例如120，选中0，其实就是选中了个位，而不是选中0这个数字，当个位是1时，只有01，11，21，直到111，一共有12种组合，也就是12*1，再看一个例子102，选中十位，那么就只有10，11，12，一直到19，这么10种组合也就是$1×10$，可见这里的组合数量的规律是0左侧的数字，乘以0所在的位数的基数。
- 当选中的位上的数字是1，例如121，那么相比上一种，就多了121这种组合可能，再看112，选中十位上的1，那么相比上一种就多了110，111，112这么三种可能，所以此处的规律相比上一种就只需要加上1右边的数字再加上1种可能，（0+1，2+1）
- 当选中的位上的数字大于1，例如123，选中3，那么可以取01，11，一直到121，那就是(12 + 1) * 1种。

## 代码与实现

```cpp
#include <iostream>

using namespace std;

int main() {
    int n, left = 0, right = 0, a = 1, now = 1, ans = 0;
    scanf("%d", &n);
    while (n / a) {
        // left是当前选取的数位左边的那串数字，now是当前选取的数位，right是当前选取数位右边的那串数字
        left = n / (a * 10), now = n / a % 10, right = n % a;
        // 而且，由于我们是从右到左计算，且每次都只计算当前数位为1的可能的个数！
        // now==0说明now位只有在left从0~left-1的时候会产生1，所以会产生left次，但是又因为右边会重复从0~999…出现a次
        // 例如120，当now==0时，只有01，11，21...111才会让这一位成为1且小于n
        if (now == 0) ans += left * a;
            // 如果当前位是1，left可以取0-left，所以相比上一步，我们要加一个当now为1的时候右边出现0~right个数导致的now为1的次数
            // 例如113，选中中间的1，那么就可取，010，011，一直到019，再从019一直到113。因为left * a这个式子已经包含了重复的right，所以只需要考虑left最大的时候那个有限的right
        else if (now == 1) ans += left * a + right + 1;
            // 当now>=1时，例如123，选中3，那么可以取01，11，一直到121，那就是(12 + 1) * 1种。
        else ans += (left + 1) * a;
        a = a * 10;
    }
    printf("%d", ans);
    return 0;
}
```