//
// Created by tanknee on 2021/2/5.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int lengthOfLongestSubstring(const string &s) {
    int i = 0, j = 0;
    int characters[130], max_length = 0;
    while (i < s.length() && j < s.length()) {
        j = i + 1;
        fill(characters, characters + 130, -1);
        characters[s[i]] = i;
        while (j < s.length() && characters[s[j]] == -1) {
            characters[s[j]] = j;
            j++;
        }
        max_length = max(max_length, j - i);
        i = characters[s[j]] + 1;
    }
    return max_length;
}
