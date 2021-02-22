# 题目

## 1024 Palindromic Number (25 分)

A number that will be the same when it is written forwards or backwards is known as a **Palindromic Number**. For example, 1234321 is a palindromic number. All single digit numbers are palindromic numbers.

Non-palindromic numbers can be paired with palindromic ones via a series of operations. First, the non-palindromic number is reversed and the result is added to the original number. If the result is not a palindromic number, this is repeated until it gives a palindromic number. For example, if we start from 67, we can obtain a palindromic number in 2 steps: 67 + 76 = 143, and 143 + 341 = 484.

Given any positive integer *N*, you are supposed to find its paired palindromic number and the number of steps taken to find it.

### Input Specification:

Each input file contains one test case. Each case consists of two positive numbers *N* and *K*, where *N* (≤1010) is the initial numer and *K* (≤100) is the maximum number of steps. The numbers are separated by a space.

### Output Specification:

For each test case, output two numbers, one in each line. The first number is the paired palindromic number of *N*, and the second number is the number of steps taken to find the palindromic number. If the palindromic number is not found after *K* steps, just output the number obtained at the *K*th step and *K* instead.

### Sample Input 1:

```in
67 3
```

### Sample Output 1:

```out
484
2
```

### Sample Input 2:

```in
69 3
```

### Sample Output 2:

```out
1353
3
```

# 理解与算法

又是一道回文数的题目，不过在判断回文数的基础上增加了几个步骤，也就是多判断几次罢了，粗略估计数字可能会非常大，用int可能会溢出（ -2147483648~2147483647），所以我们用string来做。

给出一个大数加法的模板：

```cpp
string add(string num1, string num2) {
    int flag = 0;
    string new_num;
    new_num.resize(num1.length());
    for (int i = num1.length() - 1; i >= 0; --i) {
        int tmp = num1[i] - '0' + num2[i] - '0' + flag;
        if (tmp >= 10) {
            tmp -= 10;
            flag = 1;
        } else flag = 0;
        new_num[i] = tmp + '0';
    }
    if (flag) {
        string tmp_num;
        tmp_num.resize(new_num.length() + 1);
        tmp_num[0] = '1';
        for (int i = 1; i < new_num.length() + 1; ++i) {
            tmp_num[i] = new_num[i - 1];
        }
        return tmp_num;
    }
    return new_num;
}
```

其实就是循环加每一位数，然后稍微考虑一下进位即可。

## 代码与实现

```cpp
#include <iostream>

using namespace std;

bool check_palindromic(string num) {
    for (int i = 0; i < (num.length() / 2) + 1; ++i) {
        if (num[i] != num[num.length() - 1 - i]) return false;
    }
    return true;
}

string add(string num1, string num2) {
    int flag = 0;
    string new_num;
    new_num.resize(num1.length());
    for (int i = num1.length() - 1; i >= 0; --i) {
        int tmp = num1[i] - '0' + num2[i] - '0' + flag;
        if (tmp >= 10) {
            tmp -= 10;
            flag = 1;
        } else flag = 0;
        new_num[i] = tmp + '0';
    }
    if (flag) {
        string tmp_num;
        tmp_num.resize(new_num.length() + 1);
        tmp_num[0] = '1';
        for (int i = 1; i < new_num.length() + 1; ++i) {
            tmp_num[i] = new_num[i - 1];
        }
        return tmp_num;
    }
    return new_num;
}

string reverse(string num) {
    string res;
    res.resize(num.length());
    for (int i = num.length() - 1; i >= 0; --i) {
        res[num.length() - 1 - i] = num[i];
    }
    return res;
}

int main() {
    string num, tmp;
    int max_step;
    cin >> num >> max_step;
    tmp.resize(num.length());
    for (int i = 0; i < num.length(); ++i) {
        tmp[num.length() - i - 1] = num[i];
    }
    int step = 0;
    while (step < max_step) {
        if (check_palindromic(num)) {
            cout << num << endl;
            cout << step;
            break;
        }
        num = add(num, tmp);
        tmp = reverse(num);
        step++;
    }
    if (step >= max_step) {
        cout << num << endl;
        cout << max_step;
    }
    return 0;
}
```