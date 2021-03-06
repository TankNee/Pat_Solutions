# 题目

## 1036 Boys vs Girls (25 分)

This time you are asked to tell the difference between the lowest grade of all the male students and the highest grade of all the female students.

### Input Specification:

Each input file contains one test case. Each case contains a positive integer *N*, followed by *N* lines of student information. Each line contains a student's `name`, `gender`, `ID` and `grade`, separated by a space, where `name` and `ID` are strings of no more than 10 characters with no space, `gender` is either `F` (female) or `M` (male), and `grade` is an integer between 0 and 100. It is guaranteed that all the grades are distinct.

### Output Specification:

For each test case, output in 3 lines. The first line gives the name and ID of the female student with the highest grade, and the second line gives that of the male student with the lowest grade. The third line gives the difference *g**r**a**d**e**F*−*g**r**a**d**e**M*. If one such kind of student is missing, output `Absent` in the corresponding line, and output `NA` in the third line instead.

### Sample Input 1:

```in
3
Joe M Math990112 89
Mike M CS991301 100
Mary F EE990830 95
```

### Sample Output 1:

```out
Mary EE990830
Joe Math990112
6
```

### Sample Input 2:

```in
1
Jean M AA980920 60
```

### Sample Output 2:

```out
Absent
Jean AA980920
NA
```

# 理解与算法

排序题。

## 代码与实现

```cpp
//
// Created by tanknee on 2021/3/1.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct student {
    string name, id;
    char sex;
    int grade;
};

int main() {
    int N;
    vector<student> males;
    vector<student> females;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        student s;
        cin >> s.name >> s.sex >> s.id >> s.grade;
        if (s.sex == 'M') {
            males.push_back(s);
        } else {
            females.push_back(s);
        }
    }
    sort(males.begin(), males.end(), [](const student &s1, const student &s2) { return s1.grade < s2.grade; });
    sort(females.begin(), females.end(), [](const student &s1, const student &s2) { return s1.grade > s2.grade; });
    if (males.empty()) {
        if (females.empty()) cout << "Absent" << endl;
        else {
            cout << females[0].name << " " << females[0].id << endl;
        }
        cout << "Absent" << endl;
        cout << "NA";
        return 0;
    } else if (females.empty()) {
        cout << "Absent" << endl;
        if (males.empty()) cout << "Absent" << endl;
        else {
            cout << males[0].name << " " << males[0].id << endl;
        }
        cout << "NA";
        return 0;
    }
    cout << females[0].name << " " << females[0].id << endl;
    cout << males[0].name << " " << males[0].id << endl;
    cout << females[0].grade - males[0].grade;
    return 0;
}
```

