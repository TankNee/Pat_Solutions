# 题目

## 1022 Digital Library (30 分)

A Digital Library contains millions of books, stored according to their titles, authors, key words of their abstracts, publishers, and published years. Each book is assigned an unique 7-digit number as its ID. Given any query from a reader, you are supposed to output the resulting books, sorted in increasing order of their ID's.

### Input Specification:

Each input file contains one test case. For each case, the first line contains a positive integer *N* (≤104) which is the total number of books. Then *N* blocks follow, each contains the information of a book in 6 lines:

- Line #1: the 7-digit ID number;
- Line #2: the book title -- a string of no more than 80 characters;
- Line #3: the author -- a string of no more than 80 characters;
- Line #4: the key words -- each word is a string of no more than 10 characters without any white space, and the keywords are separated by exactly one space;
- Line #5: the publisher -- a string of no more than 80 characters;
- Line #6: the published year -- a 4-digit number which is in the range [1000, 3000].

It is assumed that each book belongs to one author only, and contains no more than 5 key words; there are no more than 1000 distinct key words in total; and there are no more than 1000 distinct publishers.

After the book information, there is a line containing a positive integer *M* (≤1000) which is the number of user's search queries. Then *M* lines follow, each in one of the formats shown below:

- 1: a book title
- 2: name of an author
- 3: a key word
- 4: name of a publisher
- 5: a 4-digit number representing the year

### Output Specification:

For each query, first print the original query in a line, then output the resulting book ID's in increasing order, each occupying a line. If no book is found, print `Not Found` instead.

### Sample Input:

```in
3
1111111
The Testing Book
Yue Chen
test code debug sort keywords
ZUCS Print
2011
3333333
Another Testing Book
Yue Chen
test code sort keywords
ZUCS Print2
2012
2222222
The Testing Book
CYLL
keywords debug book
ZUCS Print2
2011
6
1: The Testing Book
2: Yue Chen
3: keywords
4: ZUCS Print
5: 2011
3: blablabla
```

### Sample Output:

```out
1: The Testing Book
1111111
2222222
2: Yue Chen
1111111
3333333
3: keywords
1111111
2222222
3333333
4: ZUCS Print
1111111
5: 2011
1111111
2222222
3: blablabla
Not Found
```

# 理解与算法

这道题只要搞定了输入，其他都不太复杂，只要用几个map就能实现$O(1)$的时间复杂度，值得记忆的点是关键字keywords的读取和划分，最开始我想的是直接读取一整行的内容，然后用空格对读取到的内容进行划分，后来发现有点麻烦，就在网上找到了这样的办法：

```cpp
while (cin >> tmp) {
    keywords_map[tmp].insert(tmp_block.id);
    if (getchar() == '\n') break;
}
```

只要下一个是换行符就当他结束了。

## 代码与实现

```cpp
//
// Created by tanknee on 2/16/2021.
//

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <set>

using namespace std;

struct block {
    int id;
    string title;
    string author;
    vector<string> keywords;
    string publisher;
    int year;
};

int main() {
    int block_num;
    map<string, set<int>> title_map, author_map, keywords_map, publisher_map, year_map;
    cin >> block_num;
    block tmp_block;
    string tmp;
    for (int i = 0; i < block_num; ++i) {
        scanf("%d\n", &tmp_block.id);
        getline(cin, tmp_block.title);
        title_map[tmp_block.title].insert(tmp_block.id);
        getline(cin, tmp_block.author);
        author_map[tmp_block.author].insert(tmp_block.id);
        while (cin >> tmp) {
            keywords_map[tmp].insert(tmp_block.id);
            if (getchar() == '\n') break;
        }
        getline(cin, tmp_block.publisher);
        publisher_map[tmp_block.publisher].insert(tmp_block.id);
        scanf("%d\n", &tmp_block.year);
        year_map[to_string(tmp_block.year)].insert(tmp_block.id);
    }
    int query_num;
    cin >> query_num;
    for (int i = 0; i < query_num; ++i) {
        scanf("%d: ", &block_num);
        getline(cin, tmp);

        printf("%d: %s\n", block_num, tmp.c_str());
        if (year_map.find(tmp) != year_map.end()) {
            for (auto it = year_map[tmp].begin(); it != year_map[tmp].end(); it++) {
                printf("%07d\n", *it);
            }
            continue;
        }
        if (title_map.find(tmp) != title_map.end()) {
            for (auto it = title_map[tmp].begin(); it != title_map[tmp].end(); it++) {
                printf("%07d\n", *it);
            }
            continue;
        }
        if (author_map.find(tmp) != author_map.end()) {
            for (auto it = author_map[tmp].begin(); it != author_map[tmp].end(); it++) {
                printf("%07d\n", *it);
            }
            continue;
        }
        if (keywords_map.find(tmp) != keywords_map.end()) {
            for (auto it = keywords_map[tmp].begin(); it != keywords_map[tmp].end(); it++) {
                printf("%07d\n", *it);
            }
            continue;
        }
        if (publisher_map.find(tmp) != publisher_map.end()) {
            for (auto it = publisher_map[tmp].begin(); it != publisher_map[tmp].end(); it++) {
                printf("%07d\n", *it);
            }
            continue;
        }
        cout << "Not Found" << endl;
    }
    return 0;
}
```