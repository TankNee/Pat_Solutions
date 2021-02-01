# 题目

## 1007 Maximum Subsequence Sum (25分)

Given a sequence of *K* integers { *N*1, *N*2, ..., *N**K* }. A continuous subsequence is defined to be { *N**i*, *N**i*+1, ..., *N**j* } where 1≤*i*≤*j*≤*K*. The Maximum Subsequence is the continuous subsequence which has the largest sum of its elements. For example, given sequence { -2, 11, -4, 13, -5, -2 }, its maximum subsequence is { 11, -4, 13 } with the largest sum being 20.

Now you are supposed to find the largest sum, together with the first and the last numbers of the maximum subsequence.

### Input Specification:

Each input file contains one test case. Each case occupies two lines. The first line contains a positive integer *K* (≤10000). The second line contains *K* numbers, separated by a space.

### Output Specification:

For each test case, output in one line the largest sum, together with the first and the last numbers of the maximum subsequence. The numbers must be separated by one space, but there must be no extra space at the end of a line. In case that the maximum subsequence is not unique, output the one with the smallest indices *i* and *j* (as shown by the sample case). If all the *K* numbers are negative, then its maximum sum is defined to be 0, and you are supposed to output the first and the last numbers of the whole sequence.

### Sample Input:

```in
10
-10 1 2 3 4 -5 -23 3 7 -21
```

### Sample Output:

```out
10 1 4
```

# 理解与算法

经典的最大子序列和的问题，不过要多求两个值：最大子序列的始末值，相当于要求出子序列的位置！

最右侧的值很容易给出，因为每一次更新最大值时都会更新这个值，不需要考虑太多。

问题在于怎么找到起始值？

这里我想了很多，后来觉得是多虑了！只需要抓住一个点就行：

**当之前的子序列不可能是最大子序列的时候，更新起始值的下标(`temp_index`)！**那么我们怎么知道这个子序列不可能是最大子序列呢？它的和小于零，出现这个特征不管后面是多大的值，只要加上前面一部分，就会比不加上这一部分要小，所以我们应该直接舍弃，进入下一个子序列的搜寻！于是我们可以把下一个搜寻的起始下标设置为`i+1`，这里的i为迭代变量！

因为这两个下标的更新时间点是互斥的，不可能同时更新，所以要用`else if`连接，否则会导致错误输出！

## 代码实现

```c++
#include <iostream>
#include <vector>

using namespace std;
int main() {
    int count;
    cin >> count;
    vector<int> v(count);
    // 最大值默认为-1，方便后面判断有没有找到最大值
    // 左右下标初始值为整个数组的左右下标！
    int max = -1, temp_max = 0, temp_index = 0, left = 0, right = count - 1;
    for (int i = 0; i < count; ++i) {
        cin >> v[i];
        temp_max += v[i];
        // 如果和已经小于零了，那么再往下走肯定不会是最大子序列！
        if (temp_max < 0) {
            // 重置临时最大值变量
            temp_max = 0;
            // 然后将下标移动到下一个值
            temp_index = i + 1;
        } else if (temp_max > max) {
            // 如果找到了一个更大的和，就记录这个最大值和左右下标，因为起伏不定所以左下标会一直变化，就使用temp_index来作为下标
            max = temp_max;
            left = temp_index;
            right = i;
        }
    }
    // 如果最大值小于0，那么说明没找到大于0的最大值，就将其置为0！
    if (max < 0) max = 0;
    cout << max << " " << v[left] << " " << v[right];
    return 0;
}
```