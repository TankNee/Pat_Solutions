# 题目

## 1023 Have Fun with Numbers (20 分)

Notice that the number 123456789 is a 9-digit number consisting exactly the numbers from 1 to 9, with no duplication. Double it we will obtain 246913578, which happens to be another 9-digit number consisting exactly the numbers from 1 to 9, only in a different permutation. Check to see the result if we double it again!

Now you are suppose to check if there are more numbers with this property. That is, double a given number with *k* digits, you are to tell if the resulting number consists of only a permutation of the digits in the original number.

### Input Specification:

Each input contains one test case. Each case contains one positive integer with no more than 20 digits.

### Output Specification:

For each test case, first print in a line "Yes" if doubling the input number gives a number that consists of only a permutation of the digits in the original number, or "No" if not. Then in the next line, print the doubled number.

### Sample Input:

```in
1234567899
```

### Sample Output:

```out
Yes
2469135798
```

# 理解与算法

将给定的数字变为原来的两倍，然后计算结果是否由原来数字的各个数组成。要注意这里给出的数字最大可能有20位，所以用int存不下（ -2147483648~2147483647），同时为了方便拿到每一位上的数字，我选择使用string来存。然后手写一个大数乘法就行，比较方便。

## 代码与实现

```cpp
#include <iostream>

using namespace std;

int main() {
    string num;
    cin >> num;
    string new_num;
    new_num.resize(num.length());
    int flag = 0, cur = 0;
    for (int i = num.length() - 1; i >= 0; --i) {
        cur = num[i] - '0';
        cur = cur * 2 + flag;
        if (cur >= 10) {
            cur -= 10;
            flag = 1;
        } else flag = 0;
        new_num[i] = cur + '0';
    }
    // 如果进位了那么数字位数都对不上肯定不满足题目要求！
    if (flag) {
        cout << "No" << endl;
        cout << "1" << new_num;
        return 0;
    }
    int tmp[num.length()];
    fill(tmp, tmp + num.length(), 0);
    for (char &j : num) {
        tmp[j - '0']++;
    }
    for (int i = 0; i < new_num.length(); ++i) {
        if (tmp[new_num[i] - '0'] <= 0) {
            cout << "No" << endl;
            cout << new_num;
            return 0;
        } else {
            tmp[new_num[i] - '0']--;
        }
    }
    cout << "Yes" << endl;
    cout << new_num;
    return 0;
}
```

