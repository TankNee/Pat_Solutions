# 题目与翻译

## 1006 Sign In and Sign Out 登录和退出 (25分)

At the beginning of every day, the first person who signs in the computer room will unlock the door, and the last one who signs out will lock the door. Given the records of signing in's and out's, you are supposed to find the ones who have unlocked and locked the door on that day.

每天一开始，第一个在机房签名的人将打开门，最后一个签名的人将锁上门。根据登录和离开的记录，你应该找到那天开锁和锁门的人。

### Input Specification:

### 输入规格:

Each input file contains one test case. Each case contains the records for one day. The case starts with a positive integer *M*, which is the total number of records, followed by *M* lines, each in the format:

每个输入文件包含一个测试用例。每个案例包含一天的记录。首先是一个正整数 m，表示记录的总数，然后是 m 行，每行格式如下:

```
ID_number Sign_in_time Sign_out_time
```

where times are given in the format `HH:MM:SS`, and `ID_number` is a string with no more than 15 characters.

其中倍数以 HH: MM: SS 格式给出，而 ID _ number 是一个不超过15个字符的字符串。

### Output Specification:

### 输出规格:

For each test case, output in one line the ID numbers of the persons who have unlocked and locked the door on that day. The two ID numbers must be separated by one space.

对于每个测试用例，用一行输出当天开锁和锁门的人员的 ID 号码。两个 ID 号必须用一个空格分隔。

Note: It is guaranteed that the records are consistent. That is, the sign in time must be earlier than the sign out time for each person, and there are no two persons sign in or out at the same moment.

注意: 保证记录是一致的。也就是说，每个人的签到时间必须早于签到时间，而且不能有两个人同时签到或签出。

### Sample Input:

### 样本输入:

```in
3
CS301111 15:30:28 17:00:10
SC3021234 08:00:00 11:25:25
CS301133 21:45:00 21:58:40
```

### Sample Output:

### 示例输出:

```out
SC3021234 CS301133
```

# 理解与算法

这道题也比较简单，实现一个时间比较算法就行，用几个变量存储最早来的和最迟走的人的学号。

对于时间的比较我们可以先考虑给出的时间格式，八位固定字符串，那么我们可以直接用`substr`方法来读取时分秒的值，然后用运算符比较就行，不需要再转换成整形值。

```c++
/**
 * 判断时间1是否大于时间2，如果大于则返回true，小于返回false，不存在相同的情况
 * @param time_1
 * @param time_2
 * @return compared result
 */
bool compare_time(const string& time_1, const string& time_2) {
    if (time_1.substr(0, 2) > time_2.substr(0, 2)) {
        return true;
    } else if (time_1.substr(0, 2) == time_2.substr(0, 2)) {
        if (time_1.substr(3, 2) > time_2.substr(3, 2)) {
            return true;
        } else if (time_1.substr(3, 2) == time_2.substr(3, 2)) {
            if (time_1.substr(6, 2) > time_2.substr(6, 2)) {
                return true;
            }
        }
    }
    return false;
}
```

同时我们考虑到题目中已经给出时间不会相同，那么只需考虑大于和小于的情况，比较方便。

## 代码实现

```c++
//
// Created by tanknee on 2021/1/23.
//

#include <iostream>

using namespace std;

/**
 * 判断时间1是否大于时间2，如果大于则返回true，小于返回false，不存在相同的情况
 * @param time_1
 * @param time_2
 * @return compared result
 */
bool compare_time(const string& time_1, const string& time_2) {
    if (time_1.substr(0, 2) > time_2.substr(0, 2)) {
        return true;
    } else if (time_1.substr(0, 2) == time_2.substr(0, 2)) {
        if (time_1.substr(3, 2) > time_2.substr(3, 2)) {
            return true;
        } else if (time_1.substr(3, 2) == time_2.substr(3, 2)) {
            if (time_1.substr(6, 2) > time_2.substr(6, 2)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    string earliest_in_people, earliest_in_time, last_out_people, last_out_time, people, in_time, out_time;
    int count;
    cin >> count;
    cin >> earliest_in_people >> earliest_in_time >> last_out_time;
    last_out_people = earliest_in_people;
    for (int i = 1; i < count; ++i) {
        cin >> people >> in_time >> out_time;
        if (!compare_time(in_time, earliest_in_time)) {
            earliest_in_time = in_time;
            earliest_in_people = people;
        }
        if (compare_time(out_time, last_out_time)) {
            last_out_time = out_time;
            last_out_people = people;
        }
    }
    cout << earliest_in_people << " " << last_out_people;
    return 0;
}
```