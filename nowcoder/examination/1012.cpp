//
// Created by tanknee on 2021/1/30.
//

#include <iostream>
#include <vector>
#include <algorithm>

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