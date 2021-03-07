# 题目

## 1031 Hello World for U (20 分)

Given any string of *N* (≥5) characters, you are asked to form the characters into the shape of `U`. For example, `helloworld` can be printed as:

```
h  d
e  l
l  r
lowo
```

That is, the characters must be printed in the original order, starting top-down from the left vertical line with *n*1 characters, then left to right along the bottom line with *n*2 characters, and finally bottom-up along the vertical line with *n*3 characters. And more, we would like `U` to be as squared as possible -- that is, it must be satisfied that *n*1=*n*3=max{ *k* | *k*≤*n*2 for all 3≤*n*2≤*N* } with *n*1+*n*2+*n*3−2=*N*.

### Input Specification:

Each input file contains one test case. Each case contains one string with no less than 5 and no more than 80 characters in a line. The string contains no white space.

### Output Specification:

For each test case, print the input string in the shape of U as specified in the description.

### Sample Input:

```in
helloworld!
```

### Sample Output:

```out
h   !
e   d
l   l
lowor
```

# 理解与算法

将给出的字符串U型打印出来，题目的要求是U型的三条边要尽可能一样长，如果无法三等分，那就把多的那部分给最下面的那条边。

```cpp
int n1 = n / 3, n2 = n / 3 + n % 3, index = 0;
```

因为n1=n3，所以只需要计算n1的长度，这里的n是：`int n = strlen(c) + 2;`得到的，所以就有$n1+n2+n3=n=N+2$这个等式！

## 代码与实现

```cpp
//
// Created by tanknee on 2/24/2021.
//

#include <iostream>
#include <string.h>
using namespace std;
int main() {
    char c[81], u[30][30];
    memset(u, ' ', sizeof(u));
    scanf("%s", c);
    int n = strlen(c) + 2;
    int n1 = n / 3, n2 = n / 3 + n % 3, index = 0;
    for(int i = 0; i < n1; i++) u[i][0] = c[index++];
    for(int i = 1; i <= n2 - 2; i++) u[n1-1][i] = c[index++];
    for(int i = n1 - 1; i >= 0; i--) u[i][n2-1] = c[index++];
    for(int i = 0; i < n1; i++) {
        for(int j = 0; j < n2; j++)
            printf("%c", u[i][j]);
        printf("\n");
    }
    return 0;
}
```

