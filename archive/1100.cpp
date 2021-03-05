#include <bits/stdc++.h>

using namespace std;

string to_mars_list[25] = {"tret", "jan", "feb", "mar", "apr", "may", "jun", "jly", "aug", "sep", "oct", "nov", "dec",
                           "tam", "hel", "maa", "huh", "tou", "kes", "hei", "elo", "syy", "lok", "mer", "jou"};

int find_index(string n) {
    for (int i = 0; i < 25; ++i) {
        if (to_mars_list[i] == n) return i;
    }
    return -1;
}

void to_mars(int num) {
    int high = num / 13;
    int low = num % 13;
    if (high) {
        cout << to_mars_list[high + 12];
        if (low) cout << " ";
    }
    if (low || num == 0)
        cout << to_mars_list[low];
    cout << endl;
}

void to_earth(const string &num) {
    int res = 0;
    if (num.find(' ') != -1) {
        string high = num.substr(0, num.find(' '));
        string low = num.substr(num.find(' ') + 1);
        res += (find_index(high) - 12) * 13;
        res += find_index(low);
    } else {
        res += find_index(num) > 12 ? (find_index(num) - 12) * 13 : find_index(num);
    }
    cout << res << endl;
}

int main() {
    int N;
    scanf("%d\n", &N);
    string buf;
    for (int i = 0; i < N; ++i) {
        getline(cin, buf);
        if (!isalpha(buf[0])) {
            to_mars(stoi(buf));
        } else {
            to_earth(buf);
        }
    }
    return 0;
}