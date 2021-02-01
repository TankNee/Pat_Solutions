# 题目与翻译

## 1005 Spell It Right 拼写正确 (20分)

Given a non-negative integer *N*, your task is to compute the sum of all the digits of *N*, and output every digit of the sum in English.

给定一个非负整数 n，你的任务是计算 n 的所有数字之和，并用英语输出和的每个数字。

### Input Specification:

### 输入规格:

Each input file contains one test case. Each case occupies one line which contains an *N* (≤10100).

每个输入文件包含一个测试用例，每个用例占用一行，其中包含一个 n (≤10100)。

### Output Specification:

### 输出规格:

For each test case, output in one line the digits of the sum in English words. There must be one space between two consecutive words, but no extra space at the end of a line.

对于每个测试用例，用英语单词在一行中输出和的数字。两个连续的单词之间必须有一个空格，但是在一行的末尾没有额外的空格。

### Sample Input:

### 样本输入:

```in
12345
```

### Sample Output:

### 示例输出:

```out
one five
```

# 理解与算法

就是把各个位置的数字加起来，然后再用英文输出，理解起来没什么难度，重点在于如何实现，如何相对优雅地实现。

写下来有这么几个要注意的：

- 输入的数字可能会非常大，如果我们用整形来存储是存不下的，所以要用字符串string

- 因为要计算每位数字的和，所以要将string拆成多个数字，我们可以利用string是char的数组这一特性，遍历字符串，而其整形值可以用每个字符的值减去`'0'`的值来取。

- 最后输出的是英文字符，如果用if else的办法，就要写很多行，这里用一个字符串数组来存取10个英文单词，这样就不用一个一个比较了，最多可以将速度比原来提升9倍。

- 对于整形如何转为字符串类型，有以下这些办法[^1]

  - ```c
    string to_string (int val);
    
    string to_string (long val);
    
    string to_string (long long val);
    
    string to_string (unsigned val);
    
    string to_string (unsigned long val);
    
    string to_string (unsigned long long val);
    
    string to_string (float val);
    
    string to_string (double val);
    
    string to_string (long double val);
    ```

    

## 代码实现

```c++
#include <iostream>
#include <vector>

using namespace std;

string english_numbers[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int main() {
    string number;
    cin >> number;
    int count = 0;
    for (char i : number) {
        count += i - '0';
    }
    string number_string = to_string(count);
    cout << english_numbers[number_string[0] - '0'];
    for (int i = 1; i < number_string.size(); ++i) {
        cout << " " << english_numbers[number_string[i] - '0'];
    }
    return 0;
}
```

[^1]: https://www.cnblogs.com/smile233/p/8379802.html