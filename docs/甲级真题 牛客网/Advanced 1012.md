# 题目

## Kuchiguse (20)

### **题目描述**

The Japanese language is notorious for its sentence ending particles. Personal preference of such particles can be considered as a reflection of the speaker's personality. Such a preference is called "Kuchiguse" and is often exaggerated artistically in Anime and Manga. For example, the artificial sentence ending particle "nyan~" is often used as a stereotype for characters with a cat-like personality:
Itai nyan~ (It hurts, nyan~)
Ninjin wa iyada nyan~ (I hate carrots, nyan~)
Now given a few lines spoken by the same character, can you find her Kuchiguse?

### **输入描述:**

Each input file contains one test case.  For each case, the first line is an integer N (2<=N<=100). Following are N file lines of 0~256 (inclusive) characters in length, each representing a character's spoken line. The spoken lines are case sensitive.

### **输出描述:**

For each test case, print in one line the kuchiguse of the character, i.e., the longest common suffix of all N lines. If there is no such suffix, write "nai".

### **输入例子:**

```
3
Itai nyan~
Ninjin wa iyadanyan~
uhhh nyan~
```

### **输出例子:**

```
nyan~
```

# 理解与算法

这道题的描述说的云里雾里的，什么玩意儿『Kuchiguse』，不就是口头禅吗，其实这道题就是要你求所有句子的最大公共后缀，因为是公共后缀，所以当一个后缀不满足公共后缀，那就找上一个是公共后缀的字符串。

要注意考虑整个字符串都是公共后缀的情况！

## 代码与实现

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

bool ends_with(string origin, string suffix) {
    if (origin.length() < suffix.length()) return false;
    for (int i = 0; i < suffix.size(); ++i) {
        if (suffix[suffix.length() - 1 - i] != origin[origin.length() - 1 - i]) return false;
    }
    return true;
}

int main() {
    int N, max = 0;
    scanf("%d\n", &N);
    vector<string> sentences;
    for (int i = 0; i < N; ++i) {
        char tmp[256];
        cin.getline(tmp, 256);
        sentences.emplace_back(tmp);
    }
    sort(sentences.begin(), sentences.end(), [](string s1, string s2) {
        return s1.length() < s2.length();
    });
    for (int i = 0; i < sentences[0].length(); ++i) {
        char tmp[256];
        bool flag = false;
        for (int j = 0; j < sentences.size(); ++j) {
            if (!ends_with(sentences[j], sentences[0].substr(sentences[0].length() - i - 1, sentences[0].length()))) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            max = i + 1;
            continue;
        }
        if (max) {
            cout << sentences[0].substr(sentences[0].length() - max, sentences[0].length());
            break;
        } else {
            cout << "nai";
            break;
        }
    }
    if (max == sentences[0].length()) {
        cout << sentences[0].substr(sentences[0].length() - max, sentences[0].length());
    }
    return 0;
}
```

